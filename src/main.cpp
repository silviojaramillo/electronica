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
int outputC = 24;
int outputD = 25;

//Variables para guardar los valores de la tensiones de las entradas
double mesureVoltageA;
double mesureVoltageB;

//Variables para guardar los valores de las corrientes de las entradas
double measureCurrentA;
double measureCurrentB;

//Lista para guardar los estados de los elementos


//Función para leer la tensión
double measureVoltage(int valuePin){
    double volt = valuePin*10/1024;
    return volt;
}

//Función para leer la corriente
double measureCurrent(int valuePin){
    return 0;
}

//Función para controlar el paso de la corriente en las entradas
int intputControl(int valueV, int valueC){
    int outputFunction;
    if(valueV <= 5 && valueC < 1){
        outputFunction = HIGH;
    }else{
        outputFunction = LOW;
    }
    return outputFunction;
}

//Función para las salidas de las señales
int outputsControl(){
    return 0;
}


void setup(){
    
}
void loop(){

}