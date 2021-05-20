#include "LPC407x_8x_177x_8x.h"
int millisecond = 2004;
void init() {
LPC_GPIO1->CLR = 1 << 18;
LPC_GPIO1->DIR |= 1 << 18;
LPC_IOCON->P1_18 &= ~(0x3 << 3);
LPC_IOCON->P1_18 |= (0 & 0x3) << 3;
}
void update() {
int i;
LPC_GPIO1->SET = 1 << 18;
for(i=0;i<millisecond*2000;i++);
LPC_GPIO1->CLR = 1 << 18;
for(i=0;i<millisecond*2000;i++);
}
int main() {
init();
while(1) {
update();
}
}
