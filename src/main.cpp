#include <Arduino.h>
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
double measureCurrentA;
double measureCurrentB;

//Lista para guardar los estados de los elementos
int statesInOuts[] = {};

//Definiendo las lecturas de los botones
int button1 = 28;
int button2 = 29;
int button3 = 30;
int button4 = 31;

//Pines para encender leds en las entradas
int ledInputA = 32;
int ledInputB = 33;
int ledOutputAC = 34;
int ledOutputAD = 35;
int ledOutputBC = 36;
int ledOutputBD = 37;

//Función para leer la tensión
double measureVoltage(int valuePin){
    double volt = valuePin*10/1024;
    return volt;
}

//Función para leer la corriente
double measureCurrent(int valuePin){
    return 0;
}

//Función para determinar qué botón se ha pulsado
int buttonPressed(){
    
    return 0;
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
        outputBC = LOW;
        outputAC = HIGH;
    //A saliendo por D
    }
    if(buttonPulse == button2){
        outputBD = LOW;
        outputAD = HIGH;
    //B saliendo por C
    }
    if(buttonPulse == button3){
        outputAC = LOW;
        outputBC = HIGH;
    //B saliendo por D
    }
    if(buttonPulse == button4){
        outputAD = LOW;
        outputBD = HIGH;
    }

    //Salidas por defecto
    if(!button1 && !button2 && !button3 && !button4){
        outputAC = HIGH;
        outputBD = HIGH;
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

    //Pines analógicos
    pinMode(voltageA,INPUT);
    pinMode(voltageB,INPUT);
    pinMode(currentA,INPUT);
    pinMode(currentB,INPUT);
    pinMode(voltageC,INPUT);
    pinMode(voltageD,INPUT);
    pinMode(currentC,INPUT);
    pinMode(currentD,INPUT);

    //Pines digitales
    pinMode(inputA,OUTPUT);
    pinMode(inputB,OUTPUT);
    pinMode(outputAC,OUTPUT);
    pinMode(outputAD,OUTPUT);
    pinMode(outputBC,OUTPUT);
    pinMode(outputBD,OUTPUT);
    pinMode(button1,OUTPUT);
    pinMode(button2,OUTPUT);
    pinMode(button3,OUTPUT);
    pinMode(button4,OUTPUT);
    pinMode(ledInputA,OUTPUT);
    pinMode(ledInputB,OUTPUT);
    pinMode(ledOutputAC,OUTPUT);
    pinMode(ledOutputAD,OUTPUT);
    pinMode(ledOutputBC,OUTPUT);
    pinMode(ledOutputBD,OUTPUT);
}
void loop(){

    //Se miden las tensiones y corrientes de las entradas
    mesureVoltageA = measureVoltage(inputA);
    measureCurrentA = measureCurrent(inputA);
    mesureVoltageB = measureVoltage(inputB);
    measureCurrentB = measureCurrent(inputB);

    //De acuerdo a las lecturas se permite o no el paso de la corriente
    inputA = inputControl(mesureVoltageA,measureCurrentA);
    inputB = inputControl(mesureVoltageB,measureCurrentB);

    //Se enciende los leds que indican la presencia de tensión en las entradas
    onLed(mesureVoltageA,inputA);
    onLed(mesureVoltageB,inputB);

    //Se controla las salidas

    //outputsControl();
}