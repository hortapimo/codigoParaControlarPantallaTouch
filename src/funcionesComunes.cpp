#include "funcionesComunes.h"
#include "Arduino.h"
#define XMAX 3700 // enrealida se trata de la y max, pero transformamos a landscape mode
#define XMIN 750 //los valores se obtuvieron de la prueba de calibracion
#define YMAX 3700
#define YMIN 530  

void cambioCordenadas(TSPoint& point)
{
  int auxX = map(point.y, YMAX, YMIN, 0, 480);
  int auxY = map(point.x, XMIN, XMAX, 0, 320);

  point.x = auxX;
  point.y = auxY;
}

void imprimirPunto(int x, int y, int z)
{
  Serial.print("\tPressure = "); Serial.println(z);
  Serial.print("\tx = "); Serial.println(x);
  Serial.print("\ty = "); Serial.println(y);
  delay(300);
}