#include <stm32f103xb.h>
#include <stdbool.h>
#include "delay.h"
#include "ituzaingo.h"
#define SENSOR1 4
#define SENSOR2 5
int sens[2]={0,1}
volatile int autos=0;
int boton[3]={4,5,6};
char modo;
int main(void){
    estInit();
    RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;

    for(int i = 0;i<2;i++){
        GPIOA -> CRL &= ~(0xF << sens[i]*4);
        GPIOA -> CRL |= (0b0100 << sens[i]*4);
        AFIO -> EXTICR[0] &= ~(0xF << sens[i]*4);
        EXTI -> IMR|= (1<<sens[i]*4);
        EXTI -> RTSR|= (1<<sens[i]*4);
        EXTI -> FTSR &= ~(1<<sens[i]*4);
    }
    for(int i = 0;i<3;i++){
        GPIOA -> CRL &= ~(0xF << boton[i]*4);
        GPIOA -> CRL |= (0b0100 << boton[i]*4);
        AFIO -> EXTICR[1] &= ~(0xF << (boton[i]%4)*4);
        EXTI -> IMR|= (1<<boton[i]*4);
        EXTI -> RTSR|= (1<<boton[i]*4);
        EXTI -> FTSR &= ~(1<<boton[i]*4);
    }

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 1);

    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI1_IRQn, 1);

    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_SetPriority(EXTI4_IRQn, 1);

    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_SetPriority(EXTI9_5_IRQn, 1);

    while(1){
        switch(pulsador){
            case 1:
                estModo('N');
            break;
            case 2:
                estModo('L');
            break;
            case 3:
                estModo('R');
            break;
        }
    }
    return 0;
}
void EXTI0_IRQHanlder(void){
    if(EXTI->PR&(1<<sens[0])){
        EXTI->PR |= (1 << sens[0]);
        autos++;
    }
}
void EXTI1_IRQHanlder(void){
    if(EXTI->PR&(1<<sens[1])){
        EXTI->PR |= (1 << sens[1]);
        autos--;
    }
}
void EXTI4_IRQHanlder(void){
    if(EXTI->PR&(1<<sens[0])){
        EXTI->PR |= (1 << sens[0]);
        pulsador = 1;
    }
}
void EXTI9_5_IRQHanlder(void){
    if(EXTI->PR&(1<<sens[1])){
        EXTI->PR |= (1 << sens[1]);
        pulsador = 2;
    }
    if(EXTI->PR&(1<<sens[2])){
        EXTI->PR |= (1 << sens[1]);
        pulsador = 3;
    }
}
