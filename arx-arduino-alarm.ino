#include <FastLED.h>

#define KNOWN_RESISTANCE 2200
#define ALARM_RESISTANCE 1000
#define TAMPER_RESISTANCE 2800
#define LED_PIN 2
#define NUM_LEDS 8
#define RELAY1 4
#define RELAY2 5
#define RELAY3 6
#define RELAY4 7
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
}

void loop() {
  int PIRValue[3];
  float voltage[3];
  float resistance[3];
  bool alarmTriggered = false;
  bool tamperTriggered = false;

  for (int i = 0; i < 3; i++) { //For balanced PIR sensor input
    PIRValue[i] = analogRead(A0 + i); // read the voltage at A0, A1, and A2
    voltage[i] = (PIRValue[i] / 1023.0) * 5.0; // calculate the voltage at each analog pin
    resistance[i] = KNOWN_RESISTANCE * (5.0 / voltage[i] - 1.0); //calculate ohms at each analog pin

    if (resistance[i] <= ALARM_RESISTANCE) { //Normal state
      if (i == 0) {
        leds[0] = CRGB::Green;
        leds[1] = CRGB::Green;
      } else if (i == 1) {
        leds[3] = CRGB::Green;
        leds[4] = CRGB::Green;
      } else if (i == 2) {
        leds[6] = CRGB::Green;
        leds[7] = CRGB::Green;
      }
    } else if (resistance[i] <= TAMPER_RESISTANCE) { //Alarm state
      if (i == 0) {
        leds[0] = CRGB::Red;
        leds[1] = CRGB::Red;
      } else if (i == 1) {
        leds[3] = CRGB::Red;
        leds[4] = CRGB::Red;
      } else if (i == 2) {
        leds[6] = CRGB::Red;
        leds[7] = CRGB::Red;
      }
      alarmTriggered = true;
    } else { //Tamper state
      if (i == 0) {
        leds[0] = CRGB::Yellow;
        leds[1] = CRGB::Yellow;
      } else if (i == 1) {
        leds[3] = CRGB::Yellow;
        leds[4] = CRGB::Yellow;
      } else if (i == 2) {
        leds[6] = CRGB::Yellow;
        leds[7] = CRGB::Yellow;
      }
      tamperTriggered = true;
    }
  }
  FastLED.setBrightness(8);
    FastLED.show();
  
  if (alarmTriggered) {
    digitalWrite(RELAY2, LOW);
    delay(15000);
    digitalWrite(RELAY2, HIGH);
  }

  if (tamperTriggered) {
    digitalWrite(RELAY3, LOW);
    delay(10000);
    digitalWrite(RELAY3, HIGH);
  }

  delay(100); // wait for 100 milliseconds
}