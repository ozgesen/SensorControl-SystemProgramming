#ifndef SENSORVERI_H
#define SENSORVERI_H
#define bool int
#define true 1
#define false 0

//Sensor verilerinin tutuldugu yapı


typedef struct{
 char durum;
 int sensorSayi;
 unsigned int id;
 char sensorTipi[10];
 
} Sensor;

//Surucu verilerinin tutuldugu yapı
typedef struct{
 bool durum;
} Surucu;



#endif
