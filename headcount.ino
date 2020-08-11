#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int pin1=D6;
int pin2=D7;
int count=0;
// Replace with your network credentials
const char* ssid = "PIKAACHU";
const char* password = "pikapika";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
//double data; 
void setup(void){

 // pinMode(A0, INPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  
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
    page = "<h1>Sensor to Node MCU Web Server</h1><h3>Data:</h3> <h4>"+String(count)+"</h4>";
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  //data = analogRead(A0);
  if(digitalRead(pin1)==HIGH)
  count++;
  if(digitalRead(pin2)==HIGH)
  count--;
  delay(1000);
  server.handleClient();
}
