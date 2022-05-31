#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

SoftwareSerial ss(D6,D5); // D6 to pin 3 Arduino, D5 to pin 2 Arduino

const char* ssid = "AAA";
const char* password = "universe";

#define BOTtoken "5548817647:AAF-ZmTBbysfridOEa_bJ4tvgKU2uRGW_RI"

#define CHAT_ID "1009881422"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

String nilaiSrf = "";


void setup() {
  Serial.begin(9600);
  ss.begin(115200);
  WiFi.begin(ssid, password);

  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
//  Serial.println("...");
  String tmpValue = "";
  String msg = "";
  while(ss.available() > 0){
    char mychar = ss.read();
    tmpValue += mychar;
    delay(10);
  }

  if(tmpValue != ""){
    
    if(WiFi.status() == WL_CONNECTED){
        if(tmpValue.charAt(0) == '@'){
          String newTmpValue = "";
          for(int i=1;i<tmpValue.length();i++){
              newTmpValue += tmpValue.charAt(i);
          }

          WiFiClient client;
          HTTPClient http;
          String url = "";
//          url += "srf=";
          url += tmpValue.charAt(1);
          url += tmpValue.charAt(2);
          
          Serial.println(url);
          http.begin(client,url);  
          http.GET();
          String payload = http.getString();  
          Serial.println('#' + String(payload));  
          http.end();

          if(url <= "5"){
            Serial.println("Pompa Menyala!");
          }
          else{
            bot.sendMessage(CHAT_ID, "Air Penuh!", "");
            Serial.println("Pompa Mati!");
          }
        } 

    }
  }

  
  if(WiFi.status() != WL_CONNECTED){
    recon();
  }
  
   delay(50);
}

void recon(){
  while(WiFi.status() != WL_CONNECTED){

    //wifi reload connection
    WiFi.begin(ssid, password);
    delay(1000);

  }
}
