#ifndef SENSORVERIGET_H
#define SENSORVERIGET_H
#define bool int
#define true 1
#define false 0
#include "SensorVeri.h"
#include <stdio.h>


int getSensorDurum(Sensor* );
int getSensorSayi(Sensor* );
unsigned int getSensorId(Sensor* );
char* getSensorTip(Sensor* );

bool getSurucuDurum(Surucu*);

#endif
