#include "LPC407x_8x_177x_8x.h"

#define GPIO_base 0x20098000
#define GPIO0 ((GPIO_TypeDef *)(GPIO_base + 0x000)) //0x20098000
#define GPIO1 ((GPIO_TypeDef *)(GPIO_base + 0x020)) //0x20098020
#define GPIO2 ((GPIO_TypeDef *)(GPIO_base + 0x040)) //0x20098040
#define GPIO3 ((GPIO_TypeDef *)(GPIO_base + 0x060)) //0x20098060
#define GPIO4 ((GPIO_TypeDef *)(GPIO_base + 0x080)) //0x20098080
#define GPIO5 ((GPIO_TypeDef *)(GPIO_base + 0x0A0)) //0x200980A0

#define IOCON_P1_5 *((volatile uint32_t *) 0x4002C094UL)
#define IOCON_P1_6 *((volatile uint32_t *) 0x4002C098UL)
#define IOCON_P1_7 *((volatile uint32_t *) 0x4002C09CUL)
#define IOCON_P1_11 *((volatile uint32_t *) 0x4002C0ACUL)
#define IOCON_P1_3 *((volatile uint32_t *) 0x4002C08CUL)
#define IOCON_P1_23 *((volatile uint32_t *) 0x4002C0DCUL)
#define IOCON_P1_24 *((volatile uint32_t *) 0x4002C0E0UL)
#define IOCON_P0_25 *((volatile uint32_t *) 0x4002C064UL)

#define PCONP *((volatile uint32_t *) 0x400FC0C4UL)

#define OFFSET_A 5
#define OFFSET_B 6
#define OFFSET_C 7
#define OFFSET_D 11
#define OFFSET_E 3
#define OFFSET_F 23
#define OFFSET_G 24
#define OFFSET_TEMP 25
	
static const uint32_t a = (uint32_t)(1<<OFFSET_A);
static const uint32_t b = (uint32_t)(1<<OFFSET_B);
static const uint32_t c = (uint32_t)(1<<OFFSET_C);
static const uint32_t d = (uint32_t)(1<<OFFSET_D);
static const uint32_t e = (uint32_t)(1<<OFFSET_E);
static const uint32_t f = (uint32_t)(1<<OFFSET_F);
static const uint32_t g = (uint32_t)(1<<OFFSET_G);

static const uint32_t temp = ((uint32_t)(1<<OFFSET_TEMP));

static const uint32_t seven_segment[10]= {(g), (a+b+c+d+g), (f+c), (f+e), (a+e+d), (b+e), (b), (d+e+f+g), 0, (e)};

int millisecond = 3000;


typedef struct{
	volatile 	uint32_t 	DIR;
						uint32_t 	reserved[3];
	volatile 	uint32_t 	MASK;
	volatile 	uint32_t 	PIN;
	volatile 	uint32_t 	SET;
	volatile 	uint32_t 	CLR;
}GPIO_TypeDef;

void LED_Init(){
	int j;
	int key = 0;
	int t = 0;
	uint32_t check;
	
	while(1){
		
		check = GPIO0->PIN & temp;
		GPIO3->PIN = check;
		for(j=0;j<millisecond*2000;j++);
		if(check == temp){
			t = 0;
			key++;
			key %= 10;
			GPIO1->PIN = seven_segment[key];
		}
		else{
			key = 0;
			if(t == 0){
				GPIO1->PIN = seven_segment[key];
				t = 1;
			}
			
		}
	}
	
}

void init(){
	
	PCONP |= (1<<15);
	IOCON_P1_5 &= ~(1<<2|1<<1|1);
	IOCON_P1_6 &= ~(1<<2|1<<1|1);
	IOCON_P1_7 &= ~(1<<2|1<<1|1);
	IOCON_P1_11 &= ~(1<<2|1<<1|1);
	IOCON_P1_3 &= ~(1<<2|1<<1|1);
	IOCON_P1_23 &= ~(1<<2|1<<1|1);
	IOCON_P1_24 &= ~(1<<2|1<<1|1);
	IOCON_P0_25 &= ~(1<<2|1<<1|1);
	
	GPIO1->DIR |= (uint32_t)(1 << OFFSET_A |1 << OFFSET_B |1 <<OFFSET_C |1 <<OFFSET_D |1<<OFFSET_E |1<<OFFSET_F |1<<OFFSET_G);
	GPIO0->DIR &= ~(1 << OFFSET_TEMP);
	GPIO1->PIN = g;
	
}

void update() {
	LED_Init();
}

int main() {
	init();
	update();
}