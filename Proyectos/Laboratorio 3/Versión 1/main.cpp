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

char MSJ_1[30];
char MSJ_2[30];
char MSJ_3[20];
char MSJ_4[25];
char MSJ_5[25];
int POS_MSJ1[30]={133, 195, 197, 204, 132, 139, 202, 192, 198, 193, 206, 131, 199, 205, 194, 135, 201, 196, 134, 203, 136, 138, 137};
char  psw[4] = {0,0,0,0};

char CADENA[500];
uint8_t INDICE = 0;
char RX;

void INIT_LCD(void);
void LCD_INSTRUCTION (uint8_t COMANDO);
void SHOW_IN_LCD (uint8_t CARACTER);
void WELCOME(void);
void SET_PSW(void);
void CHECK_PSW(void);

int main()
{
    INIT_LCD();
    WELCOME();
   
    FTDI.printf("\n\rBienvenido!");
    FTDI.printf("\n\rPaquita's security system");
    FTDI.printf("\n\rEstableciendo contrasena...");
    
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
    len = sprintf(MSJ_1,"QUITASYSTEMPYECISRUST'A");//PAQUITA'S SECURITY SYSTEM
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
//--------------------------------------------------
void SET_PSW(void){
    uint8_t i,count ;
    uint8_t len = 0;
    len = sprintf(MSJ_2,"ESTABLECERCONTRASENA:");
    LCD_INSTRUCTION(193);
    for(i=0;i<len;i++)
    {
        SHOW_IN_LCD(MSJ_2[i]);
        if(i==9){LCD_INSTRUCTION(149);}
    }
    count = 0;
    
    FTDI.printf("\n\rIngrese el 1 simbolo: ");
    while(count<4)
    {
        if(FTDI.readable()) // Ha llegado algun dato al buffer de RX
        {
                psw[count] = FTDI.getc();
                SHOW_IN_LCD(psw[count]);
                count++;
                if(count<4){FTDI.printf("\n\rIngrese el %i simbolo: ",(count+1));}    
        }
    }
    FTDI.printf("\n\rContraseña establecida con exito!!\n\r");
    for(i=0;i<4;i++){FTDI.printf("%c",psw[i]);}
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
 len = sprintf(MSJ_3,"INGRESECLAVE:");
 BT.printf("\n\rBIENVENIDO!");
 
 LCD_INSTRUCTION(193);
 for(i=0; i<len;i++)
 {
    SHOW_IN_LCD(MSJ_3[i]);
    if(i==6){LCD_INSTRUCTION(149);}
 }
    count = 0;
    BT.printf("\n\rIngrese el 1 simbolo: ");
    while(count<4)
    {
        if(BT.readable()) // Ha llegado algun dato al buffer de RX
        {
            if(psw[count]!=BT.getc()){same_psw=false;}
            SHOW_IN_LCD('*');
            count++;
            if(count<4){BT.printf("\n\rIngrese el %i simbolo: ",(count+1));}    
        }
    }
    wait_ms(500);
    LCD_INSTRUCTION(1);
    if(same_psw){
        len = sprintf(MSJ_5,"LA CLAVE ES CORRECTA");
        BT.printf("\n\rACCESO PERMITIDO");
        FTDI.printf("\n\rACCESO PERMITIDO");
        LCD_INSTRUCTION(192);
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ_5[i]);
        }
    }else{
        len = sprintf(MSJ_4,"LA CLAVE ESINCORRECTA");
        BT.printf("\n\rACCESO DENEGADO");
        FTDI.printf("n\rACCESO DENEGADO");
        for(i=0;i<len;i++)
        {
            SHOW_IN_LCD(MSJ_4[i]);
            if(i==10){LCD_INSTRUCTION(149);}
        }
    }
    wait_ms(5000);
    LCD_INSTRUCTION(1);
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