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

#include "horarioUTC.hpp" 
#include "sendingDataGAS.hpp" 
#define IARSSID  
#define PASSWORDWIFI    
#define PINCONNECTIAR 2  
#define HOURON_O3Z104 
#define HOURON_O3Z102 

extern WiFiClientSecure client ; 
extern unsigned int localPort ; 

extern WiFiUDP udp;


void setup() {
  Serial.begin(115200); 
  pinMode(PINCONNECTIAR, OUTPUT);

  connectNetwork() ; 
  
  udp.begin(localPort);
  client.setInsecure() ; 

}
unsigned long int t0 = 0 ; 
unsigned long int t1 = 0 ; 
unsigned long int waitHour = 0 ; 
bool wait = false  ; 
bool obtainHour = true ; 
void loop() {
  if (millis()-t0>=1000){
     if (statusNetworkPlace()==false){
        connectNetwork() ;    
     }
  }else if (millis()-t1>=600000 && obtainHour == true) // 10 minutos 
  {
    waitHour = millis() ; 
    obtainDate();     
    wait = true ; 
  }else if (millis()-waitHour>=1000 && wait == true)
  { 
    wait = false ; 
    
  }


  
} 

void connectNetwork() {
  int timeout_connect = 0 ;  
  WiFi.mode(WIFI_STA); 
//WiFi.config(ip, gateway, subnet/*, dns1, dns2*/);
  WiFi.begin(IARSSID,PASSWORDWIFI) ;  
  while (WiFi.status() != WL_CONNECTED && timeout_connect<20) 
  {
    timeout_connect++ ; 
    delay(200);
  }
  if (timeout_connect == 19){
    digitalWrite(PINCONNECTIAR,HIGH) ; 
    return ; 
  }
  digitalWrite(PINCONNECTIAR,LOW) ; 

}


bool statusNetworkPlace() { 
   if (WiFi.status()==WL_CONNECTED){
     digitalWrite(PINCONNECTIAR,LOW) ; 
     return true ; 
   }else{ 
     digitalWrite(PINCONNECTIAR,HIGH) ;
     return false ; 
   }
}
