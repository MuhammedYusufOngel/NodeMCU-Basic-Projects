/*
  This program make two options separately. It provides blink led with manual or automatic.
  When you press the button in manual mode, it causes the LED to light up within 10 seconds.
  In automatic mode, you need to set the timer to make the LED turn on at the time you want. And at the time, your LED light up within 10 seconds. 
*/

#define BLYNK_TEMPLATE_ID "TMPL6odN7wwpa"
#define BLYNK_TEMPLATE_NAME "ManuelAndAuto"
#define BLYNK_AUTH_TOKEN "dzCIq3bPMWTFdVnNTmFNWMCx5OIpUAxg"
#define BLYNK_PRINT Serial

#define buttonPin D2
#define ledPin D1

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUdp;
const long utcOffsetInSeconds = 10800;
NTPClient timeClient(ntpUdp, "asia.pool.ntp.org", utcOffsetInSeconds);

char ssid[] = "DIRILIS";
char pass[] = "B8A7M6S5I4A3L2P1";

int startTime = 0;
bool buttonActiveControl = false;
bool timeActiveControl = false;

BLYNK_WRITE(V0) {
  if(param.asInt() == 1)
  {
    buttonActiveControl = true;
    Serial.println("Automatic mode is activated.");
  }
  
  else
  {
    buttonActiveControl = false;
    Serial.println("Automatic mode isn't active.");
  }
}

BLYNK_WRITE(V1) {
  if(param.asInt() == 1)
  { 
    timeActiveControl = true;
    Serial.println("Manuel mode is activated.");
  }
  else
  {
    timeActiveControl = false;
    Serial.println("Manuel mod isn't active.");
  }
}

BLYNK_WRITE(V2) {
  if(timeActiveControl) {
    startTime = param.asInt();

    if(startTime == 0)
      startTime = 99999;

    Serial.print("Start Time: ");
    Serial.println(startTime);
    Serial.print("End Time: ");
    Serial.println(startTime + 10);
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  
  timeClient.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  if(buttonActiveControl) {
    if(digitalRead(buttonPin) == LOW)
    {
      digitalWrite(ledPin, HIGH);
      delay(10000);
    }

    else
      digitalWrite(ledPin, LOW);

  }
  if(timeActiveControl){
    timeClient.update();

    int HH = timeClient.getHours();
    int MM = timeClient.getMinutes();
    int SS = timeClient.getSeconds();

    int serverTime = 3600 * HH + 60 * MM + SS;
    Serial.print("Live Time: ");
    Serial.println(serverTime);
    delay(1000);

    if(startTime == serverTime) {
      digitalWrite(ledPin, HIGH);
    }

    if(startTime + 10 == serverTime) {
      digitalWrite(ledPin, LOW);
    }
  }

  Blynk.run();
}
