#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define SALA 3
#define Q1 5
#define Q2 4
#define LAMP 1

#define R 14
#define G 12
#define B 13
//----------------------------------//
  const char* ssid = "NodeMCU";
  const char* password = "12345678";
  ESP8266WebServer server(80);
//----------------------------------//

void desligar(){
  digitalWrite(SALA, LOW);
  digitalWrite(Q1, LOW);
  digitalWrite(Q2, LOW);
  digitalWrite(LAMP, LOW);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  String message = "{\"status\":\"DESLIGADO!\"}";
  server.send(200, "application/json", message); 
}
void liga(){
  digitalWrite(SALA, HIGH);
  digitalWrite(Q1, HIGH);
  digitalWrite(Q2, HIGH);
  digitalWrite(LAMP, HIGH);
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  String message = "{\"status\":\"LIGADO!\"}";
  server.send(200, "application/json", message); 
}
void rgb() { 

String message = "";

if (server.arg("Red")== "" || server.arg("Blue")== "" || server.arg("Green")== "" ){


analogWrite(R, 0);
analogWrite(G, 0);
analogWrite(B, 0);
message = "{\"status\":\"RBG Apagado!\"}";

}else{

message = "{\"status\":\"RBG Jooj!\"}";


int Red = map(server.arg("Red").toInt(), 0, 255, 0, 1024);
int Green = map(server.arg("Green").toInt(), 0, 255, 0, 1024);
int Blue = map(server.arg("Blue").toInt(), 0, 255, 0, 1024);

analogWrite(R, Red);
analogWrite(G, Green);
analogWrite(B, Blue);

}

server.send(200, "application/json", message);          //Returns the HTTP response

}
void lampada() { 

String message = "";

digitalWrite(LAMP, !digitalRead(LAMP));
if(digitalRead(LAMP) == 0){
  
message = "{\"status\":\"LAMP Apagada!\"}";

}else{

message = "{\"status\":\"LAMP Acesa! \"}";

}
server.send(200, "application/json", message);          //Returns the HTTP response

}

void sala() { 

String message = "";

digitalWrite(SALA, !digitalRead(SALA));
if(digitalRead(SALA) == 0){
  
message = "{\"status\":\"SALA Apagada!\"}";

}else{

message = "{\"status\":\"SALA Acesa! \"}";

}
server.send(200, "application/json", message);          //Returns the HTTP response

}
void q1(){ 

String message = "";

digitalWrite(Q1, !digitalRead(Q1));
if(digitalRead(Q1) == 0){
  
message = "{\"status\":\"QUARTO1 Apagado!\"}";

}else{

message = "{\"status\":\"QUARTO1 Aceso!\"}";

}
server.send(200, "application/json", message);          //Returns the HTTP response

}
void q2(){ 

String message = "";

digitalWrite(Q2, !digitalRead(Q2));
if(digitalRead(Q2) == 0){
  
message = "{\"status\":\"QUARTO2 Apagado!\"}";

}else{

message = "{\"status\":\"QUARTO2 Aceso!\"}";

}
server.send(200, "application/json", message);          //Returns the HTTP response

}
void buitin(){ 

String message = "";

digitalWrite(2, !digitalRead(2));
if(digitalRead(2) == 1){
  
message = "{\"status\":\"Led Apagado!\"}";

}else{

message = "{\"status\":\"Led Aceso!\"}";

}
server.send(200, "application/json", message);          //Returns the HTTP response
}
void setup() {
  Serial.begin(9600);
  delay(10);
  
  //Prepare GPIO3 - SALA
  pinMode(SALA, OUTPUT);
  digitalWrite(SALA, LOW);
  
  //Prepare GPIO5 - QUARTO1
  pinMode(Q1, OUTPUT);
  digitalWrite(Q1, LOW);
  //Prepare GPIO4 - QUARTO1
  pinMode(Q2, OUTPUT);
  digitalWrite(Q2, LOW);

  // Prepare GPIO12, GPIO13, GPIO14
  pinMode(R, OUTPUT);
  analogWrite(R, 0);
  pinMode(G, OUTPUT);
  analogWrite(G, 0);
  pinMode(B, OUTPUT);
  analogWrite(B, 0);
  // prepare GPIO1 - LAMP
  pinMode(LAMP, OUTPUT);
  digitalWrite(LAMP, 0);
  
  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  IPAddress staticIP(192, 168,  4, 2);
  IPAddress gateway (192, 168,  4, 1);
  IPAddress subnet  (255, 255, 255, 0);

  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password, 2, 0);
  WiFi.config(staticIP, gateway, subnet);

  server.begin();

  Serial.println("Server started"); 
  Serial.println(WiFi.softAPIP());

  server.on("/DESLIGA", desligar);
  server.on("/LAMP", lampada);
  server.on("/RGB",    rgb);   
  server.on("/SALA",  sala);   
  server.on("/QUARTO1", q1);   
  server.on("/QUARTO2", q2);
  server.on("/LED", buitin);
  
}

void loop() {
server.handleClient();

}

