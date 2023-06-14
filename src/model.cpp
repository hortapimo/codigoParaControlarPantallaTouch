#include "model.h"
#include "Arduino.h"
#include "Servo.h""

const short int PIN_PULSO_M1 = 31;
const short int PIN_DIRECCION_M1 = 33;
const short int PIN_PULSO_M2 = 35;
const short int PIN_DIRECCION_M2 = 37;

const short int PIN_SERVO = 53;

const float CANTIDAD_MOTORES =2;

const float DIAMETRO_INTERNO = 0.16; //cm
const float PULSOS_VUELTA = 1600; //cm
const float RADIO_PERIMETRO = 2.475; //cm
const float FACTOR_CORRECCION = 0.6; //cm


const char POSICION_DESCARTE = 'd';
const char POSICION_SINTESIS = 's';

void Model::dosificar()
{
    iniciarPines();
    float caudalPorBomba = caudal/CANTIDAD_MOTORES;
    float periodoPulso = calcularPeriodoPulso(caudalPorBomba);
    float tiempoDosis = calcularTiempoDosis();
    float tiempoDescarte = calcularTiempoDescarte();

    moverServo(POSICION_DESCARTE);
    delay(1000);

    float tiempoInicio = millis();
    float tiempo = millis();

    //Se dosifica el descarte
    while((tiempo - tiempoInicio) < tiempoDescarte)
    {
        for(int i=0; i<PULSOS_VUELTA/8;i++)
        {
            girarMotores(periodoPulso); 
        }
        tiempo = millis();
    }

    moverServo(POSICION_SINTESIS);
    tiempoInicio = millis();
    tiempo = millis();

    //Se dosifica la sintesis
    while((tiempo - tiempoInicio) < tiempoDosis)
    {
        for(int i=0; i<PULSOS_VUELTA/8;i++)
        {
           girarMotores(periodoPulso); 
        }
        tiempo = millis();
    }

    moverServo(POSICION_DESCARTE);
}

void Model::iniciarPines()
{
    //Inicializacion pines Motores
    pinMode(PIN_DIRECCION_M1, OUTPUT);
    pinMode(PIN_DIRECCION_M2, OUTPUT);
    digitalWrite(PIN_DIRECCION_M1, HIGH);
    digitalWrite(PIN_DIRECCION_M2, HIGH);

    pinMode(PIN_PULSO_M1,OUTPUT);
    pinMode(PIN_PULSO_M2,OUTPUT);

    //Inicializacion pines Servo
    pinMode(PIN_SERVO, OUTPUT);
    servo.attach(PIN_SERVO);

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

void Model::girarMotores(long periodoPulsoM1, long periodoPulsoM2, long relacionCaudal)
{

}

float Model::calcularTiempoDosis()
{
    float tiempo = dosis / caudal; // ml/(ml/min) = min
    tiempo = tiempo * 60 *1000; //en milisegundos

    return tiempo;
}

float Model::calcularTiempoDescarte()
{
    float tiempo = dosisDescarte / caudal; // ml/(ml/min) = min
    tiempo = tiempo * 60 *1000; //en milisegundos

    return tiempo;
}

void Model::moverServo(char posicion)
{
    if(posicion == POSICION_DESCARTE)
    {
        servo.write(10);
    }
    if(posicion == POSICION_SINTESIS)
    {
        servo.write(100);
    }
}
