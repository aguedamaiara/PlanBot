
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
#include <credentials.h>
#include <ArduinoJson.h>

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;-
UniversalTelegramBot bot(PLANT_NOTE_BOT, secured_client);

const unsigned long SCAN_DELAY = 1000;
unsigned long lastScan;

extern "C"
{
#include <lwip/icmp.h> // needed for icmp packet definitions
}

// Declaração de variáveis globais
int soilSensorInput, soilSensorPercentage;
int baselineAir = 680;
int baselineWater = 280;
int minimumPercentage = 35;
bool watered = true;
bool waitMin = false;

// Configuração de endereços IP
IPAddress local_IP(192, 168, 100, 36);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);
const int DNS_PORT = 53;

// Função para limitar um valor de porcentagem entre 0 e 100
void percentageLimiter(int &percentageReading)
{
  if (percentageReading < 0)
    percentageReading = 0;
  else if (percentageReading > 100)
    percentageReading = 100;
}

// Função de callback para o modo de configuração da rede Wi-Fi
void configModeCallback(WiFiManager *wifiManager)
{
  Serial.println("entered config mode");
  Serial.println(WiFi.softAPIP());
}

// Função para lidar com mensagens recebidas do bot do Telegram
void messagesHandler(int numNewMessages)
{
  Serial.printf("\n Recebidas %d novas mensagens \n", numNewMessages);
  String response;

  for (int i = 0; i < numNewMessages; i++)
  {
    telegramMessage &msg = bot.messages[i];
    Serial.print("Mensagem " + msg.text);
    Serial.print(numNewMessages);
    Serial.print(i);

    if (msg.text == "/setmin" || msg.text == "/setmin@plantnote_bot")
    {
      waitMin = true;
      response = "Defina a umidade mínima respondendo com um número entre 5 e 90";
    }
    else if (msg.text.toInt() >= 5 && msg.text.toInt() <= 90 && waitMin == true)
    {
      waitMin = false;
      minimumPercentage = msg.text.toInt();
      response = "Porcentagem mínima definida para " + msg.text;
    }
    else if (msg.text == "/humidity" || msg.text == "/humidity@plantnote_bot")
    {
      response = "A umidade atual é " + String(soilSensorPercentage) + "%";
    }
    else
    {
      response = "Isso não foi uma entrada válida";
    }

    bot.sendMessage(msg.chat_id, response, "Markdown");
  }
}

void setup()
{
  WiFi.mode(WIFI_STA);
  WiFiManager wifiManager;
  bool res;

  // Inicialização do monitor serial
  Serial.begin(9600);
  Serial.println("");

  // Configuração do callback para o modo de configuração Wi-Fi
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 1, 1), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));
  res = wifiManager.autoConnect(BOT_NAME);

  Serial.println(WiFi.localIP());

  if (!res)
  {
    Serial.print("NÃO CONECTADO");
    ESP.restart();
  }
  else
  {
    // Configuração de conexão segura com o Telegram
    secured_client.setTrustAnchors(&cert);

    Serial.print("Obtendo a hora: ");
    configTime(0, 0, "pool.ntp.org"); // Obtenção do tempo UTC via NTP

    time_t now = time(nullptr);

    while (now < 24 * 3600)
    {
      Serial.print(".");
      delay(100);
      now = time(nullptr);
    }

    Serial.println(now);

    Serial.print("Enviando mensagem para ");
    Serial.println(CHAT_ID);

    bot.sendMessage(CHAT_ID, "Bot de planta iniciado, umidade mínima - 35%", "");
}

void loop()
{
  // Leitura da umidade do solo
  soilSensorInput = analogRead(A0);
  soilSensorPercentage = map(soilSensorInput, baselineAir, baselineWater, 0, 100);
  percentageLimiter(soilSensorPercentage);

  // Verificação de novas mensagens do bot do Telegram
  if (millis() - lastScan > SCAN_DELAY)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Serial.print(numNewMessages);

    while (numNewMessages)
    {
      Serial.println("recebeu resposta");
      messagesHandler(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Serial.print(numNewMessages);
    lastScan = millis();
  }

  // Verificação da umidade do solo e envio de alertas
  if (waitMin == false)
  {
    if (soilSensorPercentage < minimumPercentage && watered == true)
    {
      watered = false;
      Serial.print("Planta precisa de água!! Umidade atual: ");
      Serial.println(soilSensorPercentage);
      bot.sendMessage(CHAT_ID,"*ALERTA!! PLANTA PRECISA DE ÁGUA!!* Porcentagem atual: ", "Markdown");
      bot.sendMessage(CHAT_ID, String(soilSensorPercentage), "");
    }
    else if (soilSensorPercentage >= minimumPercentage && watered == false)
    {
        watered = true;
      Serial.print("Planta regada *! Umidade atual: ");
      Serial.println(soilSensorPercentage);
      bot.sendMessage(CHAT_ID, "Planta *regada*!", "");
    }
  }
}
