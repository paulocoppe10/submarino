#include <Servo.h>

Servo horizontal; 
Servo vertical;

int pothorizontal = 0;
int valhorizontal;  
int potvertical = 1; 
int valvertical; 
int pothelice = 2;
int pottanques = 3;

int LED = 11; 
int BOTAO = 8; 
int valor = LOW;
int valorAnterior = LOW;
int estado = 0;
int brilho = 128;
unsigned long inicio;

void setup() {
  horizontal.attach(9); 
  vertical.attach(10);  
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);  
  pinMode(LED, OUTPUT);
  pinMode(BOTAO, INPUT); 
}

void loop() {
  valhorizontal = analogRead(pothorizontal);           
  valhorizontal = map(valhorizontal, 0, 1023, 180, 0);     
  horizontal.write(valhorizontal); 
  Serial.print("angulo hori:");
  Serial.println(valhorizontal);
  delay(15);   
  
  
  valvertical = analogRead(potvertical);           
  valvertical = map(valvertical, 0, 1023, 180, 0);     
  vertical.write(valvertical); 
  Serial.print("angulo vert:");
  Serial.println(valvertical);
  delay(15);     
  
  Serial.println(analogRead(pothelice));
  if (analogRead(pothelice) > 511) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  if (analogRead(pothelice) < 511) {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  
  Serial.println(analogRead(pottanques));
  if (analogRead(pottanques) > 511) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  if (analogRead(pottanques) < 511) {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
  delay(15);
  
  
  valor = digitalRead (BOTAO);

  if ((valor == HIGH) && (valorAnterior==LOW)) {
estado = 1 - estado;
inicio = millis();
delay (10); }

  if ((valor==HIGH) &&
(valorAnterior==HIGH)) {

  if (estado==1 && (millis()-inicio) > 500); {
brilho++;
delay(10);

    if (brilho > 255)
brilho = 0; } }
valorAnterior = valor;

  if (estado == 1) {
analogWrite(LED, brilho); }

  else {
analogWrite(LED, 0); } 
}
