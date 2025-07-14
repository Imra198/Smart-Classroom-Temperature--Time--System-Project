
// create the necessary libraries that help in building up the project
#include <Wire.h> // used by RTC for I2C communication
#include "RTClib.h"// provides functions for DS1307 RTC
#include "DHT.h"// allows to read temperature from DHT11 sensor
#include <LiquidCrystal.h>// controls LCD

// LCD setup (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// RTC and DHT setup
RTC_DS1307 rtc;//allows to create RTC object
#define DHTPIN 6 // Connect DHT11 data to pin 6
#define DHTTYPE DHT11 //uses DHT11
DHT dht(DHTPIN, DHTTYPE);//creates DHT sensor objects of the above settings

// Alert pins
#define BUZZER_PIN 8 //connected to 8
#define LED_PIN 7 // alert led temp connected to 7
#define NORMAL_LED 9 // normal led temp connected to 9

// Day names
const char* daysOfTheWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

//set up the LCD,DHT sensor,RTC and serail monitor so that the arduino can begin showing na displaying the devices
void setup() {
  lcd.begin(16, 2);      
  dht.begin();           
  Wire.begin();          
  Serial.begin(9600);

//sets up the output modes for the buzzer and two LEDs, so the Arduino can turn them off or on depending on the suitation
  pinMode(BUZZER_PIN, OUTPUT);//set buzzer pin as an output 
  pinMode(LED_PIN, OUTPUT);//set LED pin as an output
  digitalWrite(BUZZER_PIN, LOW);// allows to turn of the buzzer
  digitalWrite(LED_PIN, LOW);// allows to turn off LED
  pinMode(NORMAL_LED, OUTPUT);//set LED pin as an output
  digitalWrite(NORMAL_LED, LOW);//turns off LED

// start up the RTC modules to enusre its running, should print RTC not found and displayed on lcd if theres an error
//but if its running well it should set the current date and time

  if (!rtc.begin()) { // starts RTC
    lcd.print("RTC not found");
    Serial.println("RTC not found");
    while (1);//stop if RTC not Found
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// sets the current time
  }
}

void loop() {
 // get current time and temperature and clear the LCD screen so it can display updated data
  DateTime now = rtc.now();
  float tempC = dht.readTemperature();

  lcd.clear();// clears the display before updating

  // the code will display the hour in 12 hourclock time which is done by converting 24 hour time to 12 hoursindicating Am/Pm on the LCD 
  //it will also if the time is over 12 then its pm but if its below or = 12 then its am
  lcd.setCursor(0, 0);// prints from the top row
  int displayHour = now.hour() % 12; 
  if (displayHour == 0) displayHour = 12;
  bool isPM = now.hour() >= 12; 

// LCD will display the current day, hour in digit format, current minute in 2 digit format but should be less than 10 and p or a depending on time
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);// displays the name of current day
  lcd.print(" ");
  if (displayHour < 10) lcd.print('0'); 
  lcd.print(displayHour);
  lcd.print(':');
  if (now.minute() < 10) lcd.print('0'); 
  lcd.print(now.minute());
  lcd.print(isPM ? "P" : "A");

  // LCD allows the second row to start which will show the current month, day and year 
  lcd.setCursor(0, 1);
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.day()); 
  lcd.print('/');
  lcd.print(now.year() % 100);// prints year
  lcd.print(" "); // prints single charcter on LCD screen

//the code continues to check the correct temperatureture and displays it on th LCD using celicius format 
  if (!isnan(tempC)) {
    lcd.print((int)tempC);//prints tempreature
    lcd.print((char)223); // Degree symbol
    lcd.print("C");//prints celicius 

// add a code to check if the alert is triggered
   static bool alertTriggered = false; // checks if the alert is triggered
   static unsigned long alertStartTime = 0;

//the code will check if temprature is greater or = 30 then the alert is triggered, also it will turn on the red LED and the buzzer sound
if (tempC >= 30 && !alertTriggered) {
   digitalWrite(LED_PIN, HIGH);
  int pitch = 800 + (millis() % 400); 
  tone(BUZZER_PIN, pitch);
  alertStartTime = millis();         
  alertTriggered = true; 

  digitalWrite(NORMAL_LED, LOW);//is turned off during the alert
}
// Normal_LED will be blinking indicating that the room teamperature is safe which is done by checking if temperature is below 30,
//the blinking effect is created by using millisecond and every 0.5 seconds it increases 500. if the previous state was on, the next 0.5 will turn the LED off,
// but if the previous state was off it will turn the LED on in the next o.5 seconds

if(tempC<30){// checks if temp is less than 30
  if (millis()/ 500% 2 == 0) {
    digitalWrite(NORMAL_LED, HIGH);// LED is on for first 0.5 seconds 
  }else {
    digitalWrite(NORMAL_LED, LOW);// LED is off for next 0.5 seconds
  }
}

//the following code deactivates an alert of of buzzer sound and LED every after 1 second and it shows a message if DHT11 sensor radings fails
if (alertTriggered && millis() - alertStartTime >= 1000) {
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
  alertTriggered = false;
}
  } else {
    lcd.print("failed to get DHT11 sensor readings");
  }

  delay(2000);  
}