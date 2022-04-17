#include "mbed.h"        
                //LSB                             MSB
BusOut DATOS(PA_3, PA_4, PA_5, PA_6, PA_7, PB_0, PB_1, PB_10);
DigitalOut ENABLES (PA_2); // Pin de Enable para generar el pulso para realizar la accion
DigitalOut RS (PA_1);

BusOut LEDS (PB_12,PB_13,PB_14,PB_15,PA_8,PA_9,PA_10,PA_11,PA_12,PA_15,PB_3,PB_4,PB_5,PB_6,PB_7,PB_8);
BusOut Col_1 (PB_15, PA_8, PB_4, PB_5);
BusOut Col_2 (PB_14, PA_9, PB_3, PB_6);
BusOut Col_3 (PB_13, PA_10, PA_15, PB_7);
BusOut Col_4 (PB_12, PA_11, PA_12, PB_8);
BusOut access (PB_5,PB_4,PA_8,PB_14,PB_13,PA_11,PA_12,PB_8,PB_3,PA_15);
BusOut NO_access (PA_9,PA_15);

BusIn  SW1(PC_13,PC_14,PC_15,PA_0);
BusIn BTN1(PB_11);

char MSJ_1[30];
char MSJ_2[30];
char MSJ_3[20];
char MSJ_4[25];
char MSJ_5[25];
int POS_MSJ1[30]={197,149,160,200,155,162,201,151,159,198,158,161,195,196,152,153,157,154,150,203,199,148,202};
char psw[4]={0,0,0,0};

void INIT_LCD(void);
void LCD_INSTRUCTION (uint8_t COMANDO);
void SHOW_IN_LCD (uint8_t CARACTER);
void WELCOME(void);
void SET_PSW(void);
void CHECK_PSW(void);
void anti_rebote(void);

//---------------------------------------------------------------------------------------------


int main()
{
 
    INIT_LCD();
    WELCOME();
    SET_PSW();
    while(1)
    {
        CHECK_PSW();
    }
}


//------------------------------------------------------------
void LCD_INSTRUCTION (uint8_t COMANDO)
{
    RS      = 0;
    ENABLES  = 0;
    DATOS   = COMANDO;
    
    ENABLES  = 1;
    wait_us(1);
    ENABLES  = 0;
    
    wait_ms(2);
}
//------------------------------------------------------------
void SHOW_IN_LCD (uint8_t CARACTER)
{
    RS      = 1;
    //RW    = 0;
    ENABLES  = 0;
    DATOS   = CARACTER;
    
    ENABLES  = 1;
    wait_us(1);
    ENABLES  = 0;
    
    wait_ms(2);
}

//------------------------------------------------------------
void WELCOME(void){
    uint8_t i;
    uint8_t len = 0;
    len = sprintf(MSJ_1,"QETTYMAUSUYEPARISTCSIS'");//PAQUITA'S SECURITY SYSTEM
    for(i=0; i<len; i++)
    {
        LCD_INSTRUCTION(POS_MSJ1[i]);
        SHOW_IN_LCD(MSJ_1[i]);
        wait_ms(250);
    }
    
    for(i=0; i<40;i++)
    {
        LCD_INSTRUCTION(0b00011000);
        wait_ms(100);
    }
    
    wait_ms(3000);
    LCD_INSTRUCTION(1);    
}
//------------------------------------------------------------
void SET_PSW(void){
    uint8_t i,psw_en ;
    uint8_t len = 0;
    len = sprintf(MSJ_2,"ESTABLECERCONTRASENA:");
    LCD_INSTRUCTION(193);
    for(i=0;i<len;i++)
    {
        SHOW_IN_LCD(MSJ_2[i]);
        if(i==9){LCD_INSTRUCTION(149);}
    }
    psw_en = 0;
    while(psw_en<4)
    {
        anti_rebote();
        
        if(SW1 < 10){psw[psw_en] = (SW1+48);}
        else{psw[psw_en] = (SW1+55);}
        
        SHOW_IN_LCD(psw[psw_en]);
        switch(psw_en)
        {
            case 0:
                Col_1= 0b1111;
                break;
            case 1:
                Col_2=0b1111;
                break;
            case 2:
                Col_3=0b1111;
                break;
            case 3:
                Col_4=0b1111;
                break;
            default:
                break;       
        }
        psw_en++;
    }
    wait_ms(5000);
    LCD_INSTRUCTION(1);
    LEDS= 0;
}
//------------------------------------------------------------
void CHECK_PSW()
{
 
 LCD_INSTRUCTION(193);
 uint8_t len = 0;
 uint8_t count, digito,i;
 bool same_psw = true;
 len = sprintf(MSJ_3,"INGRESECLAVE:");
 
 LCD_INSTRUCTION(193);
 for(i=0; i<len;i++)
 {
    SHOW_IN_LCD(MSJ_3[i]);
    if(i==6){LCD_INSTRUCTION(149);}
 }
    count = 0;
    digito; 
    while(count<4)
    {
        anti_rebote();
        SHOW_IN_LCD(42);//*
    
    if(SW1 < 10){digito = (SW1+48);}
        else{digito = (SW1+55);}

        if(psw[count]!=digito){same_psw=false;}
        count++;
    }
    wait_ms(500);
    LCD_INSTRUCTION(1);
    if(same_psw){
        len = sprintf(MSJ_5,"LA CLAVE ES CORRECTA");
        access = 0b1111111111;
        LCD_INSTRUCTION(192);
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ_5[i]);
        }
    }else{
        len = sprintf(MSJ_4,"LA CLAVE ESINCORRECTA");
        NO_access = 0b11;
        Col_1 = Col_4 = 0b1111;
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ_4[i]);
            if(i==10){LCD_INSTRUCTION(149);}
        }
    }
    wait_ms(5000);
    LCD_INSTRUCTION(1);
    LEDS = 0;
}
//------------------------------------------------------------
void INIT_LCD(void)
{
    wait_ms(50);
    LCD_INSTRUCTION(0b00110000);
    
    wait_ms(25);
    LCD_INSTRUCTION(0b00110000);
    
    wait_ms(1);
    LCD_INSTRUCTION(0b00110000);
    
    LCD_INSTRUCTION(0b00111000);  
    LCD_INSTRUCTION(0b00001111);  
    LCD_INSTRUCTION(0b00001110);
    LCD_INSTRUCTION(0b00000001);    
}

//------------------------------------------------------------
void anti_rebote(void){
    while(BTN1){}
    wait_ms(40);
    while(!BTN1){}
    wait_ms(40);
}