/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Akash/IoTCamp2023/Lab8/src/Lab8.ino"
#include "env.h"

#include "oled-wing-adafruit.h"
#include "blynk.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"

void setup();
void loop();
void proximityChangeLEDs();
void betterDisplaySetup();
void betterDelay(int time);
#line 7 "c:/Users/Akash/IoTCamp2023/Lab8/src/Lab8.ino"
#define VCNL 0x60
#define BLUE_LED D7
#define YELLOW_LED D6
#define GREEN_LED D5

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
VCNL4040 proximitySensor;

bool buttonPressed = false;
bool aPushSent = false;
bool bPushSent = false;
bool cPushSent = false;
int proximityValue = 0;
int lightLevel = 0;
// setup() runs once, when the device is first turned on.
void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN);
  display.setup();
  Wire.begin();
  Serial.begin(9600);
  while (!Serial.isConnected()) {}
  display.clearDisplay();
  display.display();
  proximitySensor.begin();
  proximitySensor.powerOnAmbient();
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  Blynk.run();
  display.loop();
  uint16_t lightValue = proximitySensor.getAmbient();
  uint16_t proximityValue = proximitySensor.getProximity();
  Serial.println("work :(");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (proximityValue < 5)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
  else if (proximityValue >= 5 && proximityValue < 300)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }

  if (display.pressedA())
  {
    aPushSent = !aPushSent;
  }
  if (aPushSent)
  {
    if (bPushSent) {}
    else {
      display.clearDisplay();
      display.setCursor(0, 0);
    }
    display.println("Proximity: " + String(proximityValue));
  }
  if (display.pressedB())
  {
    bPushSent = !bPushSent;
  }
  if (bPushSent)
  {
    if (aPushSent) {}
    else {
      display.clearDisplay();
      display.setCursor(0, 0);
    }
    display.println("Light: " + String(lightValue));
  }
  if (display.pressedC())
  {
    cPushSent = !cPushSent;
  }
  if (cPushSent)
  {
    display.clearDisplay();
    if (aPushSent) {
      Blynk.virtualWrite(V3, proximityValue);
      Blynk.virtualWrite(V5, 1);
    }
    if (bPushSent) {
      Blynk.virtualWrite(V2, lightValue);
      Blynk.virtualWrite(V4, 1);
    }
  } 
  if (!cPushSent) {
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V2, 0);
  }
  display.display();
}

BLYNK_WRITE(V0)
{
  Serial.println("Button Tapped");
  if (param.asInt() == 1)
  {
    Blynk.logEvent("notifyPhone", "Hey, Blynk push here!");
  }
}

void proximityChangeLEDs()
{
  if (proximityValue < 5)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }
  else if (proximityValue >= 5 && proximityValue < 300)
  {
    display.println("green");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
  }
  else
  {
    display.println("yellow");
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}

void betterDisplaySetup() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
}

void betterDelay(int time) { // makes delay run the 2 important functions every 100 milliseconds
  int timePerSegment = 100; 
  for (int passedTime = 0; passedTime < time + 1; passedTime += timePerSegment) {
    display.loop();
    Blynk.run();
    delay(timePerSegment);
  }
}