int redPin = 5;/* assigning the Arduino pin for red LED*/int greenPin = 4;/* assigning the Arduino pin for green LED*/
int sensorPin = 6; /* assigning the Arduino pin for motion detection sensor*/
int buzzPin = 3; /* assigning the Arduino pin for buzzer */
int val = 0; /*assigning the variables for string the output of the sensor */

void setup() {
  /* assigning  pin mode for the LEDs and sensor */
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buzzPin, OUTPUT);

  Serial.begin(9600);
  digitalWrite(greenPin,HIGH); /* giving the LED a HIGH state */
}
void loop(){
  val = digitalRead(sensorPin);  /* reading the output of the motion sensor*/

  if (val == HIGH) /* if the value is HIGH then */
  {
    digitalWrite(redPin, HIGH);  /* turn on the RED led */
    digitalWrite(greenPin,LOW);/* turn off the green led */
    digitalWrite(buzzPin,HIGH);/* turn on the buzzer alarm */
  }
    if (val == LOW)/* if the output of the sensor is low then */
    {
      digitalWrite(redPin, LOW); /* turn the red led off */
      digitalWrite(greenPin,HIGH);/* turn on  the green led*/
      digitalWrite(buzzPin,LOW);/* turn off the buzzer*/
    }
}