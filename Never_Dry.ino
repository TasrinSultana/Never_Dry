#include <LiquidCrystal.h>
#include <Servo.h>

Servo waterPipe; // create servo object to control a servo

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//For LM35 Temperature sensor
float temp;
int tempPin = A0;

//For rain sensor
int rain;
int rainPin = A1; // connect rain sensor on A1

//For soil moisture sensor
int humidity;
int moistPin = A2; // connect soil moisture sensor on A2

void setup() {
  waterPipe.attach(9); // Attaches servo motor on digital pin 9
  waterPipe.write(0); //Keep the waterpipe on 0 degree angle first
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("STARTING");
}

void loop() {

  // to determine temperature
  lcd.setCursor(0,0);
  temp = analogRead(tempPin);
  temp = temp * 0.48828125;
  lcd.print("TEMP = ");
  lcd.print(temp);
  lcd.print("C");
  delay(1000);

  // reads value from rain and moisture sensor
  rain = analogRead(rainPin);
  humidity = analogRead(moistPin);

  // If it rains, nothing to do
  if(rain > 400)
  {
    lcd.setCursor(0, 1);
    lcd.print("It's raining...");
    delay(1000);
    lcd.clear();
  }

  // If not raining, but the soil is moist, then nothing to do also
  else if(humidity > 400)
  {
    lcd.setCursor(0, 1);
    lcd.print("Soil too moist");
    delay(1000);
    lcd.clear();
  }

  /* 
   *  It's not raining and the soil is not moist 
   *  but the temperature is greater than 25C, then
   *  lower the pipe to water the plant.
   *  After 7 second, lift up the pipe,
   *  and the plant is now watered successfully :)
  */
  else if(temp > 25)
  { 
    waterPipe.write(135);
    lcd.setCursor(0,1);
    lcd.print("Watering..");
    delay(7000); // Water for 7 seconds.
    
    lcd.setCursor(0,1);
    lcd.print("Done... :)");
    waterPipe.write(0);
    delay(15); //wait to set the pipe in the right place again
  }

  else
  {
    lcd.setCursor(0,1);
    lcd.print("Plant is safe :)");
  }
}