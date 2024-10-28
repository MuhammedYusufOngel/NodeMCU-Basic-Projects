#define BLYNK_TEMPLATE_ID "       "
#define BLYNK_TEMPLATE_NAME "         " 
#define BLYNK_AUTH_TOKEN "          "
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int segmentG = 12;   //D6
const int segmentF = 14;  //D5
const int segmentE = 2;  //D4
const int segmentD = 0;  //D3
const int segmentC = 4;  //D2
const int segmentB = 5;  //D1
const int segmentA = 16;  //D0
const int segmentPoint = 13;  //D7

//This function provides that we don't need write these codes again to show number
void writeNumber(uint8_t g, uint8_t f, uint8_t e, uint8_t d, uint8_t c, uint8_t b, uint8_t a)
{
	digitalWrite(segmentG,g);
	digitalWrite(segmentF,f);
	digitalWrite(segmentE,e);
	digitalWrite(segmentD,d);
	digitalWrite(segmentC,c);
	digitalWrite(segmentB,b);
	digitalWrite(segmentA,a);
	digitalWrite(segmentPoint, HIGH);
}

void displayNumber(int number)
{
  if(number == -1)
  {
    writeNumber(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  if(number == 0)
  {
    writeNumber(HIGH, LOW, LOW, LOW, LOW, LOW, LOW);
  }

  if(number == 1)
  {
    writeNumber(HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH);
  }

  else if(number == 2)
  {
    writeNumber(LOW, HIGH, LOW, LOW, HIGH, LOW, LOW);
  }

  else if(number == 3)
  {
    writeNumber(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW);
  }

  if(number == 4)
  {
    writeNumber(LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH);
  }

  if(number == 5)
  {
    writeNumber(LOW, LOW, HIGH, LOW, LOW, HIGH, LOW);
  }

  else if(number == 6)
  {
    writeNumber(LOW, LOW, LOW, LOW, LOW, HIGH, LOW);
  }

  else if(number == 7)
  {
    writeNumber(HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW);
  }

  else if(number == 8)
  {
    writeNumber(LOW, LOW, LOW, LOW, LOW, LOW, LOW);
  }

  else if(number == 9)
  {
    writeNumber(LOW, LOW, HIGH, LOW, LOW, LOW, LOW);
  }
}

char ssid[] = "           "; //Your wifi name
char pass[] = "           "; //Your wifi password
int receivedNumber = 0;
String receivedText = "";

BLYNK_WRITE(V0)
{
  receivedNumber = param.asInt();
  displayNumber(receivedNumber);
  Serial.print("Received Number: ");
  Serial.println(receivedNumber);
}

BLYNK_WRITE(V1)
{
  receivedText = param.asStr();
  Serial.print("Received Text: ");
  Serial.println(receivedText);
}

void setup() {
  Serial.begin(9600);
  pinMode(segmentA, HIGH);
  pinMode(segmentB, HIGH);
  pinMode(segmentC, HIGH);
  pinMode(segmentD, HIGH);
  pinMode(segmentE, HIGH);
  pinMode(segmentF, HIGH);
  pinMode(segmentG, HIGH);
  pinMode(segmentPoint, HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
