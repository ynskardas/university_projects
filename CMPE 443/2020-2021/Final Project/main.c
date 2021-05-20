#include "LPC407x_8x_177x_8x.h"

#define GPIO_base 0x20098000

#define PCONP *((volatile uint32_t *) 0x400FC0C4)	// bit 15 is IOCON / GPIO
#define PCONP_TIMER (1 << 1)	//
#define PCONP_ADC (1 << 12)

#define GPIO0 ((GPIO_Type *)(GPIO_base + 0x000)) //0x20098000

#define TIMER0_base	0x40004000

#define TIMER0 ((TIMER_TypeDef*) TIMER0_base)

#define IOCON_P1_27	*((volatile uint32_t*)(0x4002C0ECUL)) // Timer iocon // Timer 0 - Cap 1
#define IOCON_P3_16 (*((volatile uint32_t *)  0x4002C1C0)) // PWM0[1] iocon for buzzer // P3[16] for buzzer

#define PWM_base 0x40014000
#define PWM_Type ((PWM_Typedef *)(PWM_base))

// ADC
#define ADC_ADDRESS	0x40034000
#define ADC_Type	((ADC_TypeDef*) ADC_ADDRESS)
#define IOCON_P0_23	*((volatile uint32_t*)(0x4002C05CUL))	 //ADC0[0] P0[23]

#define UART1_base 0x40010000
#define UART1	((UART1_Typedef*) UART1_base)

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
  	volatile uint32_t MR4;
  	volatile uint32_t MR5;
  	volatile uint32_t MR6;
    volatile uint32_t PCR;
    volatile uint32_t LER;
    volatile uint32_t reserved2[8]; 
    volatile uint32_t CTCR;
} PWM_Typedef;

typedef struct{
 volatile uint32_t RBR;
 volatile uint32_t THR;
 volatile uint32_t DLL;
 volatile uint32_t DLM;
 volatile uint32_t IER;
	volatile uint32_t LCR;
}UART1_Typedef;


typedef struct{
 volatile uint32_t DIR;
 uint32_t reserved[3];
 volatile uint32_t MASK;
 volatile uint32_t PIN;
 volatile uint32_t SET;
 volatile uint32_t CLR;
}GPIO_Type;

typedef struct {
  volatile	uint32_t CR;
  volatile	uint32_t GDR;
						uint32_t RESERVED0;
  volatile	uint32_t INTEN;
  volatile	uint32_t DR[8];
  volatile	uint32_t STAT;
  volatile	uint32_t TRM;
}ADC_TypeDef;

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
	uint32_t reserved0[2];
	volatile uint32_t EMR;
	uint32_t reserved1[12];
	volatile uint32_t CTCR;
}TIMER_TypeDef;

void timerInit() {
	PCONP |= PCONP_TIMER;
	
	IOCON_P1_27 |=  (3);
	IOCON_P1_27 &= ~(4);

	TIMER0->CTCR &= ~3;
	
	TIMER0->TCR &= ~1; 
	TIMER0->TCR |=  2; 
	
	TIMER0->PR = 59;
	TIMER0->CCR |= (7 << 3); 
	
	TIMER0->TCR &= ~2; 
	TIMER0->TCR |=  1; 
	
	NVIC_EnableIRQ(TIMER0_IRQn); //  TIMER0 

}

void pwmInit(){
  PCONP |= 1<<5;
  
  IOCON_P3_16 |= 2;
  IOCON_P3_16 &= ~(5);
  
  PWM_Type->PR = 59; 
	PWM_Type->PCR = 0; 
	PWM_Type->MR0 = 15000; 
	PWM_Type->MR1 = 5000; 
	PWM_Type->MCR = 2; 
	PWM_Type->LER = 3; 
	PWM_Type->PCR = (1<<9);
	PWM_Type->TCR = 2; 
	PWM_Type->TCR = 9;   
}

void adcInit(){

	PCONP |= PCONP_ADC;
	
	IOCON_P0_23 |= 	(1);		
  IOCON_P0_23 &= ~(6);						
  
  IOCON_P0_23 &= ~(3<<3);
	IOCON_P0_23 &= ~(1<<7);
	
	ADC_Type->INTEN |= (1 << 0);
	ADC_Type->CR = (1 << 0) | (4 << 8) | (1 << 21) | (1 << 24);
	
	NVIC_EnableIRQ(ADC_IRQn);
}

typedef enum {false, true} bool;

static char password[4] = {'1','2','3','4'};
static char numpad[12] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
static int attempts = 0;
static bool check = false;
static int state = 0;
static int number = 0;
static int beepPulse = 10;
static int ldr_value = 0;

void UARTInit(){

	
	UART1->LCR= (0x0080);
	
	UART1->IER= (0x0001);

}

void init() {
	// allow IOCON by updating PCONP 15th bit
	PCONP |= 1<<15;
	
	// set inputs and outputs
	// Rows of numpad grid, input
	GPIO0->DIR |= 1<<0;
	GPIO0->DIR |= 1<<1;
	GPIO0->DIR |= 1<<2;
	GPIO0->DIR |= 1<<3;
	// Colums of numpad grid, output
	GPIO0->DIR &= ~(1<<4);
	GPIO0->DIR &= ~(1<<5);
	GPIO0->DIR &= ~(1<<6);
	// LED ligthing of numpad, output
	GPIO0->DIR |= 1<<7;
	// LDR, input
	GPIO0->DIR &= ~(1<<8);
	// Relay (lock/unlock), output
	GPIO0->DIR |= 1<<9;
	// Tack switch (open/closed), input
	GPIO0->DIR &= ~(1<<10);
	// Buzzer, output
	GPIO0->DIR |= 1<<11;
	// Message sending, output
	GPIO0->DIR |= 1<<12;
	// Timer, output
  timerInit();
	GPIO0->DIR |= 1<<13;
	
	// initialize outputs
	// initialize Colums of numpad as zero
	GPIO0->PIN &= ~(1<<4);
	GPIO0->PIN &= ~(1<<5);
	GPIO0->PIN &= ~(1<<6);
	// LEDs off initially
	GPIO0->PIN &= ~(1<<7);
	// Relay (lock/unlock) init as locked
	GPIO0->PIN |= 1<<9;
	
	
}


