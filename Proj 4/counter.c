#asm
    .equ __lcd_port=0x0B
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
#include <stdlib.h>

unsigned int cont = 0;
char cont_fin[3];

void main(void)
{
    SetupLCD();
    PORTC=0x07;
               
    MoveCursor(1, 0);   
    StringLCD("People Counter");
    

    while (1)
        {          
            sprintf(cont_fin, "%003i", cont);
            MoveCursor(6, 1);
            StringLCDVar(cont_fin);
        
            if (PINC.0 == 0)
            {     
                delay_ms(100); 
                while (PINC.0 == 0);
                delay_ms(100);
                cont = 0;
            }    
            
            else if (PINC.1 == 0) 
            {           
                delay_ms(100);  
                while (PINC.1 == 0);
                delay_ms(100);
                if (cont <= 0)
                {         
                    cont = 0;
                }     
                else
                {
                    cont--;
                }
            }  
            
            else if (PINC.2 == 0)
            {          
                delay_ms(100);  
                while (PINC.2 == 0);
                delay_ms(100);
                if (cont >= 999)
                {
                    cont = 999;
                }    
                else
                {
                    cont++;
                }
            }
        }
}