#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define HTTPS_PORT 443 
#define GAS_ID 

WiFiClientSecure client ; 



void sendData() {
  const char *host = "script.google.com" ; 
  const int httpsPort = HTTPS_PORT ;
  String send_sps = "0.32,224,100,88"; 
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  //----------------------------------------Processing data and sending data
  String url = "/macros/s/" + String(GAS_ID) + "/exec" ;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "Content-Type: text/plain \r\n"+
         "Content-Length:"+ String(send_sps.length()) + 
         "\r\n\r\n"+
         send_sps) ; 
        
  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r"){
      break ;  
    }
  }
 
  String line = client.readStringUntil('\n');
} 
