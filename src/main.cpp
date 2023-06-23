#include "Arduino.h"
#include "Controlador.h"
#include "View.h"

#include "funcionesComunes.h"


void imprimirPunto(int x, int y, int z);

Model model;
View vista;
Controlador controlador(model, vista);


//cambio
const int XP=6,XM=A2,YP=A1,YM=7;
TouchScreen toque = TouchScreen(XP, YP, XM, YM, 300);
TSPoint punto;

void setup() {
  controlador.refVista.pantalla.InitLCD();
  vista.iniciarGui();
  Serial.begin(9600);

}

void loop() {
  punto = toque.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  
  cambioCordenadas(punto);

  controlador.procesarToque(punto);
}

