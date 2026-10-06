#include "DHT.h"
#include "WiFi.h"
#include "WebServer.h"
#include "secret.h"

#define DHTPIN 15
#define DHTTYPE DHT11
#define WIFI_SSID "your_ssid_here"
#define PASSWORD "your_password_here"


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

WiFi.begin();
bool check = config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000);
if(check){
  Serial.println("Hosting was sucessful.");
}
else{
  Serial.println("Website failed loading.");
}

Serial.println("Testing DHT Board");
Serial.println();
dht.begin();

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
    Serial.print(" | Humidity is ");
    Serial.println(getHumidityNum);
  }
  // put your main code here, to run repeatedly:

}
