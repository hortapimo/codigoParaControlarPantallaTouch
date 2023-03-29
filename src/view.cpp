#include "view.h"
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include "Arduino.h"

const int RADIO_BOTONES_CAUDAL = 40;
const int ALTURA_FILA_2 = 90;
const int ALTURA_FILA_3 = 190;

void View::iniciarGui()
{
  splashScreen();
  crearVentana1();
}

void View::splashScreen()
{
  _limpiarPantalla();
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print("Plamic Biotech S.A", CENTER, 150);
  delay(2000);
  pantalla.fillScr(VGA_BLUE);
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.print("Drug Capsule Sintetizar", CENTER, 150);
  pantalla.print("Model: 0.1", CENTER, 200);
  delay(2000);
}

void View::crearVentana1(float caudal=CAUDAL_DEFAULT , float dosis=DOSIS_DEFAULT) 
{
  _limpiarPantalla();

  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Indique Caudal y Dosis", 0,10);
  
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.print("Caudal:\n[ml/min]", 10,ALTURA_FILA_2);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(caudal,1), 150,ALTURA_FILA_2);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_2+10,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_2+10,'-',1,1,1);

  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Dosis:\n[ml/min]", 10,ALTURA_FILA_3);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(dosis,1), 150,ALTURA_FILA_3);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_3+10,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_3+10,'-',1,1,1);
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Siguiente", 280,280);
  
  ventanaActual=1;
}

void View::crearVentana2(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT)
{
  _limpiarPantalla();

  pantalla.setFont(&FreeMonoBold18pt7b);

  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Caudal y dosis\nindicada:", 0,10);

  pantalla.print("Caudal\n[ml/min]:",0,ALTURA_FILA_2);
  pantalla.print(String(caudal,1), 200, ALTURA_FILA_2);
  pantalla.print("Dosis\n[ml]:",0, ALTURA_FILA_3);
  pantalla.print(String(dosis,1), 200, ALTURA_FILA_3);

  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Iniciar",280,280);
  pantalla.print("Regresar", 0, 280);  

  ventanaActual=2;

}

void View::crearVentana3()
{
  _limpiarPantalla();

  pantalla.print("Dosificando ...", CENTER, 150);

  ventanaActual = 3;
}

void View::cambiarCaudal(float caudal, float dosis, float delta)
{
  caudal = caudal + delta;

  crearVentana1(caudal = caudal, dosis = dosis);
}

void View::cambiarDosis(float caudal, float dosis, float delta)
{ 
  dosis = dosis + delta;

  crearVentana1(caudal = caudal,dosis=dosis);
}

void View::_limpiarPantalla()
{
  //pantalla.InitLCD();
  pantalla.fillScr(VGA_BLUE);
}
