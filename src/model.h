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

    void dosificar();
};

#endif