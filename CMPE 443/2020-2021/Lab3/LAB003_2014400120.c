#include "LPC407x_8x_177x_8x.h"

#define GPIO_base 0x20098000
#define GPIO0 ((GPIO_Type *)(GPIO_base + 0x000)) //0x20098000
#define GPIO1 ((GPIO_Type *)(GPIO_base + 0x020)) //0x20098020
#define GPIO2 ((GPIO_Type *)(GPIO_base + 0x040)) //0x20098040
#define GPIO3 ((GPIO_Type *)(GPIO_base + 0x060)) //0x20098080

#define LED1_GPIO_DIR GPIO2->DIR
#define LED1_GPIO_PIN GPIO2->PIN
#define LED2_GPIO_DIR GPIO3->DIR
#define LED2_GPIO_PIN GPIO3->PIN
#define LED3_GPIO_DIR GPIO3->DIR
#define LED3_GPIO_PIN GPIO3->PIN
#define LED4_GPIO_DIR GPIO3->DIR
#define LED4_GPIO_PIN GPIO3->PIN



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
	
	if(key % 4 == 0){
		LED1_GPIO_PIN |= 	(1<<13);	//high
		LED2_GPIO_PIN |= 	(1<<28);	//high
		LED3_GPIO_PIN |= 	(1<<29);	//high
		LED4_GPIO_PIN |= 	(1<<23);	//high
	}
	
	else if(key % 4 == 1){
		LED1_GPIO_PIN &= ~(1<<13);	//low
		LED2_GPIO_PIN &= ~(1<<28);	//low
		LED3_GPIO_PIN |= 	(1<<29);	//high
		LED4_GPIO_PIN |= 	(1<<23);	//high
	}
	
	else if(key % 4 == 2){
		LED1_GPIO_PIN &= ~(1<<13);	//low
		LED2_GPIO_PIN |= 	(1<<28);	//high
		LED3_GPIO_PIN &= ~(1<<29);	//low
		LED4_GPIO_PIN |= 	(1<<23);	//high
		
	}
	
	else{
		LED1_GPIO_PIN &= ~(1<<13);	//low
		LED2_GPIO_PIN |= 	(1<<28);	//high
		LED3_GPIO_PIN |= 	(1<<29);	//high
		LED4_GPIO_PIN &= ~(1<<23);	//low
	}
}

void init(){
		LED1_GPIO_DIR |= 	(1<<13);
		LED2_GPIO_DIR |= 	(1<<28);
		LED3_GPIO_DIR |= 	(1<<29);
		LED4_GPIO_DIR |=	(1<<23);
	
		LED1_GPIO_PIN |= 	(1<<13);	//high
		LED2_GPIO_PIN |= 	(1<<28);	//high
		LED3_GPIO_PIN |= 	(1<<29);	//high
		LED4_GPIO_PIN |= 	(1<<23);	//high
}

void update() {
	LED_Init();
}

int main() {
	int i;
	init();
	while(1) {
		key++;
		key %= 4;
		for(i=0;i<millisecond*2000;i++);
		update();
		
	}
}