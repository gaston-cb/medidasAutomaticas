/*
 * Autor Gaston Valdez 
 * Codigo sobre placa ESP01 
 * Proyecto: medicion automatica de grs/h cañon de ozono 
 * Version 0.1
 * 
*/
#include "ESP8266WiFi.h"
#include "get_and_post.hpp"
#define REDWIFI "O3Z100" 
#define PASSWIFI "" 


void setup() {

  Serial.begin(115200); 
  //WiFi.mode(WIFI_STA);
  conectar_wifi() ;   

}

int timeCount = 0 ; 
void loop() {
 if(WiFi.status() == WL_CONNECTED)
 {
   requestGetString() ; 
 }else {
  conectar_wifi() ;  
 }
 delay(10000); // 10 seg 
 timeCount++ ; 
 if(timeCount == 6){
    Serial.println("sending post" ); 
    sendingPost() ; 
    timeCount  = 0 ; 
 }
}



void conectar_wifi() 
{
  byte timeout_connect = 0 ; 
  IPAddress ip(192, 168, 4, 5);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);  
  WiFi.mode(WIFI_STA); 
//  WiFi.config(ip, gateway, subnet/*, dns1, dns2*/);
  WiFi.begin(REDWIFI,PASSWIFI) ;
  Serial.print("Conectando a:\t");
  Serial.println(REDWIFI);
  
  while (WiFi.status() != WL_CONNECTED && timeout_connect<50) 
  {
    timeout_connect++ ; 
    delay(200);
    Serial.print('.');
  }

  // Mostrar mensaje de exito y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  //Serial.print("s1:") ; Serial.println(s1) ;  
  
} 
