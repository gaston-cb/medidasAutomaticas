#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define HTTPS_PORT 443 
#define GAS_ID "AKfycbyycpVu9hx9QnDmKM9sNan4nTEe4TxaCqORaBgMCL70tegk0ETl" 


WiFiClientSecure client ; 


void sendData() {
  const char *host = "script.google.com" ; 
  const int httpsPort = HTTPS_PORT ;
 // const String Gid = GAS_ID ;  
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
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
        
  Serial.println("request sent");
 
  //----------------------------------------Checking whether the data was sent successfully or not
  Serial.println("line: "); 
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r"){
      Serial.println("break");
      break ;  
    }
  }
 
  String line = client.readStringUntil('\n');
  Serial.print("reply was : ");
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
} 
