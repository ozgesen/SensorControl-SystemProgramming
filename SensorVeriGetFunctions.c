
#include "SensorVeriGetFunctions.h"
#include <stdlib.h>
#define bool int
#define true 1
#define false 0



int getSensorDurum(Sensor* sen){
    return (sen->durum);
}
int getSensorSayi(Sensor* sen){
    return (sen->sensorSayi);
}
unsigned int getSensorId(Sensor* sen){
    return (sen->id);
}
char* getSensorTip(Sensor* sen){

     return (sen->sensorTipi);
}

bool getSurucuDurum(Surucu* sur){
    return (sur->durum);
}


