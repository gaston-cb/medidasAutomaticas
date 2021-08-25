/*
 *  Autor : Gaston Valdez 
 *  Version 0.1 
 *  Programa Wemos d1 Mini 
 *  Envio automatico de datos a google sheets 
 *  Envia datos hasta el endpoint
 *  medianta HTTPS_REDIRECT usando tsl/tls 
 *  
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "sendingDataGAS.hpp" 
#define IARSSID  
#define HOMESSID "" //
#define PASSWORDWIFI    

#define HOURON_O3Z104 
#define HOURON_O3Z102 
extern WiFiClientSecure client ; 



unsigned long int timeRemainingO3Z104 ; 
unsigned long int timeRemainingO3Z102 ; 


void setup() {
  Serial.begin(115200); 
  connectNetwork() ; 
  client.setInsecure() ; 
}
unsigned long int t0 = 0 ; 
void loop() {
  if (millis()-t0>=10000){
    
    Serial.println("10 seg"); 
    sendData() ; 
    t0 = millis() ; 
  }






}

void connectNetwork() {
  int timeout_connect = 0 ;  
  WiFi.mode(WIFI_STA); 
//WiFi.config(ip, gateway, subnet/*, dns1, dns2*/);
  WiFi.begin(IARSSID,PASSWORDWIFI) ;
  Serial.print("Conectando a:\t");
  Serial.println(IARSSID);
  
  while (WiFi.status() != WL_CONNECTED && timeout_connect<50) 
  {
    //timeout_connect++ ; 
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
