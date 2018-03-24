// Water Pump Project

#define SERIESRESISTOR 560
#define SENSORPIN A0
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
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
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
}

void loop(void) {
  float reading;

  reading = analogRead(SENSORPIN);
  // Serial.print("Analog reading ");
   Serial.print(reading);

  // convert the value to resistance
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;

  if ((reading > 500) && (reading < 600)) {
    digitalWrite(relayPin, HIGH);   // Turn the relay on (HIGH is the voltage level = 1)
    analogWrite(redPin, 255);
    analogWrite(yellowPin, 0);
    analogWrite(greenPin, 0);
    lcd.setCursor(0,0);
    lcd.print("Pump ON ");
    lcd.setCursor(0,1);
    lcd.print("Water Level: ");
    lcd.print(reading);
    noTone(7);
    delay(2000);
  }

  if (reading < 350) {
    digitalWrite(relayPin, LOW);   // Turn the relay on (HIGH is the voltage level = 1)
    analogWrite(redPin, 0);
    analogWrite(yellowPin, 0);
    analogWrite(greenPin, 255);
    lcd.setCursor(0,0);
    lcd.print("Pump OFF ");
    lcd.setCursor(0,1);
    lcd.print("Water Level: ");
    lcd.print(reading);
    noTone(7);
    delay(1000);
  
  }

  if ((reading < 500) && (reading > 350)) {
    analogWrite(redPin, 0);
    analogWrite(yellowPin, 255);
    analogWrite(greenPin, 0);
    lcd.setCursor(0,0);
    lcd.print("Reading ");
    lcd.setCursor(0,1);
    lcd.print("Water Level: ");
    lcd.print(reading);
    noTone(7);
    delay(1000);

  }


  if (reading > 600) {
    digitalWrite(relayPin, HIGH);   // Turn the relay on (HIGH is the voltage level = 1)
    analogWrite(redPin, 255);
    analogWrite(yellowPin, 255);
    analogWrite(greenPin, 255);
    lcd.setCursor(0,0);
    lcd.print("Pump ERROR ");
    lcd.setCursor(0,1);
    lcd.print("Water Level: ");
    lcd.print(reading);
    for(int i = 200;i <= 800;i++)   //frequence loop from 200 to 800
      {
        tone(7,i);   //in pin7 generate a tone,it frequence is i
        delay(5);    //wait for 5 milliseconds   
      }

    for(int i = 800;i >= 200;i--)  //frequence loop from 800 downto 200
      {
        tone(7,i);  //in pin7 generate a tone,it frequence is i
        delay(5);  //delay 10ms
      }
  }


  lcd.clear();

}
