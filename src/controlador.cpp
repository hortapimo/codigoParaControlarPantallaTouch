#include "Arduino.h"
#include "HardwareSerial.h"
#include "controlador.h"
#include "funcionesComunes.h"

#define BOTON_SIGUIENTE 's'
#define BOTON_REGRESAR 'r'
#define BOTON_MAS_CAUDAL 'a'
#define BOTON_MAS_DOSIS 'b'
#define BOTON_MENOS_CAUDAL 'A'
#define BOTON_MENOS_DOSIS 'B'
#define BOTON_INICIAR 'i'
#define NINGUN_BOTON 'n'

const float DELTA_CAUDAL = 1.0;
const float DELTA_DOSIS = 0.5;

void Controlador::procesarToque(TSPoint point)
{   
  if(presionoPantalla(point.z))
  {
    
    switch(refVista.ventanaActual)
    {
      case 1:
        procesarToqueVentana1(point);
      break;

      case 2:
        Serial.println("Entro a case 2");
        delay(1000);
        procesarToqueVentana2(point);
        
      break;  

      default:
      break;
    } 

  }
}

bool Controlador::presionoPantalla(int presion)
{
  return (presion > 100);
}

void Controlador::procesarToqueVentana1(TSPoint point)
{
  switch (lugarDondeTocoVentana1(point))
  {
    case BOTON_MAS_CAUDAL:
      refVista.cambiarCaudal(refModel.caudal, refModel.dosis,DELTA_CAUDAL);
      refModel.caudal += DELTA_CAUDAL;      
    break;

    case BOTON_MENOS_CAUDAL:
      refVista.cambiarCaudal(refModel.caudal, refModel.dosis,-1*DELTA_CAUDAL);
      refModel.caudal -= DELTA_CAUDAL; 
    break;

    case BOTON_MAS_DOSIS:
      refVista.cambiarDosis(refModel.caudal, refModel.dosis,DELTA_DOSIS);
      refModel.dosis += DELTA_DOSIS;  
    break;

    case BOTON_MENOS_DOSIS:
      refVista.cambiarDosis(refModel.caudal, refModel.dosis,-1*DELTA_DOSIS);
      refModel.dosis -= DELTA_DOSIS; 
    break;

    case BOTON_SIGUIENTE:
      refVista.ventanaActual = 2;
      refVista.limpiarPantalla();
      refVista.crearVentana2(refModel.caudal, refModel.dosis);
    break;   
        
  }
}

void Controlador::procesarToqueVentana2(TSPoint point)
{

  switch (lugarDondeTocoVentana2(point))
  {
    case BOTON_REGRESAR:
    refVista.limpiarPantalla();
      refVista.crearVentana1(refModel.caudal, refModel.dosis);
    break;

    case BOTON_INICIAR:
      refVista.limpiarPantalla();
      refVista.crearVentana3();
      refModel.dosificar();
      refVista.limpiarPantalla();
      refVista.crearVentana2(refModel.caudal, refModel.dosis);
    break;   
        
  }
}

char Controlador::lugarDondeTocoVentana1(TSPoint point)
{

  if (point.x>280 && point.y > 290)
  {
    return BOTON_SIGUIENTE;
  }
  if ((270<point.x && point.x<330) && (160<point.y && point.y<240))
  {
    return BOTON_MAS_DOSIS;
  }
  if ((270<point.x && point.x<330) && (60<point.y && point.y<120))
  { 
    return BOTON_MAS_CAUDAL;
  }
  if ((395<point.x && point.x<470) && (60<point.y && point.y<120))
  {
    return BOTON_MENOS_CAUDAL;
  }
  if ((395<point.x && point.x<470) && (160<point.y && point.y<240))
  {
    return BOTON_MENOS_DOSIS;
  }
  else
  {
    return NINGUN_BOTON;
  }
}

char Controlador::lugarDondeTocoVentana2(TSPoint point)
{
  
  if (point.x<150 && point.y > 290)
  {
    return BOTON_REGRESAR;
  }
  if (point.x>280 && point.y > 290)
  {
    return BOTON_INICIAR;
  }
  else return NINGUN_BOTON;

}
