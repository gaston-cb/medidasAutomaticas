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
#include "registros.h"  
#include "horarioUTC.hpp" 
#include "sendingDataGAS.hpp" 
#define IARSSID "iar"
#define PASSWORDWIFI "iarauditorio"    
#define PINCONNECTIAR 2  
#define AMBIENTE1M3 "O3Z103" 
#define AMBIENTE30M3 "O3Z104" 

#define HOURON_O3Z104 
#define HOURON_O3Z102 

struct status_cannon sendesp01{
  0xAB, 
  AMBIENTE1M3,
  false,
  "",
  false,
  false,
  0xAB 
} ; 

extern WiFiClientSecure client ; 
extern unsigned int localPort ; 
extern int hour_day[3] ; 

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
void loop() 
{
  if (Serial.available()){
    
    if (Serial.peek() == 0xAB){
    }else if (Serial.peek() == 0xCD){
    
    }
    
  }else{
      if (millis()-t0>=60000)
      {
         Serial.println("est_red"); 
         if (statusNetworkPlace()==false)
         {
            connectNetwork() ;    
         }
         t0 = millis() ;
      }
      if (millis()-t1>=600000 && obtainHour == true){ 
        t1 = millis() ; 
        waitHour = millis() ; 
        obtainDate();     
        wait = true ; 
      }
      if (millis()-waitHour>=1000 && wait == true){ 
        wait = false ; 
        responseNTP() ; 
      }
      if (hour_day[0]==17 && hour_day[1]>=8){
        Serial.println("30m3") ;  
        obtainHour = false ; 
      }
      if (hour_day[0]==18 && hour_day[1]>=20){
        Serial.println("30m3") ;  
        obtainHour = false ; 
      }
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
