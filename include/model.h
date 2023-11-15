#ifndef MODEL_H
#define MODEL_H

#include "ESP32Servo.h"

class Model{
  private:
    void hacerPasoMotores(long periodoPulso);
    float calcularPeriodoPulso(float caudal, short int MOTOR);
    float calcularTiempoDosis(float dosis_);
    void iniciarPines();
    void moverServo(char posicion);

    Servo servo;

  public:
    float caudal = 1;// [ml/min]
    float dosis = 1;// [ml]
    float dosisLimpieza = 1;// [ml]
    float dosisDescarte = 0.2;// [ml/min]
    float relacionCaudal = 1; // [ml/min]

    void sintetizar();
    void dosificar(float tiempoDosis, float periodoPulsoM1, float periodoPulsoM2);
    void hacerDescarte(float tiempoDescarte,float periodoPulsoM1, float periodoPulsoM2);
    void limpiar();
    void cambiarCaudal(float deltaCaudal);
    void cambiarDosis(float deltaDosis);
    void cambiarDosisLimpieza(float deltaDosis);
    void cambiarDosisDescarte(float deltaDosis);
    void cambiarRelacion(float deltaRelacion);
};

#endif