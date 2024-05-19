#include <WiFi.h> // Inclui a biblioteca WiFi para conectar o ESP32 à rede sem fio.
#include <PubSubClient.h> // Inclui a biblioteca PubSubClient para permitir comunicação MQTT.

// Definições de constantes para conexão Wi-Fi e MQTT
#define WIFISSID "Seu Wi-Fi" // Define o SSID da rede Wi-Fi.
#define PASSWORD "Exemplo" // Define a senha da rede Wi-Fi.
#define TOKEN "SEU TOKEN" // Token de autenticação para Ubidots.
#define MQTT_CLIENT_NAME "SEU NOME PARA MQTT" // Nome do cliente MQTT utilizado na conexão MQTT.

/****************************************
 * Definir Constantes
 ****************************************/
#define VARIABLE_LABEL "sensor" // Nome da variável que será usada ao enviar dados para o Ubidots.
#define DEVICE_LABEL "esp32" // Nome do dispositivo conforme registrado no Ubidots.

// Configuração de pinagem para o sensor AD8232 e para o buzzer
#define LO_PLUS_PIN 2   // Pino ESP32 conectado ao pino L0+ do sensor AD8232.
#define LO_MINUS_PIN 4  // Pino ESP32 conectado ao pino L0- do sensor AD8232.
#define SENSOR_OUTPUT_PIN 36 // Pino VP da ESP32 conectado ao OUTPUT do sensor AD8232.
#define BUZZER_PIN 5    // Pino D5 da ESP32 conectado ao positivo do buzzer.

char mqttBroker[] = "industrial.api.ubidots.com"; // Endereço do broker MQTT (Ubidots).
char payload[100]; // Array para armazenar a mensagem de payload a ser enviada.
char topic[150]; // Array para armazenar o tópico de destino MQTT.
char str_sensor[10]; // Array para armazenar o valor do sensor convertido em string.

WiFiClient ubidots; // Cliente WiFi para conexão com o Ubidots.
PubSubClient client(ubidots); // Cliente MQTT configurado com o cliente WiFi.

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1]; // Cria um buffer temporário para o payload.
  memcpy(p, payload, length); // Copia os dados para o buffer.
  p[length] = NULL; // Adiciona terminador de string.
  Serial.write(payload, length); // Escreve o payload no Serial para depuração.
  Serial.println(topic); // Imprime o tópico no Serial.
}

void reconnect() {
  while (!client.connected()) { // Enquanto o cliente não estiver conectado.
    Serial.println("Tentando conexão MQTT...");
    // Tenta conectar com o servidor MQTT.
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Conectado"); // Conexão bem sucedida.
    } else {
      Serial.print("Falha, rc="); // Falha na conexão.
      Serial.print(client.state());
      Serial.println(" tentar novamente em 2 segundos");
      delay(2000); // Espera 2 segundos antes de tentar novamente.
    }
  }
}

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial a 115200 bps.
  WiFi.begin(WIFISSID, PASSWORD); // Conecta na rede Wi-Fi.
  // Configura os pinos como entrada ou saída conforme necessário.
  pinMode(LO_PLUS_PIN, INPUT);
  pinMode(LO_MINUS_PIN, INPUT);
  pinMode(SENSOR_OUTPUT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println();
  Serial.print("Aguardando WiFi..."); // Aguarda conexão Wi-Fi.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi Conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP()); // Exibe o endereço IP na serial.
  client.setServer(mqttBroker, 1883); // Define o servidor MQTT e a porta.
  client.setCallback(callback); // Define a função de callback para mensagens MQTT.
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Reconecta se não estiver conectado.
  }

  static float lastSensorValue = 0; // Valor anterior do sensor para filtro.
  float sensorValue = analogRead(SENSOR_OUTPUT_PIN); // Lê o valor do sensor.
  sensorValue = 0.5 * lastSensorValue + 0.5 * sensorValue; // Aplica um filtro simples.
  lastSensorValue = sensorValue;

  dtostrf(sensorValue, 4, 2, str_sensor); // Converte o valor do sensor para string.
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL); // Monta o tópico MQTT.
  sprintf(payload, "{\"%s\":{\"value\":%s}}", VARIABLE_LABEL, str_sensor); // Monta o payload.

  if (sensorValue > 2000) { // Se o valor for maior que o limiar.
    digitalWrite(BUZZER_PIN, HIGH); // Aciona o buzzer.
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.println("Publicando dados para a nuvem Ubidots"); // Informa que está publicando.
  client.publish(topic, payload); // Publica os dados no Ubidots.
  client.loop();
  delay(2000); // Aguarda 2 segundos para nova publicação.
}
