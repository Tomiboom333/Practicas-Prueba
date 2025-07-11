#include "stm32f103xb.h"
#include "est.h"

int teclado[4][3]={
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {1,0,1}
};

int leds[2]={7,8};//PB
int filas[4]={8,9,10,11};//PA
int columnas[4]={12,13,14,15};//PA
int numero[3];
int contador = 0;
int espacio;
volatile int autos = 0;
void estInit(){
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    for(int i =0; i<4;i++){
        GPIOA -> CRH &= ~(0xF << (filas[i]%8)*4);
        GPIOA-> CRH |= (0b0001 << (filas[i]%8)*4);
    }
    for(int = 0;i<3;i++){
        GPIOA -> CRH &= ~(0xF << (columnas[i]%8)*4);
        GPIOA-> CRH |= (0b1000 << (columnas[i]%8)*4);
    }
    GPIOB-> CRL &= ~(0xF << leds[0]*4);
    GPIOB-> CRL |= (0b0001 << leds[0]*4);
    GPIOB-> CRH &= ~(0xF << (leds[1]%8)*4);
    GPIOB-> CRH |= (0b0001 << (leds[1]%8)*4);

    for(int i=0;i<4;i++){
        GPIOA -> BSRR |= (1<<filas[i]);
        GPIOA -> BSRR |= (1<<columnas[i]);
    }
}
void estModo(char modo){
    if(modo = 'L'){
        GPIOB -> BSRR |= (1<<leds[0]+16);
        GPIOB -> BSRR |= (1<<leds[1]);//verde
    }
    if(modo = 'R'){
        GPIOB -> BSRR |= (1<<leds[0]);
        GPIOB -> BSRR |= (1<<leds[1]+16);//verde
    }
    if(modo = 'N'){
        while(contador <3){
            for(int i=0;i<4;i++){
            GPIOA->BSRR|=(1<<(filas[i] + 16));
                for(int j=0;j<3;j++){
                    if (!(GPIOA->IDR & (1 << columnas[j]))){
                        switch(contador){
                            case 0: 
                                numero[0] = (teclado[i][j])*100;
                                contador++;
                            break;
                            case 1: 
                                numero[1] = (teclado[i][j])*10;
                                contador++;
                            break;
                            case 2: 
                                numero[2] = (teclado[i][j]);
                                contador++;
                            break;
                        }
                    }
                }
            GPIOA->BSRR |= (1 << filas[i]);//prendo la fila apagada
            }
        delay_ms(5);
        }
        espacio = numero[0] + numero[1] + numero[2];
        if(autos > espacio){
            GPIOB -> BSRR |= (1<<leds[0]);
            GPIOB -> BSRR |= (1<<leds[1]+16);//verde
        }else{
            GPIOB -> BSRR |= (1<<leds[0]+16);
            GPIOB -> BSRR |= (1<<leds[1]);//verde
        }
    }
}
