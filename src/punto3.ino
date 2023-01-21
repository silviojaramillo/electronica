#include <LiquidCrystal.h>
int POT = A1;
float LecPOT;

#define IN1 12

#define IN2 11
#define IN1_1 22

#define IN2_2 23

#define ENA A3


LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
pinMode(IN1_1,OUTPUT);
pinMode(IN2_2,OUTPUT);

  pinMode(IN1, OUTPUT);

  pinMode(IN2, OUTPUT);

//pinMode(ENA, OUTPUT);

  //encender motor

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH);


}

void loop() {

  //delay(500);
  //lcd.noDisplay();
  //delay(500);
  lcd.setCursor(0,0);
  lcd.print("pos angular:");
  lcd.print(LecPOT);
  Serial.println(LecPOT);

  //lcd.setCursor(0,1);
  //lcd.print(porcentaje);
 LecPOT=analogRead(POT)/4;
  Serial.println(LecPOT);
if (LecPOT>=0 && LecPOT>50 && LecPOT<85){ //
   digitalWrite(IN1,LOW);
   digitalWrite(IN2, HIGH);
   digitalWrite(IN1_1,LOW);
   digitalWrite(IN2_2,HIGH);
}
if (LecPOT>85 && LecPOT<150){
  digitalWrite(IN2, HIGH);
   digitalWrite(IN1,LOW);
   digitalWrite(IN2_2,LOW);
}
if (LecPOT>150 && LecPOT<256){
  digitalWrite(IN1, HIGH);
   delay(1000);
   digitalWrite(IN2,LOW);
}
if (LecPOT<150 && LecPOT>85){
    digitalWrite(IN2, HIGH);
digitalWrite(IN2, HIGH);
   delay(1000);
   digitalWrite(IN1,LOW); 
  }
if (LecPOT<85 && LecPOT>50){
  digitalWrite(IN2,LOW);
  digitalWrite(IN2_2,HIGH);
}
if (LecPOT<50 && LecPOT>=0){
  digitalWrite(IN2,LOW);
  digitalWrite(IN2_2,HIGH);
}
}



