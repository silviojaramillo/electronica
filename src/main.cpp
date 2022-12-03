#include <Arduino.h>

//Confioguraciones generales de la subestación
unsigned long timePulse = 50;
bool returnButton;

//Pines para leer las tensiones de las entradas
int voltageA = A0;
int voltageB = A1;

//Pines para leer las corrientes de las entradas
int currentA = A2;
int currentB = A3;

//Pines para leer las tensiones de las salidas
int voltageC = A4;
int voltageD = A5;

//Pines para leer las corrientes de las salidas
int currentC = A6;
int currentD = A7;

//Pines para controlar los relés de las señales de entrada
int inputA = 22;
int inputB = 23;

//Pines para controlar las señales de la salida
int outputAC = 24;
int outputAD = 25;
int outputBC = 26;
int outputBD = 27;

//Variables para guardar los valores de la tensiones de las entradas
double mesureVoltageA;
double mesureVoltageB;

//Variables para guardar los valores de las corrientes de las entradas
float measureCurrentA = 0.0;
float measureCurrentB = 0.0;

//Lista para guardar los estados de los botones
int stateButtons[10] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};

//Lista para guardar los estados de los elementos
int statesInOuts[5] = {LOW,LOW,LOW,LOW,LOW};

//Lista para guardar los tiempos de cada botón
unsigned long timerbuttons[5] = {0,0,0,0,0};

//Definiendo las lecturas de los botones
int button1 = 28;
int button2 = 29;
int button3 = 30;
int button4 = 31;
int button5 = 32;

//Pines para encender leds en las entradas
int ledInputA = 33;
int ledInputB = 34;
int ledOutputAC = 35;
int ledOutputAD = 36;
int ledOutputBC = 37;
int ledOutputBD = 38;

int on = LOW;
int off = HIGH;
//Función para leer la tensión
double measureVoltage(int valuePin){
    double volt = valuePin*10/1023;
    return volt;
}

//Función para leer la corriente
float measureCurrent(int valuePin){
    float amper = 0.0;
    for (size_t i = 0; i < 500; i++){
        amper = amper + ((analogRead(valuePin)*5.0/1023)-2.5)/0.185;
    }
    return amper/500;
    amper = 0.0;
}

//Función para controlar el paso de la corriente en las entradas
int inputControl(int valueV, int valueC){
    int outputFunction;
    if(valueV <= 5 && valueC < 1){
        outputFunction = HIGH;
    }else{
        outputFunction = LOW;
    }
    return outputFunction;
}

//Función para las salidas de las señales
void outputsControl(int buttonPulse){
    //A saliendo por C
    if(buttonPulse == button1){
        digitalWrite(outputBC,off);
        digitalWrite(outputAC,on);
    //A saliendo por D
    }
    if(buttonPulse == button2){
        digitalWrite(outputBD,off);
        digitalWrite(outputAD,on);
    //B saliendo por C
    }
    if(buttonPulse == button3){
        digitalWrite(outputAC,off);
        digitalWrite(outputBC,on);
    //B saliendo por D
    }
    if(buttonPulse == button4){
        digitalWrite(outputAD,off);
        digitalWrite(outputBD,on);
    }
}

//Función para el sensor 1
float measureOne(){
    return 0;
}

//Función para el sensor 2
float measureTwo(){
    return 0;
}

//Función para encender los leds cuando la tensión sea mayor a 1 Volt
void onLed(int mesuare, int controlLed){

    //Encender o apagar led entrada A
    if(mesuare > 1 && controlLed == inputA){
        ledInputA = HIGH;
    }else{
        ledInputA = LOW;
    }

    //Encender o apagar led entrada B
    if(mesuare > 1 && controlLed == inputB){
        ledInputB = HIGH;
    }else{
        ledInputB = LOW;
    }

    //Encender o apagar led salida AC
    if(mesuare > 1 && controlLed == outputAC){
        ledOutputAC = HIGH;
    }else{
        ledOutputAC = LOW;
    }

    //Encender o apagar led salida AD
    if(mesuare > 1 && controlLed == outputAD){
        ledOutputAD = HIGH;
    }else{
        ledOutputAD = LOW;
    }

    //Encender o apagar led salida BC
    if(mesuare > 1 && controlLed == outputBC){
        ledOutputBC = HIGH;
    }else{
        ledOutputBC = LOW;
    }

    //Encender o apagar led salida BD
    if(mesuare > 1 && controlLed == outputBD){
        ledOutputBD = HIGH;
    }else{
        ledOutputBD = LOW;
    }
}

