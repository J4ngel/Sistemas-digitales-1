#include "mbed.h"

#define D0 PA_4
#define D1 PA_3
#define D2 PA_2
#define D3 PA_1
#define D4 PA_0
#define D5 PC_15
#define D6 PC_14
#define D7 PC_13

#define Tx1 PB_10
#define Rx1 PB_11

#define Tx2 PB_6
#define Rx2 PB_7

Serial BT(Tx1, Rx1);
Serial FTDI(Tx2, Rx2);

BusOut DATOS(D0,D1,D2,D3,D4,D5,D6,D7);
DigitalOut EN (PA_5);
DigitalOut RS (PA_6);

char MSJ[30];
uint8_t POS_MSJ1[30]={133, 195, 197, 204, 132, 139, 202, 192, 198, 193, 206, 131, 199, 205, 194, 135, 201, 196, 134, 203, 136, 138, 137};
const uint8_t SIZE_PSW = 20;
char  psw[SIZE_PSW];
char INPUT[SIZE_PSW];

void INIT_LCD(void);
void CLEAR_ARRAY(void);
void LCD_INSTRUCTION (uint8_t COMANDO);
void SHOW_IN_LCD (uint8_t CARACTER);
void WELCOME(void);
void SET_PSW(void);
void CHECK_PSW(void);

int main()
{
    INIT_LCD();
    CLEAR_ARRAY();
    WELCOME();
    SET_PSW();
    while(1)
    {
         CHECK_PSW();
    }
}
//-----------------FUNCTIONS------------------------
//-----------------SEQUENCES------------------------
void WELCOME(void)
{
    uint8_t i;
    uint8_t len = 0;
    
    FTDI.printf("\n\rBienvenido!");
    FTDI.printf("\n\rPaquita's security system");
    FTDI.printf("\n\rCargando...");
    len = sprintf(MSJ,"QUITASYSTEMPYECISRUST'A");//PAQUITA'S SECURITY SYSTEM
    for(i=0; i<len; i++)
    {
        LCD_INSTRUCTION(POS_MSJ1[i]);
        SHOW_IN_LCD(MSJ[i]);
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
//--------------------------------------------------
void SET_PSW(void){
    uint8_t i,count ;
    uint8_t len = 0;
    len = sprintf(MSJ,"ESTABLECERCONTRASENA:");
    LCD_INSTRUCTION(193);
    for(i=0;i<len;i++)
    {
        SHOW_IN_LCD(MSJ[i]);
        if(i==9){LCD_INSTRUCTION(149);}
    }
    
    FTDI.printf("\n\rIngrese la contraseña: ");
    FTDI.scanf("%s",psw);

    i=0;
    while(psw[i]!='\0' && psw[i]!='\n' && psw[i]!='\r')
    {
        SHOW_IN_LCD(psw[i]);
        i++;
    }
    FTDI.printf("Contraseña establecida con exito!!\n\r");
    wait_ms(5000);
    LCD_INSTRUCTION(1);
}
//--------------------------------------------------
void CHECK_PSW(void)
{
 
 LCD_INSTRUCTION(193);
 uint8_t len = 0;
 uint8_t count,i;
 bool same_psw = true;
 len = sprintf(MSJ,"INGRESECLAVE:");
 BT.printf("\n\rBIENVENIDO!");
 
 LCD_INSTRUCTION(193);
 for(i=0; i<len;i++)
 {
    SHOW_IN_LCD(MSJ[i]);
    if(i==6){LCD_INSTRUCTION(149);}
 }
    
    BT.printf("\n\rIngrese la contraseña: ");
    BT.scanf("%s",INPUT);
    FTDI.printf("\n\rSe digitó la siguiente contraseña: %s", INPUT);
    
    for(i=0; i<SIZE_PSW ; i++)
    {
        if(INPUT[i]!='\0' && INPUT[i]!='\n' && INPUT[i]!='\r'){SHOW_IN_LCD('*');}
        if(psw[i]!=INPUT[i]){same_psw=false;}
        
    }

    wait_ms(500);
    LCD_INSTRUCTION(1);
    if(same_psw){
        len = sprintf(MSJ,"LA CLAVE ES CORRECTA");
        BT.printf("\n\rACCESO PERMITIDO");
        FTDI.printf("---> ACCESO PERMITIDO");
        LCD_INSTRUCTION(192);
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ[i]);
        }
    }else{
        len = sprintf(MSJ,"LA CLAVE ESINCORRECTA");
        BT.printf("\n\rACCESO DENEGADO");
        FTDI.printf("---> ACCESO DENEGADO");
        LCD_INSTRUCTION(193);
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ[i]);
            if(i==10){LCD_INSTRUCTION(149);}
        }
    }
    wait_ms(5000);
    
    LCD_INSTRUCTION(1);
    for(i=0;i<SIZE_PSW;i++){INPUT[i]='\0';}
}
//-------------CLEAR ARRAY--------------------------
void CLEAR_ARRAY(void)
{
    uint8_t i;
    for(i=0; i<SIZE_PSW; i++)
    {
        psw[i]='\0';
        INPUT[i]='\0';
    }
}
//-------------LCD FUNCTIONS------------------------
void LCD_INSTRUCTION (uint8_t COMANDO)
{
    RS      = 0;
    EN  = 0;
    DATOS   = COMANDO;
    
    EN  = 1;
    wait_us(1);
    EN  = 0;
    
    wait_ms(2);
}

void SHOW_IN_LCD (uint8_t CARACTER)
{
    RS      = 1;
    //RW    = 0;
    EN  = 0;
    DATOS   = CARACTER;
    
    EN  = 1;
    wait_us(1);
    EN  = 0;
    
    wait_ms(2);
}

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