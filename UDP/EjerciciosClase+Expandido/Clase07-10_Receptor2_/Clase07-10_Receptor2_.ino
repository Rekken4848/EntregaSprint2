#include <M5Stack.h>

#define PinGPIO G5
static volatile uint8_t active=0;

void setup() {
  //put your setup code here, to run once:
  //Parametros de begin(bool LCDEnable, bool SDEnable, bool SerialEnable)
  M5.begin(true,false,true);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Pin %d value: ",PinGPIO);
  pinMode(PinGPIO,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinGPIO), blinka, RISING);
    //LOW,CHANGE,FALLING,RISING
}

void blinka()
{
  M5.Lcd.print ("          ROJO");
  active=10;
}

void loop() {
  // put your main code here, to run repeatedly;
  M5.Lcd.setCursor(0, 16);
  if (digitalRead(PinGPIO)){M5.Lcd.print ("ON ");}
  else {M5.Lcd.print ("OFF ");};
  if (active)
  {
    if (active%2) M5.Lcd.fillRect(0, 100, 300, 150, RED);
    else M5.Lcd.fillRect(0, 100, 300, 150, BLACK);
    active--;
  }
  M5.update();
  delay(500);
}
