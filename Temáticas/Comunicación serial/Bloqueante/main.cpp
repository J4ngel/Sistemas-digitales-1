//--------------------------------------------------------------------------------------------
// Bloque para verififcar la conexión 

#include "mbed.h"   
//#include "stdio.h" 

                                            //(TX - RX);
Serial PUERTO_SERIAL(USBTX,USBRX) ;  //(PA_2,PA_3);


DigitalOut TESTIGO(LED1);

int main()
{
    int CONTAR, LONGITUD;
    char CADENA[100];
    
    CONTAR = 0;
    TESTIGO = 0;   
   
    PUERTO_SERIAL.printf("\n\rHOLA MUNDO !");
    
    while(1)
    {
    PUERTO_SERIAL.printf("\n\rEste programa se encuentra ejecutando desde hace  %i  segundos", CONTAR);
    //LONGITUD = sprintf(CADENA,"\n\r Este programa se encuentra ejecutando desde hace  %i  segundos",CONTAR);
    //PUERTO_SERIAL.printf("%s %i",CADENA,LONGITUD);

    
    wait_ms(1000);
       
    CONTAR++;
    TESTIGO = !TESTIGO;
    }
}