#define BLYNK_TEMPLATE_ID "TMPL68h5YWTVG"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "H5iirCfOTD79sSDGQBMbQdSMsuoNEpg6"
#define BLYNK_PRINT Serial
#define DHTPIN 4
#define DHTTYPE DHT11
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "        ";
char pass[] = "        ";

DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t))
  {
    Serial.println("Failed to send from DHT Sensor");
    return;
  }

  String str = String(t, 2);

  Serial.println("Temperature: " + str);

  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);

  delay(1000);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);

  dht.begin();
}

void loop() {
  sendSensor();
  Blynk.run();
}
