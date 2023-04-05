#include "model.h"
#include "Arduino.h"
#include "Servo.h""

const float PIN_PULSO_M1 = 31;
const float PIN_DIRECCION_M1 = 33;
const float PIN_PULSO_M2 = 35;
const float PIN_DIRECCION_M2 = 37;
//const float PIN_PRENDIDO = 31;

const float CANTIDAD_MOTORES =2;

const float DIAMETRO_INTERNO = 0.16; //cm
const float PULSOS_VUELTA = 1600; //cm
const float RADIO_PERIMETRO = 2.475; //cm
const float FACTOR_CORRECCION = 0.6; //cm

void Model::dosificar()
{

    iniciarPines();
    float caudalPorBomba = caudal/CANTIDAD_MOTORES;
    float periodoPulso = calcularPeriodoPulso(caudalPorBomba);
    float tiempoDosis = calcularTiempoDosis(caudal, dosis);

    float tiempoInicio = millis();
    float tiempo;

    Serial.println("Dosificando");
    Serial.println("El periodo pulso es");
    Serial.println(periodoPulso);
    Serial.println("El tiempo de dosis es[mseg]:");
    Serial.println(tiempoDosis);


    while((tiempo - tiempoInicio)< tiempoDosis)
    {
        for(int i=0; i<PULSOS_VUELTA/4;i++){
           girarMotores(periodoPulso); 
        }
        tiempo = millis();
    }

    Serial.println("Dosificando");
    Serial.println("El periodo pulso es");
    Serial.println(periodoPulso);
/*
    for(int i=0; i<PULSOS_VUELTA;i++){
           girarMotor(periodoPulso); 
    }
*/
    Serial.println("Termino Dosis");
}

void Model::iniciarPines()
{

pinMode(PIN_DIRECCION_M1, OUTPUT);
pinMode(PIN_DIRECCION_M2, OUTPUT);
digitalWrite(PIN_DIRECCION_M1, LOW);
digitalWrite(PIN_DIRECCION_M2, LOW);

pinMode(PIN_PULSO_M1,OUTPUT);
pinMode(PIN_PULSO_M2,OUTPUT);

//pinMode(PIN_PRENDIDO, HIGH);

}

float Model::calcularPeriodoPulso(float caudal)
{
  float aux;
  float area = M_PI*(DIAMETRO_INTERNO*DIAMETRO_INTERNO)/4;
  aux = area* RADIO_PERIMETRO* 2* M_PI / (caudal*PULSOS_VUELTA) * 1000000 *60;
  aux = aux * FACTOR_CORRECCION;
 
  return aux; //Sale en microsegundos
}

void Model::girarMotores(long periodoPulso)
{

  digitalWrite(PIN_PULSO_M1, HIGH);
  digitalWrite(PIN_PULSO_M2, HIGH);

  delayMicroseconds(periodoPulso/2); 

  digitalWrite(PIN_PULSO_M1, LOW);
  digitalWrite(PIN_PULSO_M2, LOW);

  delayMicroseconds(periodoPulso/2); 

}

float Model::calcularTiempoDosis(float caudal, float dosis)
{
    float tiempo = dosis / caudal; // ml/(ml/min) = min
    tiempo = tiempo * 60 *1000; //en milisegundos

    return tiempo;
}
