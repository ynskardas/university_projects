#include "LPC407x_8x_177x_8x.h"

#define GPIO_base 0x20098000
#define GPIO0 ((GPIO_Type *)(GPIO_base + 0x000)) //0x20098000
#define GPIO1 ((GPIO_Type *)(GPIO_base + 0x020)) //0x20098020
#define GPIO2 ((GPIO_Type *)(GPIO_base + 0x040)) //0x20098040

#define LED1_GPIO_DIR GPIO1->DIR
#define LED1_GPIO_PIN GPIO1->PIN
#define LED2_GPIO_DIR GPIO0->DIR
#define LED2_GPIO_PIN GPIO0->PIN
#define LED3_GPIO_DIR GPIO1->DIR
#define LED3_GPIO_PIN GPIO1->PIN


int millisecond = 500;
int key = 0;

typedef struct{
	volatile 	uint32_t 	DIR;
						uint32_t 	reserved[3];
	volatile 	uint32_t 	MASK;
	volatile 	uint32_t 	PIN;
	volatile 	uint32_t 	SET;
	volatile 	uint32_t 	CLR;
}GPIO_Type;

void LED_Init(){
	
	if(key % 3 == 0){
		LED1_GPIO_PIN &= ~(1<<18);	//low
		LED2_GPIO_PIN |= 	(1<<13);	//high
		LED3_GPIO_PIN &= ~(1<<13);	//low
	}
	
	else if(key % 3 == 1){
		LED1_GPIO_PIN |= 	(1<<18);
		LED2_GPIO_PIN &= ~(1<<13);
		LED3_GPIO_PIN &= ~(1<<13);
	}
	else{
		LED1_GPIO_PIN |= 	(1<<18);
		LED2_GPIO_PIN |= 	(1<<13);
		LED3_GPIO_PIN |= 	(1<<13);
	}
}

void init(){
		LED1_GPIO_DIR |= 	(1<<18);
		LED2_GPIO_DIR |= 	(1<<13);
		LED3_GPIO_DIR |= 	(1<<13);
		
		LED1_GPIO_PIN &= ~(1<<18);	//low
		LED2_GPIO_PIN |= 	(1<<13);	//high
		LED3_GPIO_PIN &= ~(1<<13);	//low
}

void update() {
	LED_Init();
}

int main() {
	int i;
	init();
	while(1) {
		key++;
		key %= 3;
		for(i=0;i<millisecond*2000;i++);
		update();
		
	}
}