/* Programa para el sensor ultrasonico
 * Por: Victor Hugo Flores Vargas
 * Este programa esta hecho para el sensor
 * HC-SR04
 * Toma medidas en centimetros e implementa
 * un boton de paro
 * Fecha: 29-Julio-2021
 */

// Constantes
const byte Trig = 7;
const byte Echo = 8;
const byte button = 2;
const byte ledCerca = 6;
// Variables
long tiempoInicial, tiempoFinal; //Medir los 10us
bool button_state;
float distancia, tiempo;
int i;

void setup() {
  //Iniciamos comunicacion serial
  Serial.begin(9600);
  //Configuramos los pines como E/S
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(button, INPUT);
  pinMode(ledCerca, OUTPUT);
  //Configuramos el pin button como ISR
  attachInterrupt (digitalPinToInterrupt (button), Bandera, FALLING);
  //Iniciamos Trigger como bajo
  digitalWrite(Trig, LOW);
  digitalWrite(ledCerca, LOW);
  //Inicializamos el boton como falso
  button_state = false;
}//Fin void setup

void loop() {
   //Bucle que opera mientras el estado del boton sea true
   while (button_state == true){
      distancia = 0;
      i = 0;
      //Loop para sacar el promedio de 10 distancias
      for(i; i<10; i++){
        //Pulso de 10us para Trigger
        digitalWrite(Trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig, LOW);
        //Lectura del positive duty cycle de la señal Echo
        tiempo = pulseIn(Echo, HIGH);
        //Calculo de la distancia conociendo el tiempo
        distancia = distancia + tiempo/59;
      }
   //Imprimimos por serial la distancia obtenida   
   distancia = distancia/10;
   Serial.print("Distancia: ");
   Serial.print(distancia);
   Serial.println(" cm");
   if (distancia <= 20){
    digitalWrite(ledCerca, HIGH);
   }
   else{
    digitalWrite(ledCerca, LOW);
   }
   delay(500);
   }
}
// Funcion que conmuta el estado de la bandera
void Bandera(){
  if (button_state == true){
    button_state = false;
    Serial.println("Programa Detenido"); //Imprime que el programa se ha detenido
    digitalWrite(ledCerca, LOW);
  }
  else{
    button_state = true;
    Serial.println("Programa Iniciado");
  }
}
