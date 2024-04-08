## PlanBot

<img src="https://iron-canidae-085.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F4f850864-337d-474c-a85f-f61228b0ba02%2Ffecc543f-f60b-4614-8d46-9bf89ccfd7a2%2FPlanBot_logo.png?table=block&id=ca427296-f71f-401c-b692-ef2ff28a89bd&spaceId=4f850864-337d-474c-a85f-f61228b0ba02&width=580&userId=&cache=v2" alt="PlanBot Logo" width="300">

## Introdução

O PlanBot utiliza uma abordagem prática e eficiente para monitorar o nível de umidade do solo. Ao conectar-se a uma rede Wi-Fi por meio da placa de desenvolvimento ESP8266 e utilizar um sensor de umidade do solo, o sistema envia mensagens automáticas via Telegram, adaptando-se às necessidades específicas de suas plantas.


### Simulação

![Sensor de umidade do solo](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fhttp2.mlstatic.com%2Fsensor-de-umidade-do-solo-higrmetro-ideal-arduino-pic-D_NQ_NP_614225-MLB25397788356_022017-O.jpg&f=1&nofb=1&ipt=a36d7e7c4b903e7511e0b25af83e905cda7aa8144b2e00d45eb4248e1f50a787&ipo=images)

### Hardware

O hardware utilizado no projeto inclui:

- 1 placa de desenvolvimento ESP8266
- 1 sensor de umidade do solo
- 5 jumpers fêmea-fêmea
- 1 Módulo Comparador

### Montagem

A montagem é realizada conectando o sensor de umidade do solo à placa de desenvolvimento ESP8266, seguindo as instruções fornecidas no projeto original. É essencial seguir corretamente as conexões para garantir o funcionamento adequado.

### Programação

A etapa de programação do projeto é fundamental para garantir a integração eficiente entre o hardware e o bot do Telegram. Utilizamos a Arduino IDE para desenvolver o código necessário, incorporando bibliotecas essenciais que aprimoram as funcionalidades do sistema.

### Bibliotecas Utilizadas

1. **Universal Telegram Bot** ([Link](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)): Esta biblioteca proporciona uma interface para a integração de bots do Telegram com projetos Arduino.
2. **WiFiManager** ([Link](https://github.com/tzapu/WiFiManager)): O WiFiManager simplifica a configuração e a conexão a redes Wi-Fi em dispositivos Arduino.
3. **ArduinoJson** ([Link](https://github.com/bblanchon/ArduinoJson)): Projetada para facilitar a manipulação e geração de dados em formato JSON em projetos Arduino.
4. **ThingSpeak** ([Link](https://thingspeak.com/)): Oferece uma plataforma completa para a coleta, armazenamento e visualização de dados provenientes de dispositivos IoT.

## Instruções para Executar o Projeto

Para executar o projeto PlanBot, siga as etapas abaixo:

### 1. Montagem do Hardware

- Conecte o sensor de umidade do solo à placa de desenvolvimento ESP8266 conforme as instruções fornecidas no projeto.
- Certifique-se de seguir corretamente as conexões para garantir o funcionamento adequado.

### 2. Programação

- Abra a Arduino IDE e carregue o código fonte do projeto.
- Certifique-se de ter instalado as bibliotecas necessárias mencionadas na seção "Bibliotecas Utilizadas".
- Realize as configurações necessárias, como a chave da API do bot do Telegram, o ID do chat e o nome do bot.

### 3. Conexão à Internet

- Após a programação, conecte o dispositivo à internet.
- O WiFiManager simplifica o processo de conexão à rede Wi-Fi. Siga as instruções para configurar a rede Wi-Fi.

### 4. Utilização

- Posicione o sensor de umidade do solo no solo próximo à planta que deseja monitorar.
- Após a conexão bem-sucedida com o Wi-Fi, o bot do Telegram enviará uma notificação confirmando o início do monitoramento, com a umidade mínima predefinida em 35%.
- Utilize os comandos específicos no Telegram para ajustar o limite de umidade desejado e verificar a umidade atual.
- Após regar a planta, o bot enviará uma mensagem de confirmação.

Com essas etapas concluídas, o projeto PlanBot estará em pleno funcionamento, ajudando a manter suas plantas saudáveis e bem cuidadas.


### Referências

- [Automatic Plant Watering Messenger (using Telegram) : 7 Steps - Instructables](https://www.instructables.com/Automatic-Plant-Watering-Messenger-using-Telegram/)

### Equipe: 
@aguedamaiara, @ImBeca e @alanealvess 
