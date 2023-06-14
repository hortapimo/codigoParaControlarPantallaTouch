#ifndef MODEL_H
#define MODEL_H

#include "Servo.h"

class Model{
  private:
    void girarMotores(long periodoPulso);
    void girarMotores(long periodoPulsoM1, long periodoPulsoM2, long relacionCaudal);
    float calcularPeriodoPulso(float caudal);
    float calcularTiempoDosis();
    float calcularTiempoDescarte();
    void iniciarPines();
    void moverServo(char posicion);

    Servo servo;

  public:
    float caudal = 1;//ml/min
    float dosis = 1;//ml
    float dosisDescarte = 0.2;//ml/min
    float relacionCaudal = 1; //ml/min

    void dosificar();
    void hacerDescarte();
};

#endif