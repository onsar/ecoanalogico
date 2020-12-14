
#define DEBUG 0

#define BPS 115200
#define RXPIN 12
#define TXPIN 11

// *******************************************************


#include <SoftwareSerial.h>

SoftwareSerial wifiSerialInit (RXPIN,TXPIN);

/*******************************************/
/* Deficnicion de variables *******/
/*******************************************/
String analogicString = ("");
uint8_t numberOfDevices=6;
uint32_t t_last_tx;           // transmision
uint32_t t_last_tm;           // take measurement

struct analogicalMeasure
   {  char name[3];  
      uint8_t pin ;
      float rangeSensor;
      uint16_t numMeasures;
      uint32_t sumMeasures;
   } ;
   
analogicalMeasure am0, am1, am2, am3, am4, am5;

analogicalMeasure *analogicalMeasures[] = {&am0, &am1, &am2, &am3, &am4, &am5};


/*******************************************/
/* Deficnicion de funciones *******/
/*******************************************/
void buildMessageToTx();
void takeAnalogicMeasures();
void resetAnalogicMeasures();
void analogicSensorBegin();


void setup() {
  delay(200);

  Serial.begin(BPS);
  wifiSerialInit.begin(BPS);  // puerto serie al esp12

  // analogicSensorBegin();
  t_last_tx= millis();
  t_last_tm= millis();

  // Referencia de 1,1V
  analogReference(INTERNAL);

  Serial.println("Inciio del microcontrolador");
  delay(100);
}

void loop() {
  uint32_t current_time= millis();
  if (current_time < t_last_tx){t_last_tx = current_time;}
  if (current_time < t_last_tm){t_last_tm = current_time;}
 
  if ((current_time - t_last_tx) > 59000){
    t_last_tx = current_time;
    buildAnalogicMessage();
    if(DEBUG) Serial.print(F("****** t_last_tx - sgs: "));
    if(DEBUG) Serial.println(current_time / 1000);
  }

  if ((current_time - t_last_tm) > 5000){
    t_last_tm = current_time;
    takeAnalogicMeasures();
    if(DEBUG) Serial.print(F("****** t_last_tm - sgs: "));
    if(DEBUG) Serial.println(current_time / 1000);
  }
  
}


/*******************************************/
/* Funciones *******/
/*******************************************/

void analogicSensorBegin(){
  
  am0.name[3]="a0";  am1.name[3]="a1";  am2.name[3]="a2";  am3.name[3]="a3";  am4.name[3]="a4";  am5.name[3]="a5"; 
  am0.pin= 14;       am1.pin= 15;       am2.pin= 16;       am3.pin= 17;       am4.pin= 18;       am5.pin= 19;
  am0.rangeSensor=1; am1.rangeSensor=1; am2.rangeSensor=1; am3.rangeSensor=1; am4.rangeSensor=1; am5.rangeSensor=1;

  resetAnalogicMeasures();
  
  }


void takeAnalogicMeasures(){
  for (uint8_t sen = 0; sen < numberOfDevices; sen++){
    uint16_t sample = analogRead(analogicalMeasures[sen]->pin);    
    analogicalMeasures[sen]->sumMeasures += sample ;
    analogicalMeasures[sen]->numMeasures++ ;
  }
}

void resetAnalogicMeasures(){
  for (uint8_t sen = 0; sen < numberOfDevices; sen++){ 
    analogicalMeasures[sen]->sumMeasures = 0 ;
    analogicalMeasures[sen]->numMeasures = 0 ;
  }
}


void buildAnalogicMessage(){
  String message_to_tx ="";
  
  if(DEBUG) Serial.print(F("**** build_analogic_message() "));

  for (uint8_t sen = 0; sen < numberOfDevices; sen++){    
    String name_18 = analogicalMeasures[sen]->name ; 
    
    float value_float = float(analogicalMeasures[sen]->sumMeasures*analogicalMeasures[sen]->rangeSensor/analogicalMeasures[sen]->numMeasures)/1024;
    String value_18 = String(value_float,1);

    message_to_tx += name_18 + ":" + value_18 ;
    if (sen < (numberOfDevices -1)) {message_to_tx +=",";}
    
    if (DEBUG) Serial.print(F("device number= "));
    if (DEBUG) Serial.println(sen); 
    if (DEBUG) Serial.println(name_18 + ":" + value_18);  
  
  }
  if (message_to_tx != "") { wifiSerialInit.println (message_to_tx);}
  resetAnalogicMeasures();
  delay(10);
  if(DEBUG) {Serial.println(message_to_tx);delay(100);} 
}
