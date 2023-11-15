#include "Arduino.h"
#include "Controlador.h"
#include "View.h"

#include "funcionesComunes.h"

const float MAX_CAUDAL_GV = 20.0;

void imprimirPunto(int x, int y, int z);

Model model;
View vista;
Controlador controlador(model, vista);

const int PIN_XP=27/*lcd6*/, PIN_XM=15/*lcdrs*/, PIN_YP=4/*lcdwr*/, PIN_YM=14/*lcd7*/;
TouchScreen toque = TouchScreen(PIN_XP, PIN_YP, PIN_XM, PIN_YM, 377);
TSPoint punto;


void setup() 
{
  controlador.refVista.pantalla.InitLCD();
  vista.iniciarGui();
}

void loop() 
{
  punto = toque.getPoint();

  pinMode(PIN_YP, OUTPUT); //restauro pines compartidos
  pinMode(PIN_XM, OUTPUT);
  
  cambioCordenadas(punto);

  controlador.procesarToque(punto);
}
