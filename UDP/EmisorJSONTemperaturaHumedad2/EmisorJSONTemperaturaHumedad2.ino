#include "WiFi.h"
#include "AsyncUDP.h"
#include <DHT.h>

#define SENSOR G2
int temp, humedad;

DHT dht (SENSOR, DHT22);

const char * ssid = "TP-LINK_6CAE";
const char * password = "41422915";

AsyncUDP udp;
void setup()
{
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }

  if (udp.listen(1234)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.write(packet.data(), packet.length());
      Serial.println();
    });
  }
}

int medirTemperatura()
{
  return temp = dht.readTemperature();
}

int medirHumedad()
{
  return humedad = dht.readHumidity();
}

void loop()
{
  char texto[200];
  sprintf (texto, "%d : %d" , medirTemperatura(), medirHumedad());
  sprintf (temp, "%d", medirTemperatura());
  sprintf (humedad, "%d", medirHumedad());

  udp.broadcastTo(texto, 1234); //se envía por el puerto 1234
  //como texto

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("ºC Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
  delay(2000);
}
