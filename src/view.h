#ifndef VIEW_H
#define VIEW_H

#include <UTFTGLUE.h>

const float CAUDAL_DEFAULT = 1.0;
const float DOSIS_DEFAULT_DESCARTE = 0.2;
const float DOSIS_DEFAULT = 1.0;
const float RC_DEFAULT = 1.0;

class View{

  public:
    
    UTFTGLUE pantalla{0,A2,A1,A3,A4,A0};

    View(){
    }

    int ventanaActual;

    void iniciarGui();

    void splashScreen();
    void crearVentana1(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT);
    void crearVentana11(float dosisDescarte = DOSIS_DEFAULT_DESCARTE, float relacionCaudal = RC_DEFAULT);
    void crearVentana2(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT
    ,float dosisDescarte = DOSIS_DEFAULT_DESCARTE, float relacionCaudal = RC_DEFAULT);
    void crearVentana3();

    void cambiarCaudal(float caudal, float dosis, float delta);
    void cambiarDosis(float caudal, float dosis, float delta);
    void cambiarDosisDescarte(float dosis, float delta);
    void cambiarRelacion(float relacionCaudal, float delta);

    void limpiarPantalla();

};

#endif