#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
 //definiciones de modulo RTC i2c y archivo sd
// RTC_DS1307 rtc;
RTC_DS1307 rtc;
//archivo txt
File myFile; 
//arreglo de tiempos 
int tiempos[4];
int count=0; 
int valor=0; 
void setup() {
   Serial.begin(9600);
   //inicializar pines de salida de semaforos
    for(int i=2;i<=13;i++){
    pinMode(i,OUTPUT);
    }
  //verificar que esta en linea el modulo RTC  
  if (!rtc.begin()) {
      Serial.println("No se encuentra el modulo RTC");
      return;
   }
   Serial.print("Inicializando SD...");
   //verificar si esta en linea la SD
  if (!SD.begin(53)) {
    Serial.println("Inicializacion fallida!");
    return;
  }
  //apertura de archivo txt
  Serial.println("Inicializacion SD terminada.");
  myFile = SD.open("test.txt", FILE_WRITE);

// leer archivo de configuracion de tiempos
    myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Tiempos definidos para esta configuracion: ");
    Serial.println("1. Tiempo en verde de norte a sur");
    Serial.println("2. Tiempo en rojo de norte a sur");
    Serial.println("3. Tiempo en verde de este a oeste");
    Serial.println("4. Tiempo en rojo de este a oeste");
    //ciclo while que carga en pantalla los tiempos de semaforo y carga los tiempos a memoria
   
    
    while (myFile.available()) {
      //Serial.write(myFile.read());
      valor=myFile.parseInt();
      Serial.println(valor);
      tiempos[count]=valor;
      count++;
    }
    myFile.close();
  } else {
    Serial.println("Error abriendo el archivo .txt");
  }

  
}

void nortsurHpico(){
  
  //VERDE NORTE SUR
  digitalWrite(11,HIGH);
  digitalWrite(2,HIGH);
   //ROJO ESTE OESTE
  digitalWrite(10,HIGH);
  digitalWrite(5,HIGH);
  delay(tiempos[0]*1000);
  digitalWrite(11,LOW);
  digitalWrite(2,LOW);
  
  //AMARILLO NORTE SUR
  digitalWrite(12,HIGH);
  digitalWrite(3,HIGH);
  delay(500);
   digitalWrite(12,LOW);
  digitalWrite(3,LOW);
  delay(500);
   digitalWrite(12,HIGH);
  digitalWrite(3,HIGH);
  delay(500);
  digitalWrite(12,LOW);
  digitalWrite(3,LOW);
  delay(500);
    digitalWrite(12,HIGH);
  digitalWrite(3,HIGH);
  delay(500);
    digitalWrite(12,LOW);
  digitalWrite(3,LOW);
  delay(500);
  
  //SE APAGA ROJO ESTE OESTE
  digitalWrite(10,LOW);
  digitalWrite(5,LOW);

   
  //ROJO NORTE SUR
digitalWrite(13,HIGH);
  digitalWrite(4,HIGH);
    //VERDE ESTE OESTE
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
   delay(tiempos[2]*1000);
// SE APAGA VERDE ESTE OESTE
 digitalWrite(8,LOW);
  digitalWrite(7,LOW);
   
    //AMARILLO ESTE OESTE
digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
  delay(500);
   digitalWrite(9,LOW);
  digitalWrite(6,LOW);
  delay(500);
   digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
  delay(500);
  digitalWrite(9,LOW);
  digitalWrite(6,LOW);
  delay(500);
    digitalWrite(9,HIGH);
  digitalWrite(6,HIGH);
  delay(500);
    digitalWrite(9,LOW);
  digitalWrite(6,LOW);
  delay(500);
    
  //SE APAGA ROJO NORTE SUR
  digitalWrite(13,LOW);
  digitalWrite(4,LOW);
  nortsurHpico();
  }
  void escribir(){
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

    }


void loop() {

   nortsurHpico();
 
}
