#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

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
int lm = A5;
int ft = A6;


//Pines para controlar los relés de las señales de entrada
int inputA = 22;
int inputB = 23;

//Pines para controlar las señales de la salida
int outputAC = 24;
int outputAD = 25;
int outputBC = 26;
int outputBD = 27;

//Variables para guardar los valores de la tensiones de las entradas
float mesureVoltageA;
float mesureVoltageB;

//Variables para guardar los valores de las corrientes de las entradas
float measureCurrentA = 0.0;
float measureCurrentB = 0.0;

//Definiendo las lecturas de los botones
int button1 = 28;
int button2 = 29;
int button3 = 30;
int button4 = 31;
int button5 = 32;

// Contador para mostrar los valores en la pantalla
int counter = 0;

// Encender led con la fotorresistencia
int ftled = 40;

int on = LOW;
int off = HIGH;

//Función para leer la tensión
float measureVoltage(int valuePin){
    float volt = analogRead(valuePin)*25.0/1024;
    return volt;
}

//Función para leer la corriente
float measureCurrent(int valuePin){
    float amper = 0.0;
    for (size_t i = 0; i < 100; i++){
        amper = amper + ((analogRead(valuePin)*5.0/1023)-2.5)/0.185; 
    }
    return amper/100;
    amper = 0.0;
}

//Función para controlar el paso de la corriente en las entradas
int inputControl(float valueV, float valueC){
    int outputFunction;
    if(valueV <= 5.1 && valueC < 1.0){
        outputFunction = on;
    }else{
        outputFunction = off;
    }
    return outputFunction;
    outputFunction = -1;
}

//Función para las salidas de las señales
void outputsControl(int buttonPulse){
    //A saliendo por C
    //B saliendo por D
    if(buttonPulse == button1){
        digitalWrite(outputAD,off);
        digitalWrite(outputBC,off);
        digitalWrite(outputBD,on);
        digitalWrite(outputAC,on);
        
    //A saliendo por D
    //B saliendo por C
    }
    if(buttonPulse == button2){
        digitalWrite(outputAC,off);
        digitalWrite(outputBD,off);
        digitalWrite(outputAD,on);
        digitalWrite(outputBC,on);
    }
}

// Función para leer el sensor LM35
  float measureOne(int valuePin){
    int sensorlm35=analogRead(valuePin);
    return map(sensorlm35, 0, 309, 0, 151);
  }

// Función para leer el valor de la fotorresistencia
  float measureTwo(int valuePin){
    int resistor = analogRead(valuePin);
      return resistor*5.0/1023;
  }

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
    //Pines analógicos para toma de medidas
    pinMode(voltageA,INPUT);
    pinMode(voltageB,INPUT);
    pinMode(currentA,INPUT);
    pinMode(currentB,INPUT);
    //Pines digitales para control de acciones
    pinMode(inputA,OUTPUT);
    pinMode(inputB,OUTPUT);
    pinMode(outputAC,OUTPUT);
    pinMode(outputAD,OUTPUT);
    pinMode(outputBC,OUTPUT);
    pinMode(outputBD,OUTPUT);
    //Declarando los pines para leer las pulsaciones
    pinMode(button1,INPUT_PULLUP);
    pinMode(button2,INPUT_PULLUP);
    pinMode(button3,INPUT_PULLUP);
    pinMode(button4,INPUT_PULLUP);
    pinMode(button5,INPUT_PULLUP);
    //Iniciamos dos relés apagados y solo dos encendidos para definir dos salidas por defecto
    digitalWrite(outputAC,on);
    digitalWrite(outputAD,off);
    digitalWrite(outputBC,off);
    digitalWrite(outputBD,on);
    //Entradas encendidas por defecto
    digitalWrite(inputA,on);
    digitalWrite(inputB,on);
    //Iniciando la comunicación serial
    Serial.begin(9600);
    //Para mostrar datos en la pantalla
    lcd.begin(16, 2);
}

void loop(){
    //Se miden las tensiones y corrientes de las entradas
    mesureVoltageA = measureVoltage(voltageA);
    mesureVoltageB = measureVoltage(voltageB);
    measureCurrentA = measureCurrent(currentA);
    measureCurrentB = measureCurrent(currentB);
    //Se muestra los valores de las mediciones anteriores
    if(counter == 0){
        lcd.clear();
        //Tensiones A y B
        lcd.setCursor(0,0);
        lcd.print("VA=");
        lcd.setCursor(3,0);
        lcd.print(mesureVoltageA,2);
        lcd.setCursor(8,0);
        lcd.print("VB=");
        lcd.setCursor(11,0);
        lcd.print(mesureVoltageB,2);
        //Corrientes A y B
        lcd.setCursor(0,1);
        lcd.print("IA=");
        lcd.setCursor(3,1);
        lcd.print(measureCurrentA,2);
        lcd.setCursor(8,1);
        lcd.print("IB=");
        lcd.setCursor(11,1);
        lcd.print(measureCurrentB,2);
    }
    if(counter == 1){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("VC=");
            lcd.setCursor(0,1);
            lcd.print("IC=");
            if(digitalRead(outputAC) == on && digitalRead(outputBD) == on){
                lcd.setCursor(3,0);
                lcd.print(mesureVoltageA,2);
                lcd.setCursor(3,1);
                lcd.print(measureCurrentA,2);
                lcd.setCursor(11,0);
                lcd.print(mesureVoltageB,2);
                lcd.setCursor(11,1);
                lcd.print(measureCurrentB,2);
            }
            lcd.setCursor(8,0);
            lcd.print("VD=");
            lcd.setCursor(8,1);
            lcd.print("ID=");
            if(digitalRead(outputBC) == on && digitalRead(outputAD) == on){
                lcd.setCursor(3,0);
                lcd.print(mesureVoltageB,2);
                lcd.setCursor(3,1);
                lcd.print(measureCurrentB,2);
                lcd.setCursor(11,0);
                lcd.print(mesureVoltageA,2);
                lcd.setCursor(11,1);
                lcd.print(measureCurrentA,2);
            }
        }
        if(counter == 2){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("T=");
            lcd.setCursor(2,0);
            lcd.print(measureOne(lm),1);
            lcd.setCursor(7,0);
            lcd.print("FT=");
            lcd.setCursor(10,0);
            lcd.print(measureTwo(ft),2);
        }
    digitalWrite(inputA,inputControl(mesureVoltageA,measureCurrentA));
    digitalWrite(inputB,inputControl(mesureVoltageB,measureCurrentB));
    //Se realiza la acción
    if (digitalRead(button1) == LOW){
        outputsControl(button1);
    }
    if (digitalRead(button2) == LOW){
        outputsControl(button2);
    }
    if (digitalRead(button3) == LOW){
        counter = 0;
    }
    if (digitalRead(button4) == LOW){
        counter = 1;
    }
    if (digitalRead(button5) == LOW){
        counter = 2;
    }
    if(measureTwo(ft) < 1.15){
        digitalWrite(ftled,HIGH);
    }else{
        digitalWrite(ftled,LOW);
    }
    // Se da un pequeño delay para que los valores se muestren correctamente en la pantalla lcd.
    delay(300);
}