/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////    Autor: Ricardo Carlos Arca                                   ////
////    Version: 5.0                                                 ////
////    Fecha: 14/05/2015                                            ////
////    Descripción: PLACA DE CONTROL                                ////
////                                                                 ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////


#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //External Osc
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection

#use delay(clock=4000000)

int i=0;

int1 encendido=0, delay=0;


//#use FIXED_IO( A_outputs=PIN_A3,PIN_A2,PIN_A1,PIN_A0 )
//#use FIXED_IO( B_outputs=PIN_B1,PIN_B0 )


#define CONTACTOR  PIN_A0
#define NEON  PIN_A1
#define LED_APAGADO  PIN_A2
#define LED_ENCENDIDO  PIN_A3

#define SENNAL_APAGADO  PIN_B0
#define SENNAL_ENCENDIDO  PIN_B1
#define STOP  PIN_B2   // ENTRADA
#define START PIN_B3   // ENTRADA
#define ERROR  PIN_B4   // ENTRADA
#define MODO  PIN_B6   // ENTRADA

// #use fast_io(B)  //  PROBAR ESTOOO


//  FUNCION PRINCIPAL

void main(void)
{   
  
   set_tris_a(0b11110000);    //  PROBAR SACAR ESTOO
   set_tris_b(0b11111111);
   
   // PORT_B_PULLUPS(0b00000000);    //  PROBAR SACAR ESTOO
   
   output_a(0b00000000);
   output_b(0b00000000);
     
   OUTPUT_HIGH(LED_APAGADO);
   
   if(!INPUT(MODO))
      delay=1;   
   
   while(!delay){  // MODO DEPURACION
   
      OUTPUT_HIGH(CONTACTOR);
      
      if(INPUT(START)&&(!encendido))
      {
         encendido=1;
         OUTPUT_HIGH(SENNAL_ENCENDIDO);
         OUTPUT_LOW(LED_APAGADO);
         OUTPUT_HIGH(LED_ENCENDIDO);
         delay_ms(200);         
         OUTPUT_LOW(SENNAL_ENCENDIDO);
         OUTPUT_HIGH(NEON);
      }      
      
      if(INPUT(STOP)&&(encendido))
      {
         encendido=0;
         OUTPUT_HIGH(SENNAL_APAGADO);
         OUTPUT_LOW(LED_ENCENDIDO);
         OUTPUT_HIGH(LED_APAGADO);
         delay_ms(200);         
         OUTPUT_LOW(SENNAL_APAGADO);
         OUTPUT_LOW(NEON);
      }
      
      
      if(INPUT(ERROR)&&(encendido))   // LIMPIA LOS ERRORES
      {
         encendido=0;
         OUTPUT_LOW(LED_ENCENDIDO);
         OUTPUT_HIGH(LED_APAGADO);
         OUTPUT_LOW(NEON);
      }
   
   }   // MODO DEPURACION
   
   while(delay)  //  MODO NORMAL
   {  
      
      if(INPUT(START)&&(!encendido))
      {
         encendido=1;
         delay_ms(50);
         OUTPUT_HIGH(CONTACTOR);
         OUTPUT_LOW(LED_APAGADO);
         
         for (int i = 0; i < 10; i++){
            OUTPUT_HIGH(LED_ENCENDIDO);
            delay_ms(200);
            OUTPUT_LOW(LED_ENCENDIDO);
            delay_ms(200);

         }
         
         OUTPUT_HIGH(LED_ENCENDIDO);
         
         OUTPUT_HIGH(SENNAL_ENCENDIDO);
         delay_ms(200);
         OUTPUT_LOW(SENNAL_ENCENDIDO);
         
         OUTPUT_HIGH(NEON);
         
      }  
      
      
      if(INPUT(STOP)&&(encendido))
      {
         encendido=0;
         delay_ms(50);
         OUTPUT_HIGH(SENNAL_APAGADO);
         OUTPUT_LOW(LED_ENCENDIDO);
         
         delay_ms(200);
         OUTPUT_LOW(SENNAL_APAGADO);
         
         OUTPUT_LOW(NEON);
         
         delay_ms(200);
         OUTPUT_LOW(CONTACTOR);
                 
         for (int i = 0; i < 10; i++){
            OUTPUT_HIGH(LED_APAGADO);
            OUTPUT_HIGH(NEON);
            delay_ms(200);
            OUTPUT_LOW(LED_APAGADO);
            OUTPUT_LOW(NEON);
            delay_ms(200);
            if (i==2){
               OUTPUT_HIGH(SENNAL_ENCENDIDO);
               delay_ms(200);
               OUTPUT_LOW(SENNAL_ENCENDIDO);
            }
            else
               OUTPUT_LOW(SENNAL_ENCENDIDO);

         }
         OUTPUT_HIGH(SENNAL_APAGADO);        
         delay_ms(200);
         OUTPUT_LOW(SENNAL_APAGADO);
         /*OUTPUT_HIGH(SENNAL_ENCENDIDO);
         delay_ms(500);
         OUTPUT_LOW(SENNAL_ENCENDIDO);*/
         delay_ms(20);
         OUTPUT_HIGH(LED_APAGADO);         
         
         OUTPUT_LOW(NEON);

      }
      
      if(INPUT(ERROR)&&(encendido))   // LIMPIA LOS ERRORES
      {
         encendido=0;
         OUTPUT_LOW(LED_ENCENDIDO);
         OUTPUT_HIGH(LED_APAGADO);
         OUTPUT_LOW(NEON);
      }   

   }   // MODO NORMAL 
   
}  // FUNCION PRINCIPAL
