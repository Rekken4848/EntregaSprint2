#include "HX711.h"
#include <M5Stack.h>

const int DOUT=5;
const int CLK=G2;

HX711 balanza;

void setup() {
  M5.begin(true,false,true);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Conexión con M5Stack realizada.");
  Serial.begin(9600);
  balanza.begin(DOUT, CLK);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(195700.00*2); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}

void loop() {
  M5.Lcd.setCursor(0,0);
  Serial.print("Peso: ");
  Serial.print(balanza.get_units(20),3);
  Serial.println(" kg");
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Peso: ");
  M5.Lcd.print(balanza.get_units(20),3);
  M5.Lcd.println(" kg");
  if(balanza.get_units(20) > 0.01){
    M5.Lcd.print("Se te ha caido una prenda");
  }
  M5.update();
  delay(500);
}
