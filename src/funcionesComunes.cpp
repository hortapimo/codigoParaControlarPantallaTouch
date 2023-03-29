#include "funcionesComunes.h"
#include "Arduino.h"
#define XMAX 925 // enrealida se trata de la y max, pero transformamos a landscape mode
#define XMIN 210 //los valores se obtuvieron de la prueba de calibracion
#define YMAX 920
#define YMIN 175  

void cambioCordenadas(TSPoint& point){
  
  int auxX = map(point.y, XMAX, XMIN, 0, 480);
  int auxY = map(point.x, YMIN, YMAX, 0, 320);

  point.x = auxX;
  point.y = auxY;
}

void imprimirPunto(int x, int y, int z){
  Serial.print("\tPressure = "); Serial.println(z);
  Serial.print("\tx = "); Serial.println(x);
  Serial.print("\ty = "); Serial.println(y);
  delay(300);
}