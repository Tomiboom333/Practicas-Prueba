//el tren de la estacion de ituzaingo pasa por la estacion. A 100 metros de la estacion, hay un sensor que detecta su presencia. 
//AL detectarlo, debe abrir una barrera, y luego de 10 segundos, debe cerrarla. realizar el codigo con un stm32, con cmsis e interrupciones. Hacer libreria para los motores PaP
#include "estacion.h"
#include <stdbool.h>
#include "stm32f103xb.h"
int Cmotor[4]= {2,3,4,5};
int pasoN[4][4]={
    {1,1,0,0},
    {0,1,1,0},
    {0,0,1,1},
    {1,0,0,1}
};
int pasos, pasoActual;
volatile int direccion = 0;
void motor_Init() {
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
    for(int i = 0;i < 4;i++){
        GPIOA -> CRL &= ~(0xF <<(Cmotor[i])*4);
        GPIOA -> CRL |= (0b0001<<(Cmotor[i]*4));//floating input
    }
}
void motor(float grados){
    pasos = (int)(grados/1.8);
    switch (direccion){
        case 1:
        delay_ms(10000);
        for(int i = 0; i<pasos ;i++){
            pasoActual = i%4;
            for(int j=0;j<4;j++){
                if(pasoN[pasoActual][j]) GPIOA -> BSRR |= (1<< Cmotor[j]);
                else GPIOA -> BSRR |= (1<< (Cmotor[j]+ 16));
            }
            delay_ms(5);
        }             
        break;

        case 2:
        for(int i = 0; i <pasos;i++){
            pasoActual = 3-(i%4);
            for(int j=0;j<4;j++){
                if(pasoN[pasoActual][j]) GPIOA -> BSRR |= (1<< (Cmotor[j]));
                else GPIOA -> BSRR |= (1<< Cmotor[j]+16);
            }
            delay_ms(5);
        }
        break;

        default:
        break;
    }
}