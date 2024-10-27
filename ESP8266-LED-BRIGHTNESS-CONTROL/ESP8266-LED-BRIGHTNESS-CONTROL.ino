#define BLYNK_TEMPLATE_ID "         " // Your Blynk Template Id
#define BLYNK_TEMPLATE_NAME "           " // Your Blynk Template Name
#define BLYNK_AUTH_TOKEN "            " // Your Blynk Auth Token
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "         "; //Your WiFi Name
char pass[] = "         "; //Your WiFi Password

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();

  analogWrite(D1, pinValue);
  
  Blynk.virtualWrite(V1, pinValue);
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
}

void setup() {
  
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);

}

void loop() {
  Blynk.run();
}