void setup(){

    //Pines analógicos para toma de medidas
    pinMode(voltageA,INPUT);
    pinMode(voltageB,INPUT);
    pinMode(currentA,INPUT);
    pinMode(currentB,INPUT);
    pinMode(voltageC,INPUT);
    pinMode(voltageD,INPUT);
    pinMode(currentC,INPUT);
    pinMode(currentD,INPUT);

    //Pines digitales para control de acciones
    pinMode(inputA,OUTPUT);
    pinMode(inputB,OUTPUT);
    pinMode(outputAC,OUTPUT);
    pinMode(outputAD,OUTPUT);
    pinMode(outputBC,OUTPUT);
    pinMode(outputBD,OUTPUT);
    pinMode(ledInputA,OUTPUT);
    pinMode(ledInputB,OUTPUT);
    pinMode(ledOutputAC,OUTPUT);
    pinMode(ledOutputAD,OUTPUT);
    pinMode(ledOutputBC,OUTPUT);
    pinMode(ledOutputBD,OUTPUT);

    //Declarando los pines para leer las pulsaciones
    pinMode(button1,INPUT_PULLUP);
    pinMode(button2,INPUT_PULLUP);
    pinMode(button3,INPUT_PULLUP);
    pinMode(button4,INPUT_PULLUP);

    //Iniciamos los relés apagados
    digitalWrite(outputAC,on);
    digitalWrite(outputAD,off);
    digitalWrite(outputBC,off);
    digitalWrite(outputBD,on);

    //Entradas
    digitalWrite(inputA,off);
    digitalWrite(inputB,off);


    //Iniciando la comunicación serial
    Serial.begin(9600);
}

//Función para promediar la corriente
float averageCurrent(){
    return 0;
}
void loop(){
    digitalWrite(inputA,on);
    digitalWrite(inputB,on);

    //Se miden las tensiones y corrientes de las entradas
    //mesureVoltageA = measureVoltage(inputA);
    
    
    measureCurrentA = measureCurrent(currentA);
    measureCurrentB = measureCurrent(currentB);
    Serial.println("Corrientes de las entradas A y B ");
    Serial.print(measureCurrentA - 0.5);
    Serial.print("-------");
    Serial.println(measureCurrentB - 0.3);

    //Midiendo la tensión para realizar un ajuste
    //Serial.println(((analogRead(currentA)*5.0/1024)-2.5)/0.185);
    
    //mesureVoltageB = measureVoltage(inputB);
    /* measureCurrentB = measureCurrent(currentB);
    Serial.print("Corriente de la entrada B: ");
    Serial.println(measureCurrentB); */

    //De acuerdo a las lecturas se permite o no el paso de la corriente
    inputA = inputControl(mesureVoltageA,measureCurrentA);
    inputB = inputControl(mesureVoltageB,measureCurrentB);

    //Se enciende los leds que indican la presencia de tensión en las entradas
    onLed(mesureVoltageA,inputA);
    onLed(mesureVoltageB,inputB);

    //Se realiza la acción
    if (digitalRead(button1) == LOW){
        outputsControl(button1);
    }else if(digitalRead(button1) == HIGH){
        
    }
    if (digitalRead(button2) == LOW){
        outputsControl(button2);
    }
    if (digitalRead(button3) == LOW){
        outputsControl(button3);
    }
    if (digitalRead(button4) == LOW){
        outputsControl(button4);
    }
}