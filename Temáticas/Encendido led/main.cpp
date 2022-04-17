#include "mbed.h"
BusOut LEDS (PB_12,PB_13,PB_14,PB_15,PA_8,PA_9,PA_10,PA_11,PA_12,PA_15,PB_3,PB_4,PB_5,PB_6,PB_7,PB_8);

BusOut fun_1 (PA_9,PB_3,PB_6,PB_5,PB_4,PA_8,PB_15,PB_14,PB_13,PB_12,PA_11,PA_12,PB_8,PB_7,PA_15,PA_10);

BusOut aux1_fun_2 (PB_14,PA_9,PA_8,PB_4,PB_5,PB_3);
BusOut aux2_fun_2 (PB_7,PA_15,PA_12,PA_11,PB_12,PA_10);

BusOut aux1_fun_3 (PB_5,PB_4,PA_8,PB_15,PB_14,PB_13,PB_12);
BusOut aux2_fun_3 (PB_5,PB_6,PB_7,PB_8,PA_12,PA_11,PB_12);
BusOut aux3_fun_3 (PB_5,PB_4,PB_3,PA_9,PA_10,PB_13,PB_12);
BusOut aux4_fun_3 (PB_5,PB_6,PB_7,PA_15,PA_10,PA_11,PB_12);

BusOut fun_4 (PA_11,PB_13,PB_14,PA_8,PB_4,PB_6,PB_7,PA_12,PA_10,PA_9,PB_3,PA_15);

BusOut aux1_fun_5 (PA_8,PB_14,PA_10,PB_12,PA_11,PB_13,PA_9,PB_15);
BusOut aux2_fun_5 (PB_4,PB_6,PA_15,PB_8,PA_12,PB_7,PB_3,PB_5);

//BusIn  INTERRUPTOR(PC_13,PC_14,PC_15,PA_0);

void F1 (void);
void F2 (void);
void F3 (void);
void F4 (void);
void F5 (void);

int main(void)
{  
    LEDS = 0;
    uint8_t c = 0;
  while(1)
  {  
    switch (c)  
    {
        case 0  :F1() ;break;
        case 1  :F2() ;break;
        case 2  :F3() ;break;
        case 3  :F4() ;break;
        case 4  :F5() ;break;

        default :LEDS = 0;break;
    }
    if(c<5){
        c++;
    }else{c=0;}
    wait(2);
  }  
}

//FUNCIONES
void F1(void)
{
uint16_t state = 1;
uint8_t i = 0;

    fun_1 = 0; 

    wait_ms(400);
    
for(i=0;i<16;i++)
    {
        fun_1 = state;
        wait_ms(400);
        state = (state << 1)|1;    
    }
    
    state = 65534;

for(i=0;i<16;i++)
    {
        fun_1 = state;
        wait_ms(400);
        state = state << 1;    
    }
}

void F2(void)
{
uint16_t state = 1;
uint8_t i = 0;
    LEDS = aux1_fun_2 = aux2_fun_2 = 0; 
    
    wait_ms(400);
    
    for(i=0;i<6;i++)
    {
        aux1_fun_2 = state;
        aux2_fun_2 = state;
        wait_ms(400);
        state = (state << 1)|1;    
    }
    
    state = 31;

for(i=0;i<6;i++)
    {
        aux1_fun_2 = state;
        aux2_fun_2 = state;
        wait_ms(400);
        state = state >> 1;    
    }
}

void F3(void)
{
uint16_t state = 1;
uint8_t i = 0;

    aux1_fun_3 = aux2_fun_3 = aux3_fun_3 = aux4_fun_3 = 0; 

    wait_ms(400);
    
    for(i=0;i<7;i++)
    {
        aux1_fun_3 = aux2_fun_3 = aux3_fun_3 = aux4_fun_3 = state;
        wait_ms(400);
        state = (state << 1)|1;    
    }
    
    state = 63;

for(i=0;i<7;i++)
    {
        aux1_fun_3 = aux2_fun_3 = aux3_fun_3 = aux4_fun_3  = state;
        wait_ms(400);
        state = state >> 1;    
    }
}

void F4(void)
{
uint16_t state = 1;
uint8_t i = 0;

    LEDS = fun_4 = 0; 

    wait_ms(400);
    
    for(i=0;i<12;i++)
    {
        fun_4 = state;
        wait_ms(400);
        state = (state << 1)|1;    
    }
    
    state = 2047;

for(i=0;i<12;i++)
    {
        fun_4 = state;
        wait_ms(400);
        state = state >> 1;    
    }
}

void F5(void)
{
uint16_t state = 1;
uint8_t i = 0;

    LEDS = 0;
    
    wait_ms(400);
    
    for(i=0;i<16;i++)
    {
        LEDS = state;
        wait_ms(400);
        state = (state << 1)|1;    
    }
    
    state = 32767;

for(i=0;i<16;i++)
    {
        LEDS = state;
        wait_ms(400);
        state = state >> 1;    
    }
}