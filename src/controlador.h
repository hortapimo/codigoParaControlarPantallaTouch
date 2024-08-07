#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <TouchScreen.h>
#include "view.h"
#include "model.h"


class Controlador{
  public:

    Model& refModel;
    View& refVista;

    Controlador(Model& model, View& view)
      : refModel(model), refVista(view) //Es necesario inicializar aso porque no se pueden inicializar referencias a vacio, esto hace que la def de arriba sea automatica. 
    {}

    void procesarToque(TSPoint point);
    bool presionoPantalla(int presion);

    void procesarToqueVentana1(TSPoint point);
    void procesarToqueVentana11(TSPoint point);
    void procesarToqueVentana2(TSPoint point);

    char lugarDondeTocoVentana1(TSPoint point);
    char lugarDondeTocoVentana11(TSPoint point);
    char lugarDondeTocoVentana2(TSPoint point);

};

#endif
