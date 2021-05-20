#include "LPC407x_8x_177x_8x.h"

#define PCONP *((volatile uint32_t *) 0x400FC0C4UL)
#define IOCON_P1_25	*((volatile uint32_t*)(0x4002C0E4UL))
	
#define GPIO_base 0x20098000UL
#define TIMER_base 0x40004000UL

#define GPIO0 ((GPIO_TypeDef*) (GPIO_base + 0x00UL))
#define GPIO1 ((GPIO_TypeDef*) (GPIO_base + 0x20UL))
#define GPIO2 ((GPIO_TypeDef*) (GPIO_base + 0x40UL))
#define GPIO3	((GPIO_TypeDef*) (GPIO_base + 0x060))
#define GPIO4	((GPIO_TypeDef*) (GPIO_base + 0x080))
#define GPIO5	((GPIO_TypeDef*) (GPIO_base + 0x0A0))

#define TIMER0 ((TIMER_TypeDef *)(TIMER_base))
#define TIMER1 ((TIMER_TypeDef *)(TIMER_base + 0x4000UL))
#define TIMER2 ((TIMER_TypeDef *)(TIMER_base + 0x90000UL - 0x4000UL))
#define TIMER3 ((TIMER_TypeDef *)(TIMER_base + 0x90000UL))

#define LED1_GPIO_DIR GPIO1->DIR
#define LED1_GPIO_PIN GPIO1->PIN
#define LED2_GPIO_DIR GPIO0->DIR
#define LED2_GPIO_PIN GPIO0->PIN
#define LED3_GPIO_DIR GPIO1->DIR
#define LED3_GPIO_PIN GPIO1->PIN
#define LED4_GPIO_DIR GPIO4->DIR
#define LED4_GPIO_PIN GPIO4->PIN

#define PORT_BUTTON_DIR GPIO2 -> DIR
#define PORT_BUTTON GPIO2 -> PIN

static const uint32_t temp = ((uint32_t)(1<<13));

int millisecond = 500;
int key = 0;

typedef struct{
	volatile uint32_t DIR;
					 uint32_t reserved[3];
	volatile uint32_t MASK;
	volatile uint32_t PIN;
	volatile uint32_t SET;
	volatile uint32_t CLR;
} GPIO_TypeDef;

typedef struct {
   volatile uint32_t IR;
   volatile uint32_t TCR;
   volatile uint32_t TC;
   volatile uint32_t PR;
   volatile uint32_t PC;
   volatile uint32_t MCR;
   volatile uint32_t MR0;
   volatile uint32_t MR1;
   volatile uint32_t MR2;
   volatile uint32_t MR3;
   volatile uint32_t CCR;
   volatile uint32_t CR0;
   volatile uint32_t CR1;
						uint32_t reserved1[2];
   volatile uint32_t EMR;
						uint32_t reserved2[12];
   volatile uint32_t CTCR;
} TIMER_TypeDef;


void TIMER_INIT(){

	IOCON_P1_25 |= 3;
	
	PCONP |= 1 << 1;
	
	TIMER1->TCR = 1; 
  TIMER1->PR = 59;
  TIMER1->MR0 = 500000;   
	TIMER1->MCR = 0;     
	TIMER1->EMR |= (1<<1) | (1<<6) | (1<<7); 
}


void LED_UPDATE(){
	
	if(key % 4 == 0){
		LED1_GPIO_PIN &= ~(1<<18);	//low
		LED2_GPIO_PIN |= 	(1<<13);	//high
		LED3_GPIO_PIN &= ~(1<<13);	//low
		LED4_GPIO_PIN &= ~(1<<18);	//low
	}
	
	else if(key % 4 == 1){
		LED1_GPIO_PIN |= 	(1<<18);
		LED2_GPIO_PIN &= ~(1<<13);
		LED3_GPIO_PIN &= ~(1<<13);
		LED4_GPIO_PIN |= 	(1<<18);	
	}
	else if(key % 4 == 2){
		LED1_GPIO_PIN |= 	(1<<18);
		LED2_GPIO_PIN |= 	(1<<13);
		LED3_GPIO_PIN |= 	(1<<13);
		LED4_GPIO_PIN &= ~(1<<18);	
	}
	else{
		LED1_GPIO_PIN |= 	(1<<18);
		LED2_GPIO_PIN |= 	(1<<13);
		LED3_GPIO_PIN &= ~(1<<13);
		LED4_GPIO_PIN |= 	(1<<18);
	}
}

void LED_INIT(){
	LED1_GPIO_DIR |= 	(1<<18);
	LED2_GPIO_DIR |= 	(1<<13);
	LED3_GPIO_DIR |= 	(1<<13);
	LED4_GPIO_DIR |= 	(1<<18);
		
	LED1_GPIO_PIN &= ~(1<<18);	//low
	LED2_GPIO_PIN |= 	(1<<13);	//high
	LED3_GPIO_PIN &= ~(1<<13);	//low
	LED4_GPIO_PIN &= ~(1<<18);	//low
	
	PORT_BUTTON_DIR &= ~(1 << 13);
		
}

void update() {
	uint32_t check;
	check = temp & PORT_BUTTON;
	
	while (temp == check){
				while(TIMER1->TC < TIMER1->MR0);
				key++;
				key %= 4;
				TIMER1->TC = 0;
    
				LED_UPDATE();
			}
			LED_UPDATE();
}

int main() {
	int i;
	TIMER_INIT();
	LED_INIT();
	while(1) {
		update();
		
	}
}