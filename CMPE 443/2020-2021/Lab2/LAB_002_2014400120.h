#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "LPC407x_8x_177x_8x.h"

#define WINDOW_SIZE 3

typedef int32_t sensor_data_t;

const uint32_t dataSize = 20;
const sensor_data_t sensorData[] = { 4,8,19,15,18,9,6,14,10,15,19,4,4,18,100,2,2,9,3,6 };

	
#endif
