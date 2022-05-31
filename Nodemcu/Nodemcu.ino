#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <SoftwareSerial.h>

SoftwareSerial ss(D6,D5);

const char* ssid = "anjani";
const char* password = "gendhisanjani";


#define BOTtoken "5541256803:AAHowykPvbjNtV-6T84liTLGuyMDoARnY_M"
#define CHAT_ID "1097157888"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(9600);
  ss.begin(115200);
  WiFi.begin(ssid, password);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  bot.sendMessage(CHAT_ID, "System started", "");
  delay(1000);
}

void loop() {
//  bool value = digitalRead(Sensor);
//  Serial.println(value);
//  if (value == 1) {
//    Serial.println("Motion Detected");
//    digitalWrite(LEDR, HIGH);
//    digitalWrite(Buzzer, HIGH);
//    digitalWrite(LEDG, LOW);
//    lcd.setCursor(0, 0);
//    lcd.print("Motion Detected");
//    bot.sendMessage(CHAT_ID, "Motion detected!!", "");
//  } else if (value == 0) {
//    digitalWrite(LEDR, LOW);
//    digitalWrite(Buzzer, LOW);
//    digitalWrite(LEDG, HIGH);
//    lcd.setCursor(0, 0);
//    lcd.print("No Motion      ");
//  }

  Serial.println("...");
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
          char valSensor = tmpValue.charAt(1);
          Serial.println(valSensor);
        }
    }
  }
}
