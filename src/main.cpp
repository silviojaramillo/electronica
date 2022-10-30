#include <Arduino.h>

void setup() {
  //configurando las entradas y salidas a usar en el proyecto
  pinMode(13,OUTPUT);
  /* Primera fase del proyecto */
  // Leyendo las corrientes IA e IB
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  //Leyendo las tensiones VA y VB
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  //Permitir el paso de corriente si V < 5 V e I < 1 A
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
}

void loop() {
  // Código que se va a ejecutar en el microcontrolador Arduino Mega 2560
  digitalWrite(13,LOW);
}