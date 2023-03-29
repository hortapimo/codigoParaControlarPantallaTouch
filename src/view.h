#ifndef VIEW_H
#define VIEW_H

#include <UTFTGLUE.h>

const float CAUDAL_DEFAULT = 1.0;
const float DOSIS_DEFAULT = 1.0;

class View{

  public:
    
    UTFTGLUE pantalla{0,A2,A1,A3,A4,A0};

    View(){
    }

    int ventanaActual;

    void iniciarGui();

    void splashScreen();
    void crearVentana1(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT);
    void crearVentana2(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT);
    void crearVentana3();

    void cambiarCaudal(float caudal, float dosis, float delta);
    void cambiarDosis(float caudal, float dosis, float delta);

    void limpiarPantalla();

};

#endif