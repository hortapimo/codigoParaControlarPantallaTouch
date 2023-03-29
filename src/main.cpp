#include "Arduino.h"
#include "Controlador.h"
#include "View.h"

#include "funcionesComunes.h"


void imprimirPunto(int x, int y, int z);

Model model;
Controlador controlador(model);
View vista;


const int XP=6,XM=A2,YP=A1,YM=7;
TouchScreen toque = TouchScreen(XP, YP, XM, YM, 300);
TSPoint punto;

void setup() {
  vista.pantalla.InitLCD();
  vista.pantalla.clrScr();
  
  vista.iniciarGui();
  Serial.begin(9600);

}

void loop() {
  punto = toque.getPoint();
  cambioCordenadas(punto);

  controlador.procesarToque(punto, vista);
}

