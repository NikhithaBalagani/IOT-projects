#include <ESP8266WiFi.h>;
 
#include <WiFiClient.h>;
 
#include <ThingSpeak.h>;

#define LED0     D3 
//const int buzzer =  4;
 
const char* ssid = "rpi50"; //Your Network SSID
 
const char* password = "123456789"; //Your Network Password
 
int val;
 
int LDRpin = A0; //LDR Pin Connected at A0 Pin
 
 
 
WiFiClient client;
 
unsigned long myChannelNumber = 801687; //Your Channel Number (Without Brackets)
 
const char * myWriteAPIKey = "DU2MVCODBTTLVXO4"; //Your Write API Key
 
void setup()
 
{
 pinMode(LED0 , OUTPUT);

Serial.begin(9600);
 
delay(10);
 
// Connect to WiFi network
 
WiFi.begin(ssid, password);
 
 
 
ThingSpeak.begin(client);
 
}
 
 
 
void loop()
 
{
 
val = analogRead(LDRpin); //Read Analog values and Store in val variable


val=(val*100)/1024; 
if(val<70 && val>100)
{
  digitalWrite(LED0, LOW);
 
  }
else
{
  digitalWrite(LED0, HIGH);

  }
Serial.print(val); //Print on Serial Monitor
Serial.print(".......");
 
delay(3000);
 
ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
 
 
 
delay(100);
}

 
