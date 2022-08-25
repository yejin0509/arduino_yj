#include <EspMQTTClient.h> // PubSubclient 라이브러리를 포함한 ESP32 MQTT Client 라이브러리
#include <DHT.h> //DHT11 라이브러리
#define DHTTYPE DHT11 // DHT 센서 타입 정의
DHT dht(13, DHTTYPE); //DHT 설정 dht( 핀, DHT 종류)
float temp1,humid1;
char temp[10]; // temp, humid 를 문자열로 합쳐서 전송하기 위한 변수 정의
char humid[10];
EspMQTTClient client(
"U+Net9048", // SSID
"1DECJE#2A4", // PW
"broker.mqttdashboard.com", // MQTT Broker 서버 IP
"TEST", // 클라이언트 이름
1883 // MQTT 포트번호
);


void setup()
{
Serial.begin(115200); //Initialize serial
dht.begin();
client.enableDebuggingMessages();
client.enableLastWillMessage("TestClient/lastwill", "I am going offline");
}
void onConnectionEstablished(){
}
void loop() {
client.loop();
temp1 = dht.readTemperature(); // 온도를 읽어서 tem에 저장
humid1 = dht.readHumidity(); // 습도를 읽어서 hum에 저장
sprintf(temp, "%.2f" ,dht.readTemperature());
sprintf(humid, "%.2f" ,dht.readHumidity());
Serial.print(F("Humidity : "));
Serial.println(humid1);
Serial.print(F("Temperature : "));
Serial.println(temp1);
client.publish("mytopic/temp", temp);
client.publish("mytopic/humid", humid);
delay(5000);

}
