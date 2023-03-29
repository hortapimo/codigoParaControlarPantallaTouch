#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <TouchScreen.h>
#include "view.h"
#include "model.h"


class Controlador{
  public:

    Model& refModel;

    Controlador(Model& model)
      : refModel(model)
    {}

    void procesarToque(TSPoint point, View& refVista);
    bool presionoPantalla(int presion);

    void procesarToqueVentana1(TSPoint point, View& refView);
    void procesarToqueVentana2(TSPoint point, View& refView);

    char lugarDondeTocoVentana1(TSPoint point);
    char lugarDondeTocoVentana2(TSPoint point);


};

#endif