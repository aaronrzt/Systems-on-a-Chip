#include <io.h>
#include <delay.h> 
#include "sonido1.C" 
#include "sonido2.C" 
#include "sonido3.C"    

unsigned int i;

void main(void)
{
    DDRB.7 = 1;
    PORTC = 0x07;   //Pull ups en PC0, PC1, PC2 
    TCCR0A=0x83;    //Fast PWM
    TCCR0B=0x01;    //Sin pre-escalador
    while (1)
    { 
        if (PINC.0==0)
        {   
          for (i=0;i<LimSon1;i++)
           {
              OCR0A=Sonido1[i];
              delay_us(125); 
           }   
        }
        
        if (PINC.1==0)
        {   
          for (i=0;i<LimSon2;i++)
           {
              OCR0A=Sonido2[i];
              delay_us(125); 
           }   
        } 
        
        if (PINC.2==0)
        {   
          for (i=0;i<LimSon3;i++)
           {
              OCR0A=Sonido3[i];
              delay_us(125); 
           }   
        }
    }
}