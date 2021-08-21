//www.elegoo.com
//2018.10.24
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String months[]={ "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };

/*
 * Digital Clock Using the DS1307-module-v03(RTC module) and an LCD
*/

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();
  
  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    
  /*
  Tips:This command will be executed every time when Arduino restarts. 
       Comment this line out to store the memory of DS3231 module
  */

 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
  
}

void loop()
{
    dt = clock.getDateTime();
    int year = dt.year;
    int month = dt.month;
    int day = dt.day;
    int hour = dt.hour;
    int minute = dt.minute;
    int second = dt.second;

  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(year);   Serial.print("-");
  Serial.print(month);  Serial.print("-");
  Serial.print(day);    Serial.print(" ");
  Serial.print(hour);   Serial.print(":");
  Serial.print(minute); Serial.print(":");
  Serial.print(second); Serial.println("");

  delay(1000);

 // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  String currentMonth = months[month-1];

  lcd.print(day);
  lcd.print(" ");
  lcd.print(currentMonth);
  lcd.print(" ");
  lcd.print(year);
  
 //secondLIne
 lcd.setCursor(0, 1);
 lcd.print(hour);
 lcd.print(":");
 lcd.print(minute);
 lcd.print(":");
 lcd.print(second);
}
