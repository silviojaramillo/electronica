#include <Arduino.h>

//codigo para los pulsadores 
const int input1 = 13; // Botón asignado en el pin 2.
int   backImput1;      // guardamos el estado anterior.
int   stateImput1;        // el estado del botón.
unsigned long tempInput1;
unsigned long timeImput1 = 50;

//Declarando variables globales
int outputC = 26;
int outputD = 27;
int inputA = 22;
int inputB = 23;
//¿Quién sale por C y D
int outputtingC = 0;
int outputtingD = 0;
//Función para controlar el paso o corte de electricidad
void enableInt(float inputValueT, float inputValueC, int outputValue){
  if(inputValueT <= 5 && inputValueC < 1){
    return digitalWrite(outputValue, HIGH);
  }else{
    return digitalWrite(outputValue, LOW);
  }
}
//Función para medir corriente
float measureCurrent(int inputSensor){
  return inputSensor*4/1023;
}
//Función para medir tensión
float measureVoltage(int inputSensor){
  return inputSensor*4/1023;
}
//Encender o apagar leds
void onLeds(float measure, int valueLed){
  if (measure > 1){
    return digitalWrite(valueLed,HIGH);
  }else{
    return digitalWrite(valueLed,LOW);
  }
}

//configurando las entradas y salidas a usar en el proyecto
void setup() {
  pinMode(input1,INPUT_PULLUP);
  stateImput1 = HIGH;
  backImput1 = HIGH;

  /* Primera fase del proyecto */
  // Leyendo las corrientes IA e IB
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  //Leyendo las tensiones VA y VB
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  //Permitir el paso de corriente si V < 5 V e I < 1 A a la entrada
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  // Encender led para VA y VB superior a 1 V
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  /* Segunda fase del proyecto */
  //Parte de control
  //Salida C
  pinMode(26,OUTPUT);
  //Salida D
  pinMode(27,OUTPUT);
  /* Tercera fase del proyecto */
  //Midiendo las corrientes en las salidas IC e ID
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  //Midiendo las tensiones en las salidas VC y VD
  pinMode(A7,INPUT);
  pinMode(A8,INPUT);
  //Permitir el paso de corriente si V < 5 V e I < 1 A a la salida
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  // Encender led para VC y VD superior a 1 V
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);

  //Leer los pulsadores

  //Comunicación serial
  Serial.begin(9600);
}

//Permitir la salida por solo un canal
void enableOutput(int whoInput, int whatOutput){
  if(whatOutput == outputC && digitalRead(outputC) == LOW){
    outputtingC = whoInput;
    Serial.println("A");
    return digitalWrite(outputC,HIGH);
  }else if(whatOutput == outputC && digitalRead(outputC) == HIGH){
    digitalWrite(outputtingC,LOW);
    Serial.println("B");
    return digitalWrite(outputC,HIGH);
  }else if(whatOutput == outputD && digitalRead(outputD) == LOW){
    outputtingD = whoInput;
    Serial.println("C");
    return digitalWrite(outputD,HIGH);
  }else if(whatOutput == outputD && digitalRead(outputD) ==HIGH){
    digitalWrite(outputtingD,LOW);
    Serial.println("D");
    return digitalWrite(outputD,HIGH);
  }
  Serial.println("Soy la función que controla las salidas");
}

//Funcion para las pulsaciones
void pulseButtom(int numberPin, int statePin, int backPin, unsigned long temp, unsigned long timePulse, int inputValue, int outputValue){
  // Si el estado es igual a lo leido, la entrada no ha cambiado lo que
  // significa que no hemos apretado el botón (ni lo hemos soltado); asi que
  // tenemos que parar el temporizador.
  if (statePin==digitalRead(numberPin) ) {
    temp = 0;
  }
  
  // Si el valor distinto significa que hemos pulsado/soltado el botón. Ahora
  // tendremos que comprobar el estado del temporizador, si vale 0, significa que
  // no hemos guardado el tiempo en el que sa ha producido el cambio, así que 
  // hemos de guardarlo.
  else if ( temp == 0 ) {
    // El temporizador no está iniciado, así que hay que guardar
    // el valor de millis en él.
    temp = millis();
  }
  // El temporizador está iniciado, hemos de comprobar si el
  // el tiempo que deseamos de rebote ha pasado.
  else if ( millis()-temp > timePulse ) {
    Serial.println("Soy else if dentro de milis - temp > timepulse");
    // Si el tiempo ha pasado significa que el estado es lo contrario
    // de lo que había, asi pues, lo cambiamos.
    statePin = !statePin;
  }

  // Ya hemos leido el botón, podemos trabajar con él.
  if ( backPin==HIGH && statePin==LOW ){
    Serial.println("Me estoy ejecuntando en la función pulsebottom");
    enableOutput(inputValue,outputValue);
  }

  // Recuerda que hay que guardar el estado anterior.
  backPin = statePin;
}
void loop() {
  pulseButtom(13,stateImput1,backImput1,tempInput1,timeImput1,inputA,outputC);
}