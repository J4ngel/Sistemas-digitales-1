#include "mbed.h"   


                  				 //(TX - RX);
Serial PUERTO_SERIAL(USBTX,USBRX) ;  //(PA_2,PA_3);

//Serial PUERTO_SERIAL2(PB_10,PC_11);

DigitalOut TESTIGO(LED1);

char CADENA[500];// = {"\n\r Este programa corre desde hace 000 segundos"};
uint8_t INDICE = 0;
char RX;

int main()
{
    int CONTAR,LONGITUD,i;
    
    CONTAR = 0;
    INDICE = 0;
   
    PUERTO_SERIAL.printf("\n\rHOLA MUNDO !");
    
    while(1)
    {
    //PUERTO_SERIAL.printf("\n\rEste programa se encuentra ejecutando desde hace  %i  segundos", CONTAR);

    i=0;
    LONGITUD = sprintf(CADENA,"\n\r Este programa se encuentra ejecutando desde hace  %i  segundos",CONTAR);

    wait(1);
       
    CONTAR++;
       
        while(i < LONGITUD)
        {
            
            if(PUERTO_SERIAL.writeable())
            {
                PUERTO_SERIAL.putc(CADENA[i]);
                i++;
            }
            
           // en esta parte va el resto del codigo de la zona critica
            
            if(PUERTO_SERIAL.readable()) // Ha llegado algun dato al buffer de RX
            {
         
                    RX = PUERTO_SERIAL.getc();
                 
                    if ( RX =='A')
                    {
                        TESTIGO = 1;         
                    }    
                 
                    if( RX == 'B')
                    {
                        TESTIGO = 0;         
                    }    
            }       
        }  
    }
}