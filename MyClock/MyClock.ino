//www.elegoo.com
//2018.10.24
/*
 * Digital Clock Using: 
 * the DS1307-module-v03  
 * an LCD  
 * a DHT11 humidity temperature sensor
*/

#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );


DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String months[]={ "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };


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

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
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

 // set the cursor to column 0, line 1
 // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  String currentMonth = months[month-1];

  if(second==0 || minute==0 || hour==0){
    lcd.clear();
  }

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

 delay(500);

 // humidity stuff
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
    if(second>30 || second<40){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature: ")
      lcd.print(temperature);
      lcd.println(" C");

      lcd.setCursor(0,1);
      lcd.print("Humidity: ")
      lcd.print(humidity);
      lcd.println(" %");
    }
  }

//  lcd.clear();
//  lcd.print(temperature);

  // delay(1000);
}
