#include "estacion.h"
#include <stdbool.h>
#include "stm32f103xb.h"
int sens[2]={0,1};
volatile int barrera;
int main(void){
    motor_Init();
    
    for(int i = 0;i<2;i++){
        GPIOA -> CRL &= ~(0xF << (sens[i]*4));//input push-pull
        GPIOA -> CRL |= (1<<(sens[i]*4));
        AFIO -> EXTICR[0] &= (0xF << (sens[i]*4));
        EXTI -> IMR |= (1<<sens[i]);
        EXTI -> RTSR &= ~(1<<sens[i]);
        EXTI -> FTSR |= (1<<sens[i]);
    }

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI0_IRQn,1);
    NVIC_SetPrority(EXTI1_IRQn,1);
    while(1){
        if(barrera = 1) motor(0);
        if(barrera = 2) {
            delay_ms(10000);
            motor(60);
        }
        barrera = 0;
    }
    return 0;
}

void EXTI0_IRQHandler(void){
    if(EXTI -> PR & (1<< sens[0])){
        EXTI -> PR |= (1<< sens[0]);
        barrera = 1;
    }
}
void EXTI1_IRQHandler(void){
    if(EXTI -> PR & (1<< sens[1])){
        EXTI -> PR |= (1<< sens[1]);
        barrera = 2;
    }
}