#ifndef MODEL_H
#define MODEL_H

class Model{
  private:
    void girarMotores(long periodoPulso);
    float calcularPeriodoPulso(float caudal);
    float calcularTiempoDosis(float caudal, float dosis);
    void iniciarPines();

  public:
    float caudal = 1;//ml/min
    float dosis = 1;//ml
    float dosisDescarte = 0.2;//ml/min

    void dosificar();
    void hacerDescarte();
};

#endif