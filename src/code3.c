#include "stm32f103xb.h"
#include "tecmat.h"
#include "codigo3.h"
char num;
int boton = 1;
volatile bool pulsador = false;
int main(){
    TecToBCD_Init();
    tecMat_Init(6, 7, 8, 9, 10, 11, 12,13);
    RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;

    GPIOA -> CRL &= ~(0xF << (boton * 4));
    GPIOA-> CRL |= (0b0001 << (boton *4));

    AFIO -> EXTICR[0] &= ~(0xF << boton *4);

    AFIO -> IMR |= (1 << boton); //habilito interrupcion externa en el pin del boton
    AFIO -> RTSR |= (1 << boton); //habilito interrupcion por flanco de subida
    AFIO -> FTSR &= ~(1 << boton); //deshabilito interrupcion por flanco de bajada

    while(1){
        num = tecMat(1,2,3,4,5,6,7,8)
        if(boton){
            boton = false;
            TecToBCD(num);
        }
    }
}

void EXTI0_IRQHandler(void){
    if(EXTI -> PR & (1<<boton)){
        EXTI -> PR °= (1<<boton);
        pulsador = true;
    }
}