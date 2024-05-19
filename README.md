# Monitor_cardiaco_IOT
Meu projeto IoT da Universidade Presbiteriana Mackenzie. O projeto foi desenvolvido em C++ utilizando a IDE Arduino.

## <br> Descrição
Uilizarei o ESP32 para monitoramento de batimentos cardíacos wireless, 
combinado com o sensor ECG AD8232 e um buzzer como atuador para alertas. O 
desenvolvimento será feito na IDE do Arduino, empregando programação 
específica para integrar hardware e software, incluindo a comunicação via MQTT 
para transmissão de dados em tempo real para a plataforma Ubidots.

## <br> Instalação da IDE do Arduino
Baixar a IDE do Arduino:

Acesse o site oficial do Arduino.
Navegue até a seção de downloads e escolha a versão da IDE do Arduino compatível com seu sistema operacional (Windows, macOS ou Linux).
Instalar a IDE:

Windows: Execute o instalador baixado e siga as instruções na tela. Certifique-se de instalar todos os drivers necessários durante o processo de instalação.
macOS: Abra o arquivo .zip baixado e arraste o aplicativo Arduino para a pasta "Aplicativos".
Linux: Descompacte o arquivo baixado e execute o script de instalação.
Verificar a Instalação:

Abra a IDE do Arduino para garantir que foi instalada corretamente.
Configurando a ESP32 na IDE do Arduino
Adicionar o URL do Gerenciador de Placas para a ESP32:

Na IDE do Arduino, vá até "Arquivo" > "Preferências".
No campo "URLs Adicionais de Gerenciadores de Placas", insira o seguinte URL para o pacote da ESP32:

https://dl.espressif.com/dl/package_esp32_index.json

Clique em "OK" para salvar.

## <br> Instalar a Placa ESP32:

Navegue até "Ferramentas" > "Placa:" > "Gerenciador de Placas...".
Na janela do Gerenciador de Placas, digite "ESP32" na barra de pesquisa.
Encontre o pacote chamado "esp32 by Espressif Systems" e clique em "Instalar".

## <br> Selecionar a Placa ESP32:

Após a instalação, vá para "Ferramentas" > "Placa:" e selecione o modelo específico da sua ESP32 na lista de placas disponíveis.

## <br> Conectar e Carregar um Sketch
Conectar a ESP32 ao Computador:

Use um cabo micro USB para conectar a ESP32 à porta USB do seu computador.

## <br> Selecionar a Porta COM:

Vá para "Ferramentas" > "Porta" e selecione a porta COM que aparece com o nome da sua ESP32. Se você não tem certeza de qual porta selecionar, desconecte a placa, abra o menu novamente para ver as portas listadas, reconecte a placa e veja qual nova porta aparece.

## <br> Carregar um Sketch de Teste:

Abra um exemplo básico navegando em "Arquivo" > "Exemplos" > "01.Basics" > "Blink".
Clique no ícone de "Upload" (seta para a direita) na barra de ferramentas da IDE para carregar o sketch na sua ESP32.
Observe o LED na placa piscando, indicando que o programa está sendo executado corretamente.
Depois que conseguir testar, faça upload do meu código "code-esp32", adaptando-o para sua finalidade.



## <br> Modelo de Montagem 

O sensor ECG AD8232 é conectado ao microcontrolador ESP32, que irá processar os dados dos batimentos cardíacos. O ESP32 está ligado a um buzzer, que será utilizado para alertar o usuário em caso de detecção de anomalias cardíacas. Os cabos de alimentação do sensor ECG são conectados às entradas de 3,3V e GND do ESP32, enquanto o sinal de saída do sensor é conectado a um dos pinos analógicos. O buzzer é conectado a um pino digital do ESP32 e a GND. Este sistema é alimentado por uma fonte de 3,7V, adequada para a operação dos componentes eletrônicos envolvidos. Também há a possibilidade de alimentar todo o circuito através de um cabo USB direto de um computador, já que a ESP32 possui entrada para tal.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/b08592e9-1129-4684-b1df-b84bd5339e8e)


