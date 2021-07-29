const byte Trig = 7;
const byte Echo = 8;
const byte button = 2;
long tiempoInicial, tiempoFinal; //Medir los 10us
bool button_state = false;
float distancia, tiempo;

void setup() {
  Serial.begin(9600);
  Serial.println("Programa iniciado");
  Serial.println("Esperando boton accionador");
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  attachInterrupt (digitalPinToInterrupt (button), Bandera, FALLING);
  digitalWrite(Trig, LOW);
}

void loop() {
  if (button_state == true){
    Serial.println("Boton accionado");
    /*
   tiempoFinal = 0;
   tiempoInicial = 0;
   while(tiempoFinal-tiempoInicial < 10){ // Crear señal cuadrada de 10us
    digitalWrite(Trig, HIGH);
    tiempoInicial = tiempoFinal;
    tiempoFinal = micros();
   }//fin while
   */
   digitalWrite(Trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trig, LOW);
   tiempo = pulseIn(Echo, HIGH);
   distancia = tiempo/59;
   Serial.print("Distancia: ");
   Serial.println(distancia);
   delay(500);
  }//Fin if
}

void Bandera(){
  if (button_state == true){
    button_state == false;
    Serial.println("Programa Detenido");
  }
  else{
    button_state == true;
  }
}
