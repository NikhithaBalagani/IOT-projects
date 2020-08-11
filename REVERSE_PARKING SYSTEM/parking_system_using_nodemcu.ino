#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "<Your WiFI SSID>";
const char* password = "<Your WiFI Password>";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int data;



 
void setup(void){

  pinMode(D0,INPUT);
 pinMode(D1,INPUT);
 
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", [](){
    page = "<h1>Sensor to Node MCU Web Server</h1><h3>Head_Count:</h3> <h4>"+String(data)+"</h4>";
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
int enter = digitalRead(D0);
  int out = digitalRead(D1);
  
  Serial.print("Enter: ");
  Serial.println(enter);
  delay(500);
  Serial.print("Out: ");
  Serial.println(out);
  
  if(enter == 0 && data>=0)
  {
   
      data++;
  }
  
  if(out == 0 && data>=1)
  {
      data--;
  }
  
  Serial.println(data);


  server.handleClient();
}