## <br> Configurando conta Ubidots

Para publicar os dados no IoT Cloud, precisamos de alguma plataforma IoT. Portanto, Ubidots é uma dessas plataformas. Ubidots oferece uma plataforma para desenvolvedores que lhes permite capturar facilmente dados de sensores e transformá-los em informações úteis. Use a plataforma Ubidots para enviar dados para a nuvem a partir de qualquer dispositivo habilitado para Internet.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/8fab43f3-b999-438e-8804-7296ab05c5a7)

## <br> Etapa 1: Criando uma conta Ubidots

Acesse ubidots.com e crie uma conta. Você terá um período de teste de 30 dias.

## <br> Etapa 2: Criando Dispositivo e Adicionando Variáveis

Agora configure um dispositivo Ubidots. Para criá-lo, vá para a seção Dispositivos (Dispositivos > Dispositivos). Crie um novo dispositivo com o nome esp32.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/9426718e-4ad7-4662-9945-e9a59bd2ccdd)

Depois que o dispositivo for criado, crie uma nova variável renomeando a variável para sensor.


![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/7d07bbf5-cf7a-4797-81be-adadf4a71ac6)


## <br> Etapa 3: Criação de painéis

Vamos configurar um painel do Ubidots. Para criá-lo, vá para a seção Dashboard (Dados > Dashboard)

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/f8a0a774-460d-411c-bc99-60e8bb5e1e2c)

## <br> Etapa 4: adicionar novos widgets

Clique no sinal + no lado direito e em “Adicionar novo widget” e selecione seu widget.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/2d16283b-d125-4b74-b2e7-8398a679c137)

Agora, selecione o tipo de widget que deseja exibir. No meu caso, escolho o “Gráfico de Linhas”:

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/281b8863-ae70-4d1b-aecf-49c2e48ee9b0)

Em seguida, selecione a variável desejada para exibir os dados. Ubidots permite atribuir um nome personalizado ao widget, cor, período de dados a serem exibidos e muito mais. Para finalizar a criação do widget, pressione o ícone verde.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/e486c685-1d7e-4856-9b40-c2a7d277c262)

Selecione seu dispositivo e variáveis ​​criados anteriormente, conforme mostrado na figura abaixo.

![image](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/eaf14047-0b5f-4de1-8aac-6b5f7c418497)

## <br> Funcionamento

Sensor ECG AD8232: Captura os sinais elétricos do coração e envia para o ESP32.
ESP32: Processa os dados do sensor ECG e verifica se há alguma anomalia nos 
batimentos cardíacos. Se algo atípico for detectado, o ESP32 ativa o buzzer.
Buzzer: Atua como um alerta sonoro em caso de detecção de anomalias cardíacas.
Comunicação MQTT: Configuração do ESP32 para enviar dados dos batimentos 
cardíacos via protocolo MQTT para um servidor ou plataforma na nuvem, 
permitindo monitoramento remoto.

## <br> Vídeo-demonstração

https://youtu.be/tPufbUc4Oz0

## <br> Dados obtidos via MQTT no Ubidots

Gráfico de Leitura no Ubidots: No contexto do projeto de monitoramento de ECG utilizando o ESP32 e o sensor AD8232, implementei um filtro de média móvel para suavizar os sinais de entrada do sensor. O filtro de média móvel é uma técnica fundamental no processamento de sinais para reduzir o ruído aleatório e melhorar a confiabilidade dos dados medidos. Esta implementação especificamente utiliza uma média móvel simples, onde o valor atual do sensor é combinado com o último valor filtrado. O fator de 0.5 para ambos os valores atuais e anteriores equilibra a contribuição de cada um, oferecendo uma suavização efetiva sem atrasar demais a resposta a mudanças reais no sinal.

![Captura de tela 2024-05-10 201025](https://github.com/pedrojhenrique/monitor-cardiaco-IoT/assets/105826347/5d0239a5-b290-4bb5-ab1c-b38bcca7592d)
