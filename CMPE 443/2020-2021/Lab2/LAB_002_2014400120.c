#include "LPC407x_8x_177x_8x.h"
#include "SensorData.h"

sensor_data_t filteredSensorData[dataSize];

void insertionSort(int32_t array[], uint32_t size) {
	uint32_t step;
	int64_t j;
	uint32_t key;
  for (step = 1; step < size; step++) {
    key = array[step];
    j = step - 1;

    while (key < array[j] && j >= 0) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

void average(int32_t array[], uint32_t size, int32_t avg1[]){
	uint32_t i;
	uint32_t t;
	uint32_t total = 0;
	for(i = 0; i < size; i++){
		total = total + array[i];
	}
	
	t = (uint32_t)(total / size);
	avg1[0] = t;
}
	
void medianFilter(const sensor_data_t* data, sensor_data_t* result, uint32_t size) {
	int millisecond;
	uint32_t i; 
	uint32_t j;
	uint32_t k;
	uint32_t avg;
	uint32_t avgTemp;
	uint32_t median;
	
	for(i = 0; i < WINDOW_SIZE-1; i++){
		result[i] = data[i];
	}
	
	for(j = 0; j < dataSize - (WINDOW_SIZE-1); j++){
		int32_t temp[WINDOW_SIZE];
		int32_t avgTemp[1];
		avgTemp[0] = 0;
		for(k = j; k < j + WINDOW_SIZE; k++){
			temp[k - j] = data[k];
		}
		
		insertionSort(temp, WINDOW_SIZE);
		average(temp, WINDOW_SIZE, avgTemp);
		avg = avgTemp[0];
		median = temp[(WINDOW_SIZE - 1) / 2];
		result[j + WINDOW_SIZE - 1] = temp[(WINDOW_SIZE - 1) / 2];
		if(median * 1.5 < avg){
			
			LPC_GPIO1->SET = 2 << 31;
			for(i=0;i<millisecond*2000;i++);
			LPC_GPIO1->CLR = 2 << 31;
			for(i=0;i<millisecond*2000;i++);
			
		
		}
		
	}
	
}

void init() {
	
	LPC_GPIO1->CLR = 2 << 31;
	LPC_GPIO1->DIR |= 2 << 31;
	LPC_IOCON->P2_31 &= ~(0x3 << 3);
	LPC_IOCON->P2_31 |= (0 & 0x3) << 3;
}

void update() {
	medianFilter(sensorData, filteredSensorData, dataSize);
}

int main() {
	init();

	while(1) {
		int millisecond = 1000;
		int i;
		for(i=0;i<millisecond*2000;i++){
		}
		update();
	}
}
