#asm
    .equ __lcd_port=0x0B   //LCD en PuertoD
    .equ __lcd_EN=3
    .equ __lcd_RS=2
    .equ __lcd_D4=4
    .equ __lcd_D5=5
    .equ __lcd_D6=6
    .equ __lcd_D7=7
#endasm                

#include <mega328p.h>
#include <io.h>
#include <delay.h>
#include <display.h>        
#include <stdio.h>


unsigned char i=0;
signed char H=0,M=0,S=0;
char Cadena[5];

void main(void)
{
    CLKPR=0x80;
    CLKPR=0x04;     //Arduino nano trabajara a 16MHz/16=1MHz        
    
    SetupLCD();
    MoveCursor(0, 0);
    StringLCD("Tiempo");
    
    PORTC = 0x1F; //00011111
    
    TCCR1A=0;
    TCCR1B=0x0A;    //Timer 1 en CTC con CK/8
    OCR1AH=31249/256;
    OCR1AL=31249%256;          
    
    while (1)      // El ciclo completo tarda 0.25seg
    {
       //Imprimir hora en el LCD 
       sprintf(Cadena, "%02u:%02u:%02u    ", H, M, S);
       MoveCursor(0,1);
       StringLCDVar(Cadena);
       delay_ms(25);
       
       while(TIFR1.OCF1A==0);   //Espera a 0.25seg
       TIFR1.OCF1A=1;           //Borra Bandera
       i++;   
      
       if (i==4)
       {
            i=0;
            S++;
            if (S==60)
            {
                S=0;
                M++;
                if (M==60)
                {   
                    M=0;
                    H++;
                    if (H==24)
                        H=0;
                }     
                
            }
       }
       //Revisar switches 
       if(!PINC.0)
           H++;
       if(!PINC.1)
           H--;
       if(!PINC.2)
           M++;
       if(!PINC.3)
           M--;
       if(!PINC.4)
           S = 0;
    }
}