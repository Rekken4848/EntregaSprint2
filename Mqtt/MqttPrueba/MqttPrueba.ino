/*
  Basic ESP8266 MQTT example

  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.

  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/
const int EchoPin = 25;
const int TriggerPin = 26;
const int DigitalG2 = G2;
#include <M5Stack.h>
#include <ArduinoMqttClient.h>
#include <WiFi.h>


char ssid[] = "MiFibra-6295";    // your network SSID (name)
char pass[] = "TMJgLKn3";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "iot.smartclosset.org";
int        port     = 1883;
const char topic[]  = "hmaresc/practica/arduino";

const long interval = 1000;
unsigned long previousMillis = 0;

void setup() {
  M5.begin(true, false, false);
  M5.Lcd.setTextSize(3);
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(DigitalG2, OUTPUT);


  //conection to the wifi
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println("You're connected to the network");
  Serial.println();

  //conection to the broker

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  
}

void loop() {
  int cm = ping(TriggerPin, EchoPin);
  //escribir la distancia en el serial
  Serial.print("Distancia: ");
  Serial.println(cm);

  //escribir la distancia en la pantalla
  M5.Lcd.setCursor(30, 10);
  M5.Lcd.print("deteccion de un objeto a : ");
  M5.Lcd.print(cm);
  M5.Lcd.print("  cm ");

  //un tono de voz
  if (cm < 80) {
    digitalWrite(DigitalG2, HIGH);
    M5.Speaker.tone(1500); 
  delay(200);
  M5.Speaker.mute();
   // M5.Lcd.write   
  }
  //escribir la distancia en mqtt
  mqttClient.beginMessage(topic);
    mqttClient.print("Hola");
    mqttClient.print("   ");
    mqttClient.endMessage();


  delay(700);
}

int ping(int TriggerPin, int EchoPin) {
  long duracion, distanciaCm;
  digitalWrite(TriggerPin, LOW); //nos aseguramos señal baja al principio
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH); //generamos pulso de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  duracion = pulseIn(EchoPin, HIGH); //medimos el tiempo del pulso
  distanciaCm = duracion * 10 / 292 / 2; //convertimos a distancia
  return distanciaCm;
}
