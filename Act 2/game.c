#asm
    .equ __lcd_port=0x05
    .equ __lcd_EN=1
    .equ __lcd_RS=0
    .equ __lcd_D4=2
    .equ __lcd_D5=3
    .equ __lcd_D6=4
    .equ __lcd_D7=5
   #endasm

#include <io.h>
#include <delay.h>     
#include <stdio.h>
#include <display.h>   

#define SinTiro 0
#define Piedra 1
#define Papel 2
#define Tijera 3
unsigned char A=0, B=0, tiroA, tiroB;
void ImprimeMarcador(){
    MoveCursor(0,0);
    CharLCD(A+'0');
    MoveCursor(15,0);
    CharLCD(B+'0');
}
         
void ImprimeTiro(){
    MoveCursor(0,1);
    switch  (tiroA){
        case Piedra:
            StringLCD("Piedra  ");
            break;   
        case Papel:
            StringLCD("Papel   ");
            break;
        case Tijera:
            StringLCD("Tijera  ");
            break;

        
    }
     MoveCursor(9,1);
    switch  (tiroB){
        case Piedra:
            StringLCD(" Piedra");
            break;   
        case Papel:
            StringLCD("  Papel");
            break;
        case Tijera:
            StringLCD(" Tijera");
            break;

        
    }
  
}

void main(void)
{
 
       SetupLCD();
    PORTD=0xE1;
    PORTC=0x07 ;
    while(1){
        ImprimeMarcador();
        MoveCursor(4,0);
        StringLCD("A TIRAR");
        tiroA=SinTiro;
        tiroB=SinTiro;
        do{
            if(PIND.5==0)
            tiroA=Piedra;
            if(PIND.6==0)
            tiroA=Papel;
            if(PIND.7==0)
            tiroA=Tijera;
            if(PINC.0==0)
            tiroB=Piedra;
            if(PINC.1==0)
            tiroB=Papel;
            if(PINC.2==0)
            tiroB=Tijera;
            MoveCursor(0,1);
            if (tiroA==SinTiro) 
            StringLCD("Falta  ")  ;
            else
            StringLCD("OK     ") ; 
            MoveCursor(9,1);
            if (tiroB==SinTiro)
            StringLCD("  Falta");
            else
            StringLCD("     0K");
            
        }  
        while ((tiroA==SinTiro)||(tiroB==SinTiro));
        
            ImprimeTiro() ;
        MoveCursor(4,0);
        switch (tiroA-tiroB)
            {
            case 0:
                    StringLCD("EMPATE");
            break;

            
            case 1:
            case -2:
                    StringLCD("GANA A ");
                    A++;
            
            break;
            
            case -1:
            case 2:
                    StringLCD("GANA B "); 
                    B++;
            
            break;      
            }
            
        
                ImprimeMarcador();
                delay_ms(1500);       
        if ((A==5)||(B==5)){
        do
        {
            MoveCursor(3,0);
            if (A==5)
            StringLCD("Ganodor: A") ;
            else
            StringLCD("Ganodor: B");
            
            delay_ms(100); 
            MoveCursor(3,0);
            StringLCD("          ") ;
            delay_ms(100); 
        }
        while (PIND.0==1);
        A=0;
        B=0;
        }

    }        
}