void getInput() {
	while(1){
  	// check rows for 0 value
    // check whic column is low
    // decide which button is pressed
    	if((GPIO0->PIN|~(1<<0))!=~(1<<0)){ //check row 1 is HIGH
        if(state % 3 == 0){
      		number = 0;
          break;
        }
        else if(state % 3 == 1){
      		number = 1;
          break;
        }
        else if(state % 3 == 2){
      		number = 2;	
        	break;
        }
        
      }
      else if((GPIO0->PIN|~(1<<1))!=~(1<<1)){ //check row 2 is HIGH
        if(state % 3 == 0){
      		number = 3;
          break;
        }
        else if(state % 3 == 1){
      		number = 4;
          break;
        }
        else if(state % 3 == 2){
      		number = 5;
          break;
        }
      }
  		else if((GPIO0->PIN|~(1<<2))!=~(1<<2)){ //check row 3 is HIGH
        if(state % 3 == 0){
      		number = 6;
          break;
        }
        else if(state % 3 == 1){
      		number = 7;
          break;
        }
        else if(state % 3 == 2){
      		number = 8;
          break;
        }
      }  
 			else if((GPIO0->PIN|~(1<<3))!=~(1<<3)){ //check row 4 is HIGH
        if(state % 3 == 0){
      		number = 9;
          break;
        }
        else if(state % 3 == 1){
      		number = 10;
          break;
        }
        else if(state % 3 == 2){
      		number = 11;
          break;
        }
      }
    
  }
}

void stateChange(){
	if(state % 3 == 0){ // state of 011
  	GPIO0->PIN &= ~(1<<4);
    GPIO0->PIN |= (1<<5);
    GPIO0->PIN |= (1<<6);
  }
	else if(state % 3 == 1){ // state of 101
  	GPIO0->PIN |= (1<<4);
    GPIO0->PIN &= ~(1<<5);
    GPIO0->PIN |= (1<<6);
  }
  else if(state % 3 == 2){ // state of 110
  	GPIO0->PIN |= (1<<4);
    GPIO0->PIN |= (1<<5);
    GPIO0->PIN &= ~(1<<6);
  }

}

void ADC_IRQHandler(void){
	
	ldr_value = ADC_Type->DR[0] >> 4; // 
	if(ldr_value >= 0x100)
		GPIO0->PIN |= (1<<11);
	else
		GPIO0->PIN &= ~(1<<11);
}


void TIMER0_IRQHandler(){
  if(state > 1001) state = 0;
  state = state + 1;
	stateChange();
  
  TIMER0->IR |= (1<<2);
  TIMER0->TCR |= (1<<1);
  TIMER0->TCR &= ~(1<<1);
  
}

void beep(){
  int count = 0;
  while(count < beepPulse){
  	while(PWM_Type->TC < PWM_Type->MR0){
    	PWM_Type->LER = (1<<1);
    }
  }
	
}
void getPassword(){
  int i = 0;
  check = true;
  
  for(i = 0 ; i < 4; i = i+1){ // get four number
  	getInput();
    if(password[i] != numpad[number]){ // if wrong number encountered check becomes false
    	check = false;
    }
  }
  if(check){ // if password correct unlock
  	GPIO0->PIN |= 1<<9;
    attempts = 0;
  }
  else{    // if password is wrong, beep and increment number of attempts
    beep();
  	attempts = attempts + 1;
  }
}

void resetPassword(){
	getPassword(); // first get correct password
  if(check){     // if entered password correct, get new password
		int i = 0;
  	for(i = 0 ; i < 4; i = i+1){
      getInput();
      password[i] = numpad[number];     
  	}
  }
  else{         // if entered password is wrong, beep and reset states
  	beep();
  	//reset();
  }
}


void update() {
	// check door input and lock if door is closed
	if((GPIO0->PIN|~(1<<10))!=~(1<<10)){ //check if door closed
		GPIO0->PIN |= 1<<9; // Turn on LEDs
 }
  
	// check LDR input and turn on/off the light
	if((GPIO0->PIN|~(1<<8))!=~(1<<8)){ //check if LDR pin is 1
		GPIO0->PIN |= 1<<7; // Turn on LEDs
 } else {
		GPIO0->PIN &= ~(1<<7); //Turn off LEDs
 }
  // get input
  getInput();// get * or # firstly (* for unlocking the door, # for resetting password)
  if(numpad[number] == '*' && attempts < 3){ // if * and number of attempts is less than 3, get password
  	getPassword();
  }
	else if(attempts == 3){ // send message
		UART1->THR |= (1<<12);
		attempts = 0;
	}
  else if(numpad[number] == '#'){
  	resetPassword();
  }
  //
	
}
int main() {
	init();
  timerInit();
  adcInit();
  pwmInit();
  __enable_irq();
	while(1){
		update();
	}
}


