#include "SensorVeriSetFunctions.h"
#include <stdlib.h>
#include <string.h>
#define bool int
#define true 1
#define false 0


void setSensorDurum(Sensor* sen, int durum){
    sen->durum =durum;
}
void setSensorSayi(Sensor* sen, int sensorSayi){
     sen->sensorSayi =sensorSayi;
}
void setSensorId(Sensor* sen,unsigned int id){
     sen->id =id;
}
void setSensorTip(Sensor* sen,unsigned int id){
     if(id==0)
     strcpy(sen->sensorTipi,"SICAKLIK");
     else if(id==1)
     strcpy(sen->sensorTipi,"YAGMUR");
     else{
     strcpy(sen->sensorTipi,"NONAME");}
}

int setSurucuDurum(Surucu* sur, bool durum){
     sur->durum =durum;
    return true;
}


