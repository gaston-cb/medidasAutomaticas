#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h> 
#include "configuracion_cannon.hpp" 
//#include "registros.h" 
String str2txt(); // convierte estructura en texto plano separado por espacios en blanco 
void txt2str(String carga_util) ;  // convierte texto en estructura de tipo config_menu 

extern config_menu  registro_configuracion;
struct datos_cannon dataCannonSend{
  0xCD , //initCom 
  0.0,   // ozono_cannon 
  1.0,   // factor_o3 
  0.1,   // co2 
  1.0,   // factorCO2 
  15,    // TEMP  
  25,    // HUMEDAD 
  0xCD,  //endCom 
} ; 




void requestGetString(){
  WiFiClient client ; 
  HTTPClient http;
  String payload_get ; 
  String url = "http://192.168.4.1/estado" ;
  if (http.begin(client, url)) //Iniciar conexión
  {
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();  // Realizar petición 
    if (httpCode > 0) 
    {
       Serial.printf("[HTTP] GET... code: %d\n", httpCode);
       if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
       {
         payload_get = http.getString();   // Obtener respuesta
         Serial.print(payload_get); 
       }
    }else 
    {
       Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } 
    http.end();
   }else 
   {
          Serial.printf("[HTTP} Unable to connect\n");
   }
   // asignar estructura -- 
   txt2str(payload_get) ;  


}


