/*
Exemplo básico de conexão a Konker Plataform via MQTT, baseado no https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_auth/mqtt_auth.ino. Este exemplo se utiliza das bibliotecas do ESP8266 programado via Arduino IDE (https://github.com/esp8266/Arduino) e a biblioteca PubSubClient que pode ser obtida em: https://github.com/knolleary/pubsubclient/
*/

#include<string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Vamos primeiramente conectar o ESP8266 com a rede Wireless (mude os parâmetros abaixo para sua rede).
char byteRead;
byte arByte[130];
int contAr = 0;
char msg[200] ;
int cindex = 0;
const char* ssid = "batis";
const char* password = "66425769r";

//Criando a função de callback
void callback(char* topic, byte* payload, unsigned int length) {
  // Essa função trata das mensagens que são recebidas no tópico no qual o Arduino esta inscrito.
}

//Criando os objetos de conexão com a rede e com o servidor MQTT.
WiFiClient espClient;
PubSubClient client("mqtt.hackathon.konkerlabs.net", 1883, callback,espClient);
ADC_MODE(ADC_VCC);
char mensagemC[150];

void setup()
{
  //Conectando na Rede
    Serial.begin(57600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //Configurando a conexão com o servidor MQTT
    if (client.connect("Sorena", "2eu3tldjb756", "S6wsiJLuO5vu")) {
    //Subscrevendo no tópico <tópico para subscrição>
    client.subscribe("sub/2eu3tldjb756/banana");

  }
}

void loop()
{
  //Vamos manter o cliente ativo para receber mensagens no tópico de subscrição

  
  client.loop();
  
  
  do{
   if (Serial.available() > 0) { 
    byteRead = Serial.read();
    msg[cindex] = byteRead;
    cindex++;
   }
  }while(byteRead != 125);
  msg[cindex] = '\0';
  cindex = 0;
  Serial.println(msg);
  Serial.println("mensagem recebida");
  
  
    //Agora vamos publicar uma mensagem no <tópico para pubicação>. Nota: a mensagem deve estar no formato JSON.
    client.publish("pub/2eu3tldjb756/banana",msg);

}

