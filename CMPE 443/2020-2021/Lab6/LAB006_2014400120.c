#include "LPC407x_8x_177x_8x.h"

#define PCONP *((volatile uint32_t *) 0x400FC0C4UL)
#define IOCON_P1_25	*((volatile uint32_t*)(0x4002C0E4UL))
#define IOCON_P1_27	*((volatile uint32_t*)(0x4002C0ECUL))	// //TIMER
#define IOCON_P0_23	*((volatile uint32_t*)(0x4002C05CUL))	// //ADC


#define ADC ((ADC_Typedef*) (0x40034000UL))
	
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
#define LED4_GPIO_DIR GPIO2->DIR
#define LED4_GPIO_PIN GPIO2->PIN

#define PORT_BUTTON_DIR GPIO2 -> DIR
#define PORT_BUTTON GPIO2 -> PIN

#define PIN_LED1 (1 << 18)
#define PIN_LED2 (1 << 13)
#define PIN_LED3 (1 << 13)
#define PIN_LED4 (1 << 19)

#define PCONP_TIMER (1 << 1)	//
#define PCONP_ADC (1 << 12)
#define TIMER_N0 TIMER0
  
#define ADC_CLKDIV 4
#define Channel 0			//
#define Operation 1
#define Start 1

int key = 0;
static const uint32_t temp = ((uint32_t)(1<<13));

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

typedef struct{
	 volatile uint32_t CR;
	 volatile uint32_t GDR;
						uint32_t reserved;
   volatile uint32_t INTEN;
	 volatile uint32_t DR0; 
	 volatile uint32_t DR1; 
   volatile uint32_t DR2;
	 volatile uint32_t DR3; 
   volatile uint32_t DR4;
	 volatile uint32_t DR5; 
   volatile uint32_t DR6;
	 volatile uint32_t DR7;
	 volatile uint32_t STAT;
	 volatile uint32_t TRIM;
} ADC_Typedef;

static uint32_t session = 0;
static uint32_t rotating = 0;
static uint32_t lastHigh = 0;
static uint8_t first_time = 1;
static uint32_t ampt = 0;


void TIMER_INIT(){
	
	PCONP |= PCONP_TIMER;
	
	IOCON_P1_27 |=  (3);
	IOCON_P1_27 &= ~(4);

	TIMER_N0->CTCR &= ~3;
	
	TIMER_N0->TCR &= ~1; 
  TIMER_N0->TCR |=  2; 
	
  TIMER_N0->PR = 59;
	TIMER_N0->CCR |= (7 << 3); 
	
	TIMER_N0->TCR &= ~2; 
  TIMER_N0->TCR |=  1; 
  
	NVIC_EnableIRQ(TIMER0_IRQn); //  TIMER0 

}


void ADC_INIT(){

	PCONP |= PCONP_ADC;
	
	IOCON_P0_23 |= 	(1);		
  IOCON_P0_23 &= ~(6);						
  
  IOCON_P0_23 &= ~(3<<3);
	IOCON_P0_23 &= ~(1<<7);
	
	ADC->INTEN |= (1 << Channel);
	ADC->CR = (1 << Channel) | (ADC_CLKDIV << 8) | (Operation << 21) | (Start << 24);
	
	NVIC_EnableIRQ(ADC_IRQn);
}

void LED_INIT(){
	LED1_GPIO_DIR |= 	PIN_LED1;
	LED2_GPIO_DIR |= 	PIN_LED2;
	LED3_GPIO_DIR |= 	PIN_LED3;
	LED4_GPIO_DIR |= 	PIN_LED4;
		
	LED1_GPIO_PIN |= (PIN_LED1);	//high
	LED2_GPIO_PIN |= (PIN_LED2);	//high
	LED3_GPIO_PIN &= ~(PIN_LED3);	//low
	LED4_GPIO_PIN &= ~(PIN_LED4);	//low
}


void turn_off_leds(){
	LED1_GPIO_PIN |=  (PIN_LED1);	
	LED2_GPIO_PIN |= 	(PIN_LED2);	
	LED3_GPIO_PIN &= ~(PIN_LED3);	
	LED4_GPIO_PIN &= ~(PIN_LED4);
}

void turn_on_leds(last){
	if((ampt * last >= 60000000 - 5 * last) && (ampt * last <= 60000000 + 5 * last)){
		LED4_GPIO_PIN |= (PIN_LED4);
	} else {
		LED4_GPIO_PIN &= ~(PIN_LED4);
	}
	
	if(60000000 > 50 * last){
		LED1_GPIO_PIN &= ~(PIN_LED1);	
		LED2_GPIO_PIN &= ~(PIN_LED2);	
		LED3_GPIO_PIN |=  (PIN_LED3);	
	}
	else if(50 * last > 60000000 && 60000000 > 25 * last){
		LED1_GPIO_PIN &= ~(PIN_LED1);	
		LED2_GPIO_PIN &= ~(PIN_LED2);	
		LED3_GPIO_PIN &= ~(PIN_LED3);	
	}
	else{
		LED1_GPIO_PIN &= ~(PIN_LED1);	
		LED2_GPIO_PIN |= 	(PIN_LED2);	
		LED3_GPIO_PIN &= ~(PIN_LED3);	
	}
}

void update() {
	if(rotating){
		turn_on_leds(lastHigh);
	}
	else{
		turn_off_leds();
	}
}

void  TIMER0_IRQHandler(void){ //  here
	if((TIMER_N0->IR & (1<<5)) != 0){ //  CAP 1 = 5 CAPO = 4			//CAP1
		TIMER_N0->IR |= 1<<5;
		
		if(session == 0){
				if(first_time)
					first_time = 0;
				else{
					lastHigh = TIMER_N0->CR1; // here
					update();
				}
				
				TIMER_N0->TCR |= (1<<1);
				TIMER_N0->TCR &= ~(1<<1);
				session = 1;
		}
		else if ( session == 1){
				session = 0;
		}
	}
	
}
void ADC_IRQHandler(void){
	
	ampt = ADC->DR0 >> 4; // here
	if(ampt >= 0x100)
		rotating = 1;
	else
		rotating  = 0;
}

int main() {
	LED_INIT();
	TIMER_INIT();
	ADC_INIT();
	__enable_irq();
	
	while(1) {
		__WFI();		
	}
}