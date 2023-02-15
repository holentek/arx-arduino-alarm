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

// Define the different states of the system
enum State {
  NORMAL_STATE,
  ALARM_STATE,
  TAMPER_STATE,
  ALARM_DELAY_STATE,
  TAMPER_DELAY_STATE
};

State currentState = NORMAL_STATE;
unsigned long alarmStartTime = 0;
unsigned long tamperStartTime = 0;

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

  for (int i = 0; i < 3; i++) { // For balanced PIR sensor input
    PIRValue[i] = analogRead(A0 + i); // read the voltage at A0, A1, and A2
    voltage[i] = (PIRValue[i] / 1023.0) * 5.0; // calculate the voltage at each analog pin
    resistance[i] = KNOWN_RESISTANCE * (5.0 / voltage[i] - 1.0); // calculate ohms at each analog pin

    if (resistance[i] <= ALARM_RESISTANCE) { // Normal state
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
    } else if (resistance[i] <= TAMPER_RESISTANCE) { // Alarm state
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
    } else { // Tamper state
      if (i == 0) {
        leds[0] = CRGB::Yellow;
        leds[1] = CRGB::Yellow;
      } else if (i == 1) {
        leds[3] = CRGB::Yellow;
        leds[4] = CRGB::Yellow;
      } else if (i == 2) {
        leds[6] = CRGB::Yellow;
        leds[7] = CRGB::Yellow;
      tamperTriggered = true;
    }
  }

  FastLED.setBrightness(8);
  FastLED.show();

  // Update the state based on the current inputs and the current state
  switch(currentState) {
    case NORMAL_STATE:
      if (alarmTriggered) {
        digitalWrite(RELAY2, LOW);
        currentState = ALARM_DELAY_STATE;
        alarmStartTime = millis();
      } else if (tamperTriggered) {
        digitalWrite(RELAY3, LOW);
        currentState = TAMPER_DELAY_STATE;
        tamperStartTime = millis();
      }
      break;
    case ALARM_DELAY_STATE:
      if (millis() - alarmStartTime >= 15000) {
        digitalWrite(RELAY2, HIGH);
        currentState = NORMAL_STATE;
      }
      break;
    case TAMPER_DELAY_STATE:
      if (millis() - tamperStartTime >= 10000) {
        digitalWrite(RELAY3, HIGH);
        currentState = NORMAL_STATE;
      }
      break;
    default:
      currentState = NORMAL_STATE;
  }

  delay(100); // wait for 100 milliseconds
}
}