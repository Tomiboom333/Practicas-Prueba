#include "stm32f103xb.h"
#include "tecMat.h"
char teclado[4][4]={
    {'1','2','3','A'},
    {'4','5','6','B'},    
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void tecMat_Init(int f1, int f2, int f3, int f4, int c1, int c2, int c3, int c4){

    RCC -> APB2ENR|=RCC_APB2ENR_IOPAEN;//habilito clocks

    //configuracion de filas y columnas
    int filas[4]={f1,f2,f3,f4};
    int columnas[4]={c1,c2,c3,c4};

    for(int i = 0;i<4;i++){
        if(columnas[i]<8){
            GPIOA -> CRL &= ~(0xF<<(columnas[i]* 4));
            GPIOA->CRL |=  (1 << ((columnas[i] * 4)+3));
            GPIOA -> BSRR |= (1<<columnas[i]);
        }else{
            GPIOA -> CRH &= ~(0xF<<(columnas[i] % 8)*4);
            GPIOA->CRH |=  (1 << (((columnas[i] % 8)*4)+3));//input pull up
            GPIOA -> BSRR |= (1<<columnas[i]);
        }

        if(filas[i]<8){
            GPIOA -> CRL &= ~(0xF<<(filas[i]* 4));
            GPIOA->CRL |=  (1 << (filas[i] * 4));
        }else{
            GPIOA -> CRH &= ~(0xF<<(filas[i] % 8)*4);
            GPIOA->CRH |=  (1 << ((filas[i] % 8)*4));// output push-pull
        }
        GPIOA -> BSRR |= (1<<columnas[i]);
    }
}

char tecMat(int f1, int f2, int f3, int f4, int c1, int c2, int c3, int c4){
    int filas[4]={f1,f2,f3,f4};
    int columnas[4]={c1,c2,c3,c4};

    for(int i=0;i<4;i++){
        GPIOA->BSRR|=(1<<(filas[i] + 16));
        for(int j=0;j<4;j++){
            if (!(GPIOA->IDR & (1 << columnas[j]))) return teclado[i][j];
        }
        GPIOA->BSRR |= (1 << filas[i]);//prendo la fila apagada
    }
    return 'x';
}