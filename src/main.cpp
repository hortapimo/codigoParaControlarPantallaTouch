#include "Arduino.h"
#include "Controlador.h"
#include "View.h"

#include "funcionesComunes.h"

void imprimirPunto(int x, int y, int z);

Model model;
View vista;
Controlador controlador(model, vista);

const int PIN_XP=27/*lcd6*/, PIN_XM=15/*lcdrs*/, PIN_YP=4/*lcdwr*/, PIN_YM=14/*lcd7*/;
TouchScreen toque = TouchScreen(PIN_XP, PIN_YP, PIN_XM, PIN_YM, 300);
TSPoint punto;

void setup() {
  controlador.refVista.pantalla.InitLCD();
  vista.iniciarGui();
  Serial.begin(115200);
}

void loop() {
  punto = toque.getPoint();
  pinMode(PIN_YP, OUTPUT);      //restore shared pins
  pinMode(PIN_XM, OUTPUT);
  
  Serial.println("Antes:");
  imprimirPunto(punto.x, punto.y, punto.z);
  cambioCordenadas(punto);
  Serial.println("Despues:");
  imprimirPunto(punto.x, punto.y, punto.z);
  delay(2000);

  controlador.procesarToque(punto);
}
