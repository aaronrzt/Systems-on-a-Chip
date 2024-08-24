/*
 * cronometro.c
 *
 * Created: 13/04/2021 09:16:47 a. m.
 * Author: Aaron
 */

#asm
    .equ __lcd_port=0x02
    .equ __lcd_EN=1
    .equ __lcd_RS=0
    .equ __lcd_D4=2
    .equ __lcd_D5=3
    .equ __lcd_D6=4
    .equ __lcd_D7=5
#endasm

#include <mega2560.h>
#include <delay.h>
#include <display.h>
#include <stdio.h>
#include <stdbool.h> 

unsigned char anim1[8] = {0x0E,0x0E,0x0E,0x04,0x1E,0x05,0x0A,0x12}; //Sliding
unsigned char anim2[8] = {0x0E,0x0E,0x0E,0x04,0x0E,0x15,0x0A,0x0A}; //Still
unsigned char decimas = 0, segundos = 0, minutos = 0; 
char Cadena[8];
unsigned int pos = 0;
void main(void)
{
    PORTA.6 = 1; //PA6 con pull-up
    PORTA.7 = 1; //PA7 con pull-up
    SetupLCD();
    CreateChar(0, anim1);
    CreateChar(1, anim2);
    while (1)
    {
        //Desplegar tiempo en el LCD
        sprintf(Cadena, "%02i:%02i.%i", minutos, segundos, decimas);
        MoveCursor(4,0);
        StringLCDVar(Cadena);
        //Retardo de 1 décima de segundo (0.1seg = 100ms) 
        delay_ms(62);
        delay_us(350);
        if(PINA.6 == 0)
        {
            //Actualizar tiempo
            decimas++;
        }
        
        if(decimas == 10)
        {
            decimas = 0;
            segundos++;
            if (segundos == 60)
            {
                segundos = 0;
                minutos++;
                if(minutos == 60)
                {
                    minutos = 0;
                }
            }
        }
        
        if(PINA.7 == 1)     //Presiona el reset
        {
            decimas = 0;
            segundos = 0;
            minutos = 0;
            MoveCursor(0,1);
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            CharLCD(' ');
            pos = 0;
        }
        //Animación (tarea) No delays!
        if(PINA.6 == 1)
        {
            MoveCursor(pos,1);
            CharLCD(1);
            MoveCursor(pos-1, 1);
            CharLCD(' ');
            MoveCursor(pos-2, 1);
            CharLCD(' ');
        }
        else
        {
         MoveCursor(pos, 1);
        CharLCD(0);
        MoveCursor(pos-1, 1);
        CharLCD(' ');
        MoveCursor(pos-2, 1);
        CharLCD(' ');
        pos++;
        if(pos == 16)
        {
            MoveCursor(14,1);
            CharLCD(' ');
            CharLCD(' '); 
            CharLCD(' ');            
            pos = 0;
        }
        }
    }
}
