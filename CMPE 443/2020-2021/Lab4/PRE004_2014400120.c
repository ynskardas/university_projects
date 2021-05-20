#include "LPC407x_8x_177x_8x.h"
#include <stdbool.h> 

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

#define OFFSET_A 13
#define OFFSET_B 2
#define OFFSET_C 13
#define OFFSET_D 28
#define OFFSET_E 8
#define OFFSET_F 14
#define OFFSET_G 8
#define OFFSET_TEMP 27


#define PORT_A_DIR GPIO1 -> DIR
#define PORT_0 GPIO0 -> PIN
#define PORT_B_DIR GPIO3 -> DIR
#define PORT_1 GPIO1 -> PIN
#define PORT_C_DIR GPIO3 -> DIR
#define PORT_2 GPIO2 -> PIN
#define PORT_D_DIR GPIO0 -> DIR
#define PORT_3 GPIO3 -> PIN
#define PORT_E_DIR GPIO0 -> DIR
#define PORT_4 GPIO4 -> PIN
#define PORT_F_DIR GPIO3 -> DIR
#define PORT_5 GPIO5 -> PIN
#define PORT_G_DIR GPIO1 -> DIR


#define PORT_BUTTON_DIR GPIO3 -> DIR
#define PORT_BUTTON GPIO3 -> PIN
	
static const uint32_t a = (uint32_t)(1<<OFFSET_A);
static const uint32_t b = (uint32_t)(1<<OFFSET_B);
static const uint32_t c = (uint32_t)(1<<OFFSET_C);
static const uint32_t d = (uint32_t)(1<<OFFSET_D);
static const uint32_t e = (uint32_t)(1<<OFFSET_E);
static const uint32_t f = (uint32_t)(1<<OFFSET_F);
static const uint32_t g = (uint32_t)(1<<OFFSET_G);

static const uint32_t temp = ((uint32_t)(1<<OFFSET_TEMP));

static const uint32_t forA[7] = {e, a+g, 0, b+c+f, 0, 0};
static const uint32_t forB[7] = {d+e, a+g, 0, b+c+f, 0, 0};
static const uint32_t forC[7] = {d+e, a, 0, f, 0, 0};
static const uint32_t forD[7] = {d+e, a, 0, b+c+f, 0, 0};
static const uint32_t forE[7] = {d+e, a+g, 0, f, 0, 0};
static const uint32_t forF[7] = {e, a+g, 0, f, 0, 0};


static const uint32_t *seven_segment[6]= {forA, forB, forC, forD, forE, forF};

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
	int step = 1;
	int old = 0;
	int j;
	int key = 0;
	int t = 0;
	uint32_t check;
	bool pushed;
	bool init01;
	pushed = false;
	init01 = true;
	
	while(1){
		
		check = PORT_BUTTON & temp;
		for(j=0;j<millisecond*2000;j++);
		pushed = check == temp;
		
		if(pushed){
			step = 1;
		}
		else{
			if(old == 0){
				step = 2;
				old = 2;
			}
			else if(old == 2){
				step = 0;
				old = 0;
			}
		}
		
		if(step == 2){
			t = 0;
			key++;
			key %= 6;
					
			PORT_0 = seven_segment[key][0];
			PORT_1 = seven_segment[key][1];
			PORT_2 = seven_segment[key][2];
			PORT_3 = seven_segment[key][3];
			PORT_4 = seven_segment[key][4];
			PORT_5 = seven_segment[key][5];
			
		}
		else if(step == 0){
			key = 0;
			if(t == 0){
				
				PORT_0 = a;
					PORT_0 = seven_segment[key][0];
					PORT_1 = seven_segment[key][1];
					PORT_2 = seven_segment[key][2];
					PORT_3 = seven_segment[key][3];
					PORT_4 = seven_segment[key][4];
					PORT_5 = seven_segment[key][5];
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
	
	PORT_A_DIR |= (1<<OFFSET_A);
	PORT_B_DIR |= (1<<OFFSET_B);
	PORT_C_DIR |= (1<<OFFSET_C);
	PORT_D_DIR |= (1<<OFFSET_D);
	PORT_E_DIR |= (1<<OFFSET_E);
	PORT_F_DIR |= (1<<OFFSET_F);
	PORT_G_DIR |= (1<<OFFSET_G);
	
	PORT_BUTTON_DIR &= ~(1 << OFFSET_TEMP);
	
	PORT_0 = e;
	PORT_1 = a + g;
	PORT_2 = 0;
	PORT_3 = b + c + f;
	PORT_4 = 0;
	PORT_5 = 0;
	
	
	
	
}

void update() {
	LED_Init();
}

int main() {
	init();
	update();
}