// Water Pump Project

#define SERIESRESISTOR 560
#define SENSORPIN A0
#include <Wire.h>

const int tim = 500; //the value of delay time
const int relayPin = 13; //the "s" of relay module attach to
const int redPin = 5;    // select the pin for the red LED
const int yellowPin = 4;
const int greenPin = 6;    // select the pin for the blueLED
const int buzzerPin = 7;//the buzzer pin attach to
int fre;//set the variable to store the frequence value

void setup(void) {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT); //initialize relay as an output
  pinMode(redPin, OUTPUT); //set redPin as OUTPUT
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);//set greenPin as OUTPUT
  pinMode(buzzerPin,OUTPUT);//set buzzerPin as OUTPUT
}

void loop(void) {
  float reading;

  reading = analogRead(SENSORPIN);
  // Serial.print("Analog reading ");
  // Serial.println(reading);

  // convert the value to resistance
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;

  if (reading > 2000) {
    digitalWrite(relayPin, HIGH);   // Turn the relay on (HIGH is the voltage level = 1)
    analogWrite(redPin, 255);
    analogWrite(yellowPin, 0);
    analogWrite(greenPin, 0);
    noTone(7);
    Serial.print(reading);
    Serial.println (" - ON");
    delay(2000);
//    digitalWrite(relayPin, LOW);   // Turn the relay on (HIGH is the voltage level = 1)
//    delay(5000);
  }

  if (reading < 1000) {
    digitalWrite(relayPin, LOW);   // Turn the relay on (HIGH is the voltage level = 1)
    analogWrite(redPin, 0);
    analogWrite(yellowPin, 0);
    analogWrite(greenPin, 255);
    noTone(7);
    Serial.print(reading);
    Serial.println (" - OFF");
    delay(1000);
  
  }

  if ((reading < 2000) && (reading > 1000)) {
    analogWrite(redPin, 0);
    analogWrite(yellowPin, 255);
    analogWrite(greenPin, 0);
    noTone(7);
    Serial.print(reading);
    Serial.println (" - MONITORING");
    delay(1000);

  }

}