void sendingPost(){
  WiFiClient client ; 
  HTTPClient http;
  // configurar cañon 
  String payload_post = str2txt() ; 
  String url = "http://192.168.4.1/estado" ;
  if (http.begin(client, url)) //Iniciar conexión
  {
    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST(payload_post);  // Realizar petición 
    if (httpCode > 0) 
    {
       Serial.printf("[HTTP] POST... code: %d\n", httpCode);
       if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
       {
         String payload = http.getString();   // Obtener respuesta
         Serial.print(payload); 
       }
    }else 
    {
       Serial.printf("[HTTP]  Post... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } 
    http.end();
   }else 
   {
          Serial.printf("[HTTP} Unable to connect\n");
   }
}


/*
 * Convierte structura a enviar usando post 
 * a texto plano
 *   
*/

String str2txt(){
  //config_cannon_start() -- delay -- config_cannon_start() 
  String datos  ; 
  datos = String(registro_configuracion.date_rtc[5]);
  datos = String(registro_configuracion.date_rtc[4])+" "+datos;
  datos = String(registro_configuracion.date_rtc[3])+" "+datos;
  datos = String(registro_configuracion.date_rtc[2])+" "+datos;
  datos = String(registro_configuracion.date_rtc[1])+" "+datos;
  datos = String(registro_configuracion.date_rtc[0])+" "+datos;
  datos = String(registro_configuracion.factor_CO2)+" "+datos;
  datos = String(registro_configuracion.factor_ozono_sensor)+" "+datos;
  //datos de funcionamiento
  datos = String(registro_configuracion.CO2)+" "+datos;
  datos = String(registro_configuracion.control_ppm)+" "+datos;
  datos = String(registro_configuracion.ozono_sensor)+" "+datos;
  datos = String(registro_configuracion.hora_final[1])+" "+datos;
  datos = String(registro_configuracion.hora_final[0])+" "+datos;  
  datos = String(registro_configuracion.hora_inicial[1])+" "+datos;
  datos = String(registro_configuracion.hora_inicial[0])+" "+datos;
  datos = String(registro_configuracion.humedad)+" "+datos;
  datos = String(registro_configuracion.temperatura)+" "+datos;
  datos = String(registro_configuracion.alarma2)+" "+datos;
  datos = String(registro_configuracion.alarma)+" "+datos;
  datos = String(registro_configuracion.tiempo_comienzo)+" "+datos;
  datos = String(registro_configuracion.tiempo_uso)+" "+datos;
  datos = String(registro_configuracion.hora_fin[1])+" "+datos;
  datos = String(registro_configuracion.hora_fin[0])+" "+datos;
  datos = String(registro_configuracion.hora_inicio[1])+" "+datos;
  datos = String(registro_configuracion.hora_inicio[0])+" "+datos;
  datos = String(registro_configuracion._state_gen)+" "+datos;
  datos = String(registro_configuracion.tiempo_desinfeccion[1])+" "+datos;
  datos = String(registro_configuracion.tiempo_desinfeccion[0])+" "+datos;
  datos = String(registro_configuracion.ppm[1])+" "+datos;
  datos = String(registro_configuracion.ppm[0])+" "+datos;
  datos = String(registro_configuracion._config_select)+" "+datos;  
  return datos ; 
}

/*
 * Convierte texto recibido por get 
 * en structura 
*/
void txt2str (String txt)  {
  config_menu post_rec ; 
  
  char tomo[7];
  int j=0;
  int count=0;
  int dato;
  float flot=0;
  
  for (int i = 0; i <= txt.length()-1; i++){
  
  if(txt[i]!=' '){
    tomo[j]=txt[i];  
    j++;
    }else 
    {
      count++;
      tomo[j]='\0';
      dato = atoi(tomo);  
      flot = atof(tomo);
      j=0;
  
      //--------------------------------------------asignacion en la structura
      switch(count){
        case 1:
        post_rec._config_select=dato;
        break;
        case 2:
        post_rec.ppm[0]=dato;
        break;
        case 3:
        post_rec.ppm[1]=dato;
        break;
        case 4:
        post_rec.tiempo_desinfeccion[0]=dato;
        break;
        case 5:
        post_rec.tiempo_desinfeccion[1]=dato;
        break;
        case 6:
        post_rec._state_gen=dato;
        break;
        case 7:
        post_rec.hora_inicio[0]=dato;
        break;
        case 8:
        post_rec.hora_inicio[1]=dato;
        break;
        case 9:
        post_rec.hora_fin[0]=dato;
        break;
        case 10:
        post_rec.hora_fin[1]=dato;
        break;
        case 11:
        post_rec.tiempo_uso=dato;
        break;
        case 12:
        post_rec.tiempo_comienzo=dato;
        break;
        case 13:
        post_rec.alarma=dato;
        break;
        case 14:
        post_rec.alarma2=dato;
        break;
        case 15:
        post_rec.temperatura=dato;
        break;
        case 16:
        post_rec.humedad=dato;
        break;
        case 17:
        post_rec.hora_inicial[0]=dato;
        break;
        case 18:
        post_rec.hora_inicial[1]=dato;
        break;
        case 19:
        post_rec.hora_final[0]=dato;
        break;
        case 20:
        post_rec.hora_final[1]=dato;
        break;
        case 21:
          post_rec.ozono_sensor=flot;
          break;
        case 22:
        post_rec.control_ppm=flot; 
        break;
        case 23:
        post_rec.CO2=flot; 
        break;
        case 24:
        post_rec.factor_ozono_sensor=flot; 
        break;
        case 25:
        post_rec.factor_CO2=flot; 
        break;
        case 26:
        post_rec.date_rtc[0]=dato; 
        break;
        case 27:
        post_rec.date_rtc[1]=dato; 
        break;
        case 28:
        post_rec.date_rtc[2]=dato; 
        break;
        case 29:
        post_rec.date_rtc[3]=dato; 
        break;
        case 30:
        post_rec.date_rtc[4]=dato; 
        break;
        default :
        break;
        }
     //-------------------------------------------------condicion de finalizacion
      if(i==txt.length()-1)
      {
        tomo[j]='\0';
        dato = atoi(tomo);
        post_rec.date_rtc[5]=dato;  // asignacion del ultimo dato
        j=0;
      }
    }// fin del else  
 
  }//fin del for
  count=0;
  
  registro_configuracion = post_rec ; 
  registro_configuracion.ozono_sensor = 15 ; 
  // asignar valores para enviar al wemos d1 mini 
  dataCannonSend.ozono_cannon = post_rec.ozono_sensor ; 
  dataCannonSend.factor_ozono = post_rec.factor_ozono_sensor ;
  dataCannonSend.co2 =   post_rec.CO2 ; 
  dataCannonSend.factor_co2 =   post_rec.factor_CO2 ;  
  dataCannonSend.temperatura = post_rec.temperatura ; 
  dataCannonSend.humedad = post_rec.humedad ; 

  Serial.println() ; 
  Serial.print("ozono: "); Serial.println(dataCannonSend.ozono_cannon);
  Serial.print("factor_ozono: "); Serial.println(dataCannonSend.factor_ozono);
     
   

}//fin txt2struct
 
