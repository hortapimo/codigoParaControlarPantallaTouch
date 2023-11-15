#include "view.h"
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include "Arduino.h"
#include "constG.h"

const int RADIO_BOTONES_CAUDAL = 40;
const int ALTURA_FILA_2 = 90;
const int ALTURA_FILA_3 = 190;

void View::iniciarGui()
{
  splashScreen();
  limpiarPantalla();
  crearVentanaInicio();
}

void View::splashScreen()
{

  pantalla.fillScr(VGA_BLUE);
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print("Lab NanoMed CNEA", CENTER, 150);
  delay(2000);
  pantalla.fillScr(VGA_BLUE);
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print("DCS", CENTER, 100);
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.print("Drug Capsule Synthesizer", CENTER, 150);
  pantalla.print("Model: 0.1", CENTER, 200);
  delay(3000);
}

void View::crearVentana1(float caudal , float dosis) 
{
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Indique Caudal y Dosis", 0,10);
  
  pantalla.print("Caudal:\n[ml/min]", 10,ALTURA_FILA_2);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(caudal,1), 150,ALTURA_FILA_2);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_2+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_2+16,'-',1,1,1);

  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Dosis:\n[ml]", 10,ALTURA_FILA_3);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(dosis,1), 150,ALTURA_FILA_3);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_3+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_3+16,'-',1,1,1);
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Siguiente", 280,280);
  pantalla.print("Regresar", 0, 280);  
  
  ventanaActual=1;
}

void View::crearVentanaInicio() 
{
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("------------ Alvi 1.0 ------------", 0,10);

  pantalla.setColor(VGA_GRAY);
  pantalla.print("Limpiar", 10,ALTURA_FILA_2);

  pantalla.setFont(&FreeMonoBold18pt7b);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);

  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Sintetizar", 10,ALTURA_FILA_3);

  pantalla.setFont(&FreeMonoBold18pt7b);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  
  ventanaActual=0;
}

void View::crearVentanaLimpieza(float caudal, float dosisLimpieza)
{
  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("------------ Alvi 1.0 ------------", 0,10);

  pantalla.print("Caudal:\n[ml/min]", 10,ALTURA_FILA_2);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(caudal,1), 150,ALTURA_FILA_2);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_2+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_2+16,'-',1,1,1);

  pantalla.setFont(&FreeMonoBold12pt7b);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Dosis:\n[ml]", 10,ALTURA_FILA_3);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(dosisLimpieza,1), 150,ALTURA_FILA_3);

  pantalla.setColor(VGA_RED);
  pantalla.fillCircle(300, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_3+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_3+16,'-',1,1,1);
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Iniciar", 280,280);
  pantalla.print("Regresar", 0, 280);
  
  ventanaActual=40;
}

void View::crearVentana11(float dosis, float relacionCaudal)
{
  pantalla.setFont(&FreeMonoBold12pt7b);
  
  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Indique Dosis de descarte", 0,10);
  
  pantalla.print("Dosis:\n[ml]", 10,ALTURA_FILA_2);
  pantalla.print("Relacion\n caudal:\n(acu:org)", 10, ALTURA_FILA_3);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.print(String(dosis,1), 150,ALTURA_FILA_2);
  pantalla.print(String(relacionCaudal,0)+":1",150, ALTURA_FILA_3);


  pantalla.setColor(VGA_RED);

  pantalla.fillCircle(300, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_2+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_2+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_2+16,'-',1,1,1);

  pantalla.fillCircle(300, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(290,ALTURA_FILA_3+16,'+',1,1,1);
  pantalla.fillCircle(420, ALTURA_FILA_3+10, RADIO_BOTONES_CAUDAL);
  pantalla.drawChar(410,ALTURA_FILA_3+16,'-',1,1,1);
  
  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Siguiente", 280,280);
  pantalla.print("Regresar", 0, 280);  

  ventanaActual=11;
}

void View::crearVentana2(float caudal , float dosis , float dosisDescarte, float relacionCaudal)
{
  pantalla.setFont(&FreeMonoBold12pt7b);

  pantalla.setBackColor(VGA_BLUE);
  pantalla.setColor(VGA_GRAY);
  pantalla.print("Parametros cargados:", 0,10);

  pantalla.print("Caudal[ml/min]:",0,50);
  pantalla.print(String(caudal,1), 320, 50);
  pantalla.print("Dosis[ml]:",0, 110);
  pantalla.print(String(dosis,1), 320, 110);
  pantalla.print("Dosis descarte[ml]:",0, 170);
  pantalla.print(String(dosisDescarte,1), 320, 170);
  pantalla.print("Relacion Caudal:",0, 230);
  pantalla.print(String(relacionCaudal,0)+":1", 320, 230);

  pantalla.setFont(&FreeMonoBold18pt7b);
  pantalla.setColor(VGA_OLIVE);
  pantalla.print("Iniciar",280,280);
  pantalla.print("Regresar", 0, 280);  

  ventanaActual=2;

}

void View::crearVentana3()
{
  limpiarPantalla();

  pantalla.print("Dosificando ...", CENTER, 150);

  ventanaActual = 3;
}

void View::crearVentanaLimpiando()
{
  limpiarPantalla();

  pantalla.print("Limpiando ...", CENTER, 150);

  ventanaActual = 41;
}

void View::cambiarCaudal(float caudal, float delta)
{
  if ((MIN_CAUDAL_GB<=caudal) && (caudal <= MAX_CAUDAL_GB))
  {
    if(!((caudal==MIN_CAUDAL_GB) && (delta<0))&&!((caudal==MAX_CAUDAL_GB)&&(delta>0)))
    {
      caudal = caudal + delta;

      pantalla.setBackColor(VGA_BLUE);
      pantalla.setColor(VGA_GRAY);
      pantalla.print(String(caudal,1), 150,ALTURA_FILA_2); 
    }
  }
}

void View::cambiarDosis(float dosis, float delta)
{ 
  if (dosis>=DOSIS_MINIMA_GB)
  {
    if(!((dosis==DOSIS_MINIMA_GB)&&(delta<0)))
    {
      dosis = dosis + delta;

      pantalla.setBackColor(VGA_BLUE);
      pantalla.setColor(VGA_GRAY);
      pantalla.print(String(dosis,1), 150,ALTURA_FILA_3);
    }
  }
}

void View::cambiarDosisDescarte(float dosis, float delta)
{
    if (dosis>=DOSIS_MINIMA_DESCARTE_GB)
  {
    if(!((dosis+delta<DOSIS_MINIMA_DESCARTE_GB)))
    {
      dosis = dosis + delta;

      pantalla.setBackColor(VGA_BLUE);
      pantalla.setColor(VGA_GRAY);
      pantalla.print(String(dosis,1), 150,ALTURA_FILA_2);
    }
  }
}

void View::cambiarRelacion(float relacionCaudal, float delta)
{
  if(relacionCaudal>=RELACION_MINIMA_GB)
  {
    if(!(relacionCaudal+delta < RELACION_MINIMA_GB))
    {
      relacionCaudal = relacionCaudal + delta;

      pantalla.setBackColor(VGA_BLUE);
      pantalla.setColor(VGA_GRAY);
      pantalla.print(String(relacionCaudal,0)+":1",150, ALTURA_FILA_3);
    }
  }

}

void View::limpiarPantalla()
{
  pantalla.fillScr(VGA_BLUE);
}
