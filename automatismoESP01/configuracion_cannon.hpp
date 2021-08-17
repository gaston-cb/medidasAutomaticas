#include "registros.h" 
struct  config_menu  registro_configuracion{
 11,
  0,        //_config_select 
  {22,25},  // ppm[2] 
  {0,0},      // tiempo_desinfeccion[2]
  0,          //_state_gen  
  {0,0},       // hora_inicio[2]
  {0,0},        // hora_fin[2] 
  0,           //tiempo_uso
  0,          // tiempo comienzo 
  0,          // alarma 
  0,          // alarma2
  0,          //temperatura 
  0,          //humedad  
  {0,0},      //hora inicial 
  {0,0},      // hora final 
  0,        //ozono_sensor 
  0.1,        //control_ppm
  0.2,          //co2  
  0.3,       //factor_ozono
  0.4,       //factor_CO2
  {26,27,28,29,30,31},       //date_rtc     
  11
};


void config_cannon_start()
{
  // modificar registro_configuracion 
}
