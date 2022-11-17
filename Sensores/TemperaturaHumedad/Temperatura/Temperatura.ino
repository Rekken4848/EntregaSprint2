#include <DHT.h>
#include <M5Stack.h>

#define SENSOR 26
float temp, humedad;

DHT dht (SENSOR, DHT11);

void setup() {
  M5.begin(true,false,true);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Conexión con M5Stack realizada.");
  M5.Lcd.printf("Pin %d value: ",SENSOR);
  pinMode(SENSOR,INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
 M5.Lcd.setCursor(0,0);

 humedad = dht.readHumidity();
 temp = dht.readTemperature();
 Serial.print("Temperatura: ");
 Serial.println(temp);
 Serial.print("ºC Humedad: ");
 Serial.print(humedad);
 Serial.println("%");

  if (digitalRead(SENSOR)){M5.Lcd.println ("ON ");}
    else {M5.Lcd.println ("OFF ");};
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Temperatura: ");
  M5.Lcd.print(temp);
  M5.Lcd.print("ºC Humedad: ");
  M5.Lcd.print(humedad);
  M5.Lcd.print("%");
  M5.update();
 
 delay(2000);
}
