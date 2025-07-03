#include "stm32f103xb.h"
#include "tecmat.h"
#include "codigo3.h"

int numeros[10][4]={
    {0,0,0,0},
    {0,0,0,1},
    {0,0,1,0},
    {0,0,1,1},
    {0,1,0,0},
    {0,1,0,1},
    {0,1,1,0},
    {0,1,1,1},
    {1,0,0,0},
    {1,0,0,1}
};

int leds[4]={1,2,3,4};
char num;

TecToBCD_Init(){
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN; // Habilito el reloj del puerto A
    for(int i = 0; i < 4; i++) {
        GPIOA -> CRL &= ~(0xF << leds[i]); // Limpio la configuracion de los pines
        GPIOA -> CRL |= (1 << (leds[i] * 4)); // Configuro los pines como salida push-pull
    }
}

TecToBCD(char num){
    switch(num){
        case '0':
            for(int i = 0; i < 4; i++) {
                if(numeros[0][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '1':
            for(int i = 0; i < 4; i++) {
                if(numeros[1][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '2':
            for(int i = 0; i < 4; i++) {
                if(numeros[2][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '3':
            for(int i = 0; i < 4; i++) {
                if(numeros[3][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '4':
            for(int i = 0; i < 4; i++) {
                if(numeros[4][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '5':
            for(int i = 0; i < 4; i++) {
                if(numeros[5][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '6':
            for(int i = 0; i < 4; i++) {
                if(numeros[6][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '7':
            for(int i = 0; i < 4; i++) {
                if(numeros[7][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '8':
            for(int i = 0; i < 4; i++) {
                if(numeros[8][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
        case '9':
            for(int i = 0; i < 4; i++) {
                if(numeros[9][i]) GPIOA->BSRR |= (1 << leds[i]);
                else  GPIOA->BSRR |= (1 << leds[i]+16);
            }
        break;
    }
}