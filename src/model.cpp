#include "model.h"
#include "Arduino.h"

const short int PIN_PULSO_M1 = 18;
const short int PIN_DIRECCION_M1 = 19;
const short int PIN_PULSO_M2 = 22;
const short int PIN_DIRECCION_M2 = 23;

const short int PIN_SERVO = 5;

const float CANTIDAD_MOTORES =2;

const float DIAMETRO_INTERNO = 0.16; //cm
const float PULSOS_VUELTA = 1600; //cm
const float RADIO_PERIMETRO = 2.475; //cm
const float FACTOR_CORRECCION = 0.47; //cm


const char POSICION_DESCARTE = 'd';
const char POSICION_SINTESIS = 's';

void Model::sintetizar()
{
    //Hay que ver el tema de los tiempos en microsegundos ya que si el equipo esta prendido por ams de 1h va a fallar
    iniciarPines();
    float caudalMotor1 = caudal/(relacionCaudal+1);
    float caudalMotor2 = caudal-caudalMotor1;
    float periodoPulsoM1 = calcularPeriodoPulso(caudalMotor1);
    float periodoPulsoM2 = calcularPeriodoPulso(caudalMotor2);
    float tiempoDosis = calcularTiempoDosis();
    float tiempoDescarte = calcularTiempoDescarte();

    moverServo(POSICION_DESCARTE);
    delay(1000);

    //hacer descarte
    dosificar(tiempoDescarte, periodoPulsoM1, periodoPulsoM2);
    moverServo(POSICION_SINTESIS);

    //hacer sintesis
    dosificar(tiempoDosis, periodoPulsoM1, periodoPulsoM2);
    moverServo(POSICION_DESCARTE);
}

void Model::dosificar(float tiempoDescarte, float periodoPulsoM1, float periodoPulsoM2){
    float tiempoInicio = micros();
    float tiempo = micros();
    float tiempoRondaM1 = micros();
    float tiempoRondaM2 = micros();

    //Se dosifica el descarte
    while((tiempo - tiempoInicio) < tiempoDescarte)
    {
        if (tiempo-tiempoRondaM1 >= periodoPulsoM1){
            digitalWrite(PIN_PULSO_M1, HIGH);
            delayMicroseconds(5);
            digitalWrite(PIN_PULSO_M1, LOW);
            delayMicroseconds(5);
            tiempoRondaM1=micros();
        }
        if (tiempo-tiempoRondaM2>= periodoPulsoM2){
            digitalWrite(PIN_PULSO_M2, HIGH);
            delayMicroseconds(5);
            digitalWrite(PIN_PULSO_M2, LOW);
            delayMicroseconds(5);
            tiempoRondaM2=micros();
        }
        tiempo = micros();
    }
}
void Model::iniciarPines()
{
    //Inicializacion pines Motores
    pinMode(PIN_DIRECCION_M1, OUTPUT);
    pinMode(PIN_DIRECCION_M2, OUTPUT);
    digitalWrite(PIN_DIRECCION_M1, HIGH);
    digitalWrite(PIN_DIRECCION_M2, LOW);

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

void Model::hacerPasoMotores(long periodoPulso)
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
    tiempo = tiempo * 60 *1000000; //en microsegundos

    return tiempo;
}

float Model::calcularTiempoDescarte()
{
    float tiempo = dosisDescarte / caudal; // ml/(ml/min) = min
    tiempo = tiempo * 60 *1000000; //en microsegundos

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
