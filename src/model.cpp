#include "model.h"
#include "Arduino.h"
#include "constG.h"

const short int PIN_PULSO_M1 = 18;
const short int PIN_DIRECCION_M1 = 19;
const short int PIN_PULSO_M2 = 22;
const short int PIN_DIRECCION_M2 = 23;

const short int PIN_SERVO = 5;

const float CANTIDAD_MOTORES =2;

const float DIAMETRO_INTERNO = 0.16; // [cm]
const float PULSOS_VUELTA = 3200; // [cm]
const float RADIO_PERIMETRO = 2.475; // [cm]

const float FACTOR_CORRECCION_M1 = 0.535; // [cm]
const float FACTOR_CORRECCION_DEFAULT = 0.535; // [cm]
const float FACTOR_CORRECCION_M2 = 0.495; // [cm]

const short int MOTOR_1 = 1;
const short int MOTOR_2 = 2;
const short int MOTOR_DEFAULT = 0;

const char POSICION_DESCARTE = 'd';
const char POSICION_SINTESIS = 's';
const float VOLUMEN_MUERTO = 1.47; // [ml]bn

const short int PERIODO_PULSO_HIGH = 4;

void Model::sintetizar()
{
    //Hay que ver el tema de los tiempos en microsegundos ya que si el equipo esta prendido por ams de 1h va a fallar
    iniciarPines();
    float caudalMotor2 = caudal/(relacionCaudal+1);
    float caudalMotor1 = caudal-caudalMotor2;
    float periodoPulsoVolMuerto = calcularPeriodoPulso(caudal/2, MOTOR_DEFAULT); 
    float periodoPulsoM1 = calcularPeriodoPulso(caudalMotor1, MOTOR_1);
    float periodoPulsoM2 = calcularPeriodoPulso(caudalMotor2, MOTOR_2);
    float tiempoDosis = calcularTiempoDosis(dosis);
    float tiempoDescarte = calcularTiempoDosis(dosisDescarte);
    //tiempoDosis = tiempoDosis-tiempoDescarte;
    float tiempoVolumenMuerto =calcularTiempoDosis(VOLUMEN_MUERTO);

    moverServo(POSICION_DESCARTE);
    delay(1000);

    //llenar volumen muerto
    dosificar(tiempoVolumenMuerto, periodoPulsoVolMuerto, periodoPulsoVolMuerto);
    //hacer descarte
    dosificar(tiempoDescarte, periodoPulsoM1, periodoPulsoM2);
    moverServo(POSICION_SINTESIS);

    //hacer sintesis
    dosificar(tiempoDosis, periodoPulsoM1, periodoPulsoM2);
    moverServo(POSICION_DESCARTE);
}

void Model::dosificar(float tiempoDosis, float periodoPulsoM1, float periodoPulsoM2){
    float tiempoInicio = micros();
    float tiempoActual = micros();
    float tiempoRondaM1 = micros();
    float tiempoRondaM2 = micros();

    //Se dosifica el descarte
    while((tiempoActual - tiempoInicio) < tiempoDosis)
    {
        if (tiempoActual-tiempoRondaM1 >= periodoPulsoM1){
            digitalWrite(PIN_PULSO_M1, HIGH);
            delayMicroseconds(PERIODO_PULSO_HIGH);
            digitalWrite(PIN_PULSO_M1, LOW);
            tiempoRondaM1=micros();
        }
        if (tiempoActual-tiempoRondaM2>= periodoPulsoM2){
            digitalWrite(PIN_PULSO_M2, HIGH);
            delayMicroseconds(PERIODO_PULSO_HIGH);
            digitalWrite(PIN_PULSO_M2, LOW);
            tiempoRondaM2=micros();
        }
        tiempoActual = micros();
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

float Model::calcularPeriodoPulso(float caudal, short int motor)
{
  float aux;
  float area = M_PI*(DIAMETRO_INTERNO*DIAMETRO_INTERNO)/4;
  aux = area * RADIO_PERIMETRO * 2 * M_PI / (caudal*PULSOS_VUELTA) * 1000000 *60;
  if (motor == MOTOR_1){
    aux = aux * FACTOR_CORRECCION_M1; 
  }else if (motor == MOTOR_2){
    aux = aux * FACTOR_CORRECCION_M2; 
  }else{
    aux = aux * FACTOR_CORRECCION_DEFAULT; 
  }
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

float Model::calcularTiempoDosis(float dosis_)
{
    float tiempo = dosis_ / caudal; // ml/(ml/min) = min
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

void Model::limpiar()
{
    iniciarPines();
    float caudalLimpiezaMotor =caudal/2;
    float periodoPulsoM1 = calcularPeriodoPulso(caudalLimpiezaMotor, MOTOR_1);
    float periodoPulsoM2 = calcularPeriodoPulso(caudalLimpiezaMotor, MOTOR_2);
    float tiempoDosis = calcularTiempoDosis(dosis);

    dosificar(tiempoDosis, periodoPulsoM1, periodoPulsoM2);
}

void Model::cambiarCaudal(float deltaCaudal)
{
    if ((0<=caudal) && (caudal<= MAX_CAUDAL_GB))
    {
       if(!((caudal ==0) && (deltaCaudal<0))&&!((caudal==MAX_CAUDAL_GB)&&(deltaCaudal>0)))//para problemas en los bordes
       {
        caudal = int(caudal) + deltaCaudal;
       } 
    }
}

void Model::cambiarDosis(float deltaDosis)
{
    if (dosis>=DOSIS_MINIMA_GB)
    {
        if(!((dosis==DOSIS_MINIMA_GB)&&(deltaDosis<0)))
        {
            dosis = dosis + deltaDosis; 
        }
    }
}

void Model::cambiarDosisLimpieza(float deltaDosis)
{
    if (dosisLimpieza>=DOSIS_MINIMA_GB)
    {
        if(!((dosisLimpieza==DOSIS_MINIMA_GB)&&(deltaDosis<0)))
        {
            dosisLimpieza = dosisLimpieza + deltaDosis; 
        }
    }
}

void Model::cambiarDosisDescarte(float deltaDosis)
{
    if (dosisDescarte>=DOSIS_MINIMA_DESCARTE_GB)
    {
        if(!((dosisDescarte+deltaDosis<DOSIS_MINIMA_DESCARTE_GB)))
        {
            dosisDescarte = dosisDescarte + deltaDosis; 
        }
    }
}

void Model::cambiarRelacion(float deltaRelacion)
{
    if (relacionCaudal>=RELACION_MINIMA_GB)
    {
        if(!((relacionCaudal+deltaRelacion<RELACION_MINIMA_GB)))
        {
            relacionCaudal = relacionCaudal + deltaRelacion; 
        }
    }
}