#include "DHT.h"
#include "WiFi.h"
#include "WebServer.h"
#include "secret.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



#define DHTPIN 4
#define DHTTYPE DHT11


// Set the LCD address to 0x27 ( found after running a ___ test ) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = WIFI_SSID;
const char* password = PASSWORD;



DHT dht(DHTPIN, DHTTYPE);
//listening from port 80 
WebServer server(80);

/*
I will use an unsigned bit range since later 
on in the code when adding the millis()
function the number it returns only goes
up. Therefore if we were to add a signed
bit then the range would be only from -2.1
billion to +2.1 billion meaning after around
24 days of runtime the comparision logic 
would break. So by adding a unsigned bit, the
value is never negative, so our range would 
be from 0 to about 4.29 billion; therefore 
getting us 49 days of runtime before the 
comparasion logic breaks.
*/

unsigned long lastreading = 0; 


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFi.begin(ssid, password);

Serial.print("Connecting to wifi");

while(WiFi.status() != WL_CONNECTED){
  Serial.print(". ");
  delay(200);
}

Serial.println();
Serial.print("Wifi Connected to: ");
Serial.println(WiFi.localIP());
Serial.println();



Serial.println("Testing DHT Board");
Serial.println();
dht.begin();

Wire.begin(21,22);

// initialize the LCD and printing to test the lcd
	lcd.init();
  lcd.backlight();
 
}

void loop() {
  delay(2000);

  float getHumidityNum = dht.readHumidity();
  float getTempNum = dht.readTemperature();
  if(isnan(getHumidityNum) || isnan(getTempNum)){
    Serial.println("Failed, please check your connections");
  }
  else{
    Serial.print("Temp is ");
    Serial.print(getTempNum);
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(getTempNum);
    lcd.print("C   ");  // reason for spaces is so they overwrite any leftover digits

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(getHumidityNum);
    lcd.print("%     ");

    Serial.print(" | Humidity is ");
    Serial.println(getHumidityNum);
  }
  // put your main code here, to run repeatedly:

}
