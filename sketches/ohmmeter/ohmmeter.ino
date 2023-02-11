#define KNOWN_RESISTANCE 2200
#define ALARM_RESISTANCE 1000
#define TAMPER_RESISTANCE 2800

void setup() {
Serial.begin(9600); // initialize serial communication at 9600 baud rate
Serial.println("Arduino reset");
}

void loop() {
Serial.println("New scan");

int PIRValue1 = analogRead(A0); // read the voltage at A0
float voltage1 = (PIRValue1 / 1023.0) * 5.0; // calculate the voltage at A0
float resistance1 = KNOWN_RESISTANCE * (5.0 / voltage1 - 1.0);
Serial.print("State PIR1: ");
if (resistance1 <= ALARM_RESISTANCE) {
Serial.println("Normal");
} else if (resistance1 <= TAMPER_RESISTANCE) {
Serial.println("Alarm");
} else {
Serial.println("Tamper");
}

int PIRValue2 = analogRead(A1); // read the voltage at A0
float voltage2 = (PIRValue2 / 1023.0) * 5.0; // calculate the voltage at A0
float resistance2 = KNOWN_RESISTANCE * (5.0 / voltage2 - 1.0);
Serial.print("State PIR2: ");
if (resistance2 <= ALARM_RESISTANCE) {
Serial.println("Normal");
} else if (resistance2 <= TAMPER_RESISTANCE) {
Serial.println("Alarm");
} else {
Serial.println("Tamper");
}

int PIRValue3 = analogRead(A2); // read the voltage at A0
float voltage3 = (PIRValue3 / 1023.0) * 5.0; // calculate the voltage at A0
float resistance3 = KNOWN_RESISTANCE * (5.0 / voltage3 - 1.0);
Serial.print("State PIR3: ");
if (resistance3 <= ALARM_RESISTANCE) {
Serial.println("Normal");
} else if (resistance3 <= TAMPER_RESISTANCE) {
Serial.println("Alarm");
} else {
Serial.println("Tamper");
}

delay(1000); // wait for 1 second
}