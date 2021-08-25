struct config_menu {
  uint8_t firstbyte; // 99 dec 
  uint8_t _config_select ;  // change from esp8266  
  /************Configuracion Personalizada*****************/ 
  uint8_t ppm[2] ;                  // Partes Por Millon a controlar usando conf personalizada 
  uint8_t tiempo_desinfeccion[2];   // tiempo_desinfeccion[0]: min ,tiempo_desinfeccion[1]: seg  
  /***********Fin Configuracion Personalizada**************/
  uint8_t _state_gen ;   
  /*
   * _state_gen = 0 -- apagado 
   * _state_gen = 1 -- espera 
   * _state_gen = 2 -- generador prendido hasta ppm[] 
   * _state_gen = 3 -- Controlando el tiempo y los ppm prendiendo y apagando el equipo 
   * _state_gen = 4 -- Bajando la concentracion de ozono 
   * _state_gen = 5 -- Señalizacion para permitir entrada de personas   
  */
  uint8_t hora_inicio[2] ;   
  uint8_t hora_fin[2]    ; 
  uint16_t tiempo_uso    ; // if --> time use end --> calculate cant minutes encend 
  // hora de encendido 
  /* Alarmas */
  //char menu456 = 0b00001111
  uint8_t tiempo_comienzo  ; //en minutos, 5 minutos por defecto 
  /*** Alarmas ****/
  uint8_t alarma ;   // tiempo de espera 
  uint8_t alarma2 ;  // tiempo de desinfeccion
  uint8_t temperatura ; 
  uint8_t humedad     ; 
  //configuración de hora para saber hora de prendido y apagado
  //configuracion en modo ozonizador 
  uint8_t hora_inicial[2] ;    //hora_inicial[0]: hora , //hora_inicial[1]: minutos  
  uint8_t hora_final[2]   ;    // idem 
  float ozono_sensor      ; 
  float control_ppm       ;  
  float CO2 ;  
  float factor_ozono_sensor ; 
  float factor_CO2 ; 
  int16_t date_rtc[6] ;        //año,mes,dia, hora, min ,seg                        
  uint8_t lastbyte        ;    // 10 decimal -- 
};


/*
 * init_com and end_com is equal 0xCD
*/
struct datos_cannon{
  uint8_t init_com ; 
  float ozono_cannon ; 
  float co2 ; 
  int temperatura ; 
  int humedad ; 
  uint8_t end_com ; 
} ; 


/*
 * init_com and end_com is equal 0xAB 
*/
struct status_cannon{
  uint8_t init_com ; 
  char name_ssid[10] ;
  bool status_ssid ; 
  char passssid[6] ; 
  bool isConnect ; 
  bool connect_cannon ;  
  uint8_t end_com ; 
  
} ; 
