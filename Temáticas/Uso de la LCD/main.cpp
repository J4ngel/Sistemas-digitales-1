#include "mbed.h"
        
                //LSB                             MSB
BusOut DATOS(PA_3, PA_4, PA_5, PA_6, PA_7, PB_0, PB_1, PB_10);
DigitalOut ENABLES (PA_2); // Pin de Enable para generar el pulso para realizar la accion
DigitalOut RS (PA_1);
//DigitalOut RW (D12);// No se necesita en hardware puede ir a tierra

                                 //0123456789  
char CADENA[50]={"HOLA MUNDO"};

                                       //0123456789ABCDEF  
char CADENA2[50]={"TEXTO 2"};

void R_I (uint8_t COMANDO);
void R_D (uint8_t CARACTER);
void MENSAJE(void);
void MENSAJE2(void);
void INICIALIZAR(void);

//---------------------------------------------------------------------------------------------


int main()
{
 
    INICIALIZAR();
    MENSAJE();
wait_ms(5000); // Este retardo es de 5 segundos y permite visualizar en esa cantidad de 
 // tiempo el mensaje anterior

R_I(1); // Rutina Instruccion → Borra la pantalla y ubica el cursor en Home, es
// decir en el primer caracter del primer renglon

    MENSAJE2();

    while(1)
    {

 // Recuerde que la LCD internamente tiene un procesador junto a una memoria y no
 // requiere que la info sea actualizada, por eso la rutina principal está vacía
         R_I(0b00011000);
         wait(500);
     }
}


//------------------------------------------------------------
void R_I (uint8_t COMANDO)
{
    RS      = 0;
    //RW    = 0;
    ENABLES  = 0;
    DATOS   = COMANDO;
    
    ENABLES  = 1;
    wait_us(1);
    ENABLES  = 0;
    
    wait_ms(2); // Este tiempo es para esperar a que el procesador interno de la LCD ejecute la accion
}
//------------------------------------------------------------
void R_D (uint8_t CARACTER)
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
void MENSAJE(void)
{
    R_I(128);// Primer renglón primer caracter
    R_D('H');
    R_D('o');
    R_D('L');
    R_D('a');
    R_D(' ');
    R_D('E');
    R_D('c');
    R_D('C');
    R_D('i');

    R_I(192);// Segundo renglon primer caracter

    R_D('T');
    R_D('e');
    R_D('X');
    R_D('t');
    R_D('O');
    R_D(' ');
    R_D('D');
    R_D('e');
    R_D(' ');
    R_D('P');
    R_D('r');
    R_D('U');
    R_D('e');
    R_D('B');
    R_D('a');


}
//------------------------------------------------------------
void MENSAJE2(void)
{
    uint8_t INDICE;
uint8_t LONGITUD = 0;    
        uint8_t AA = 5;
    
    R_I(128);// Rutina Instrucción ( es la posición del primer renglón primer caracter)


    LONGITUD = sprintf(CADENA,"Pambele %i",AA); 
         // Esta función escribe en el arreglo de caracteres : PAMBELE 5 y retorna la cantidad de caracteres (LONGITUD)
 
    for(INDICE = 0;INDICE<LONGITUD;INDICE++)
    {
        //R_I(POSICION[INDICE]); // Esta en comentario porque es la explicación para realizar una animacion
R_D(CADENA[INDICE]);
        wait_ms(50);
    }
    
    R_I(192);// Rutina Instrucción ( es la posición del segundo renglón primer caracter)

    LONGITUD = sprintf(CADENA2,"Cumbiana");
    for(INDICE = 0;INDICE<LONGITUD;INDICE++)
    {
            R_D(CADENA2[INDICE]);
            wait_ms(50);
    }
}

//------------------------------------------------------------
void INICIALIZAR(void)
{
    wait_ms(50);  // Este tiempo se debe esperar para que la fuente se estabilice 
    R_I(0b00110000);
    
    wait_ms(25);
    R_I(0b00110000);
    
    wait_ms(1);
    R_I(0b00110000);
    
    R_I(0b00111000);  // Activa la segunda linea y establece la interfaz en 8 bits
    R_I(0b00001111);  // R_I(0b00001100); → sin cursor ni sin parpadeo
    R_I(0b00000001);    
}