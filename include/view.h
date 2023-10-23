#ifndef VIEW_H
#define VIEW_H

#include <UTFTGLUE.h>

const float CAUDAL_DEFAULT = 1.0;
const float DOSIS_DEFAULT_DESCARTE = 0.2;
const float DOSIS_DEFAULT = 1.0;
const float RC_DEFAULT = 1.0;

#define LCD_RST 32 //brown
#define LCD_CS 33 //red
#define LCD_RS 15 //white
#define LCD_WR 4 //yellow
#define LCD_RD 2 //purple

#define LCD_D0 12 //purple
#define LCD_D1 13 //orange
#define LCD_D2 26 //yellow
#define LCD_D3 25 //orange
#define LCD_D4 17 //grey
#define LCD_D5 16 //blue
#define LCD_D6 27 //green
#define LCD_D7 14 //blue

#define PIN_SD_CS 22 // D8 
#define PIN_SD_MISO 19 //12
#define PIN_SD_MOSI 23 //11
#define PIN_SD_SCLK 18 //10 

class View{

  public:
    
    UTFTGLUE pantalla{0, LCD_RS, LCD_WR , LCD_CS, LCD_RST, LCD_RD};

    View(){
    }

    int ventanaActual;

    void iniciarGui();

    void splashScreen();
    void crearVentanaInicio();
    void crearVentanaLimpieza(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT);
    void crearVentana1(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT);
    void crearVentana11(float dosisDescarte = DOSIS_DEFAULT_DESCARTE, float relacionCaudal = RC_DEFAULT);
    void crearVentana2(float caudal = CAUDAL_DEFAULT, float dosis = DOSIS_DEFAULT
    ,float dosisDescarte = DOSIS_DEFAULT_DESCARTE, float relacionCaudal = RC_DEFAULT);
    void crearVentana3();
    void crearVentanaLimpiando();

    void cambiarCaudal(float caudal, float dosis, float delta);
    void cambiarDosis(float caudal, float dosis, float delta);
    void cambiarDosisDescarte(float dosis, float delta);
    void cambiarRelacion(float relacionCaudal, float delta);

    void limpiarPantalla();

};

#endif