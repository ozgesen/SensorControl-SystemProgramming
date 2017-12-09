#ifndef SENSORVERISET_H
#define SENSORVERISET_H
#define bool int
#define true 1
#define false 0
#include <stdio.h>
#include "SensorVeri.h"

void setSensorDurum(Sensor* , int );
void setSensorSayi(Sensor* , int );
void setSensorId(Sensor* ,unsigned int );
void setSensorTip(Sensor* ,unsigned int );

int setSurucuDurum(Surucu* , bool );

#endif
