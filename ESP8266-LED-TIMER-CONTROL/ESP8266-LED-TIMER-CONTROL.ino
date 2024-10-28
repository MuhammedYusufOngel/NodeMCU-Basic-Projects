/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

#define BLYNK_TEMPLATE_ID "       " //Your Blynk Template Id
#define BLYNK_TEMPLATE_NAME "         " //Your Blynk Template Name
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_AUTH_TOKEN "            "  //Your Blynk Auth
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

char ssid[] = "         "; //Your wifi name
char pass[] = "         "; //Your wifi password

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 10800;  //UTC difference (My country difference +3)
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

int pin = 5; //GPIO5 = D1

int startTime;
int endTime;

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(pin, OUTPUT);

  timeClient.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V1)
{
  startTime = param[0].asInt();
  endTime = param[1].asInt();
  if(startTime == 0 && endTime == 0)
  {
    startTime = 99999;
    endTime = 99999;
  }

  Serial.println(startTime);
  Serial.println(endTime);
}

void showSomething(int thing)
{
  Serial.print("------");
  Serial.println(thing);
  delay(1000);
}


void loop() {
  timeClient.update();

  int HH = timeClient.getHours();
  int MM = timeClient.getMinutes();
  int SS = timeClient.getSeconds();

  int serverTime = 3600 * HH + 60 * MM + SS;

  showSomething(serverTime);

  if(startTime == serverTime)
  {
    digitalWrite(pin, HIGH);
  }

  if(endTime == serverTime)
  {
    digitalWrite(pin, LOW);
  }

  Blynk.run();
}