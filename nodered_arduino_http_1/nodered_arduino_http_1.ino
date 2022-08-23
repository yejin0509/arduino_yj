//https://randomnerdtutorials.com/esp32-http-get-post-arduino/
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float tem = 0;
float hum = 0;

const char* ssid = "U+Net9048";
const char* password = "1DECJE#2A4";
String serverName = "http://192.168.123.105:1880/test-1";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {

delay(500);
Serial.begin(9600);

WiFi.begin(ssid, password);
Serial.println("Connecting");

while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
void loop() {

tem = dht.readTemperature();
hum = dht.readHumidity();

Serial.print("Temperature :");
Serial.print(tem);

Serial.print("Humidity :");
Serial.print(hum);


if ((millis() - lastTime) > timerDelay) {

if(WiFi.status()== WL_CONNECTED){
HTTPClient http;
String serverPath = serverName + "?Temperature=" + String(tem) + "&" + "Humidity=" + String(hum);

http.begin(serverPath.c_str());       //부동숫자 문자열로 변경

int httpResponseCode = http.GET();

if (httpResponseCode>0) {
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
String payload = http.getString();
Serial.println(payload);
}
else {
Serial.print("Error code: ");
Serial.println(httpResponseCode);
}

http.end();
}
else {
Serial.println("WiFi Disconnected");
}
lastTime = millis();
}
}
