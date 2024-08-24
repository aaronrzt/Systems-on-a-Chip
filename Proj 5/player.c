#include <mega328p.h>
#include <delay.h>

flash int du=262,re= 294, ri=312, mi =330,fa=349, fi=370, sol=391,si=416, la=440, li=467, ti=494;
flash int MarioBros[591]={mi*2,mi*2,1,mi*2,1,du*2,mi*2,1,sol*2,1,1,1,sol,1,1,1,du*2,1,1,sol,1,1,mi,1,1,la,1,ti,1,li,la,1,sol,mi*2,1,sol*2,la*2,1,fa*2,sol*2,
1,mi*2,1,du*2,re*2,ti,1,1,du*2,1,1,sol,1,1,mi,1,1,la,1,ti,1,li,la,1,sol,mi*2,1,sol*2,la*2,1,fa*2,sol*2,1,mi*2,1,du*2,re*2,ti,1,1,1,1,sol*2,fi*2,fa*2,ri*2,1,
mi*2,1,si,la,du*2,1,la,du*2,re*2,1,1,sol*2,fi*2,fa*2,ri*2,1,mi*2,1,du*4,1,du*4,du*4,1,1,1,1,1,sol*2,fi*2,fa*2,ri*2,1,mi*2,1,si,la,du*2,1,la,du*2,re*2,1,1,
ri*2,1,1,re*2,1,1,du*2,1,1,1,1,1,1,1,1,1,sol*2,fi*2,fa*2,ri*2,1,mi*2,1,si,la,du*2,1,la,du*2,re*2,1,1,sol*2,fi*2,fa*2,ri*2,1,mi*2,1,du*4,1,du*4,du*4,1,1,1,
1,1,sol*2,fi*2,fa*2,ri*2,1,mi*2,1,si,la,du*2,1,la,du*2,re*2,1,1,ri*2,1,1,re*2,1,1,du*2,1,1,1,1,1,1,1,du*2,du*2,1,du*2,1,du*2,re*2,1,mi*2,du*2,1,la,sol,1,1,1,
du*2,du*2,1,du*2,1,du*2,re*2,1,1,1,1,1,1,1,1,du*2,du*2,1,du*2,1,du*2,re*2,1,mi*2,du*2,1,la,sol,1,1,1,mi*2,mi*2,1,mi*2,1,du*2,mi*2,1,sol*2,1,1,1,sol,1,1,1,du*2,
1,1,sol,1,1,mi,1,1,la,1,ti,1,li,la,1,sol,mi*2,1,sol*2,la*2,1,fa*2,sol*2,1,mi*2,1,du*2,re*2,ti,1,1,du*2,1,1,sol,1,1,mi,1,1,la,1,ti,1,li,la,1,sol,mi*2,1,sol*2,
la*2,1,fa*2,sol*2,1,mi*2,1,du*2,re*2,ti,1,1,mi*2,du*2,1,sol,1,1,si,1,la,fa*2,1,fa*2,la,1,1,1,ti,la*2,1,la*2,la*2,sol*2,1,fa*2,mi*2,du*2,1,la,sol,1,1,1,mi*2,du*2,
1,sol,1,1,si,1,la,fa*2,1,fa*2,la,1,1,1,ti,fa*2,1,fa*2,fa*2,mi*2,1,re*2,sol,mi,1,mi,du,1,1,1,mi*2,du*2,1,sol,1,1,si,1,la,fa*2,1,fa*2,la,1,1,1,ti,la*2,1,la*2,la*2,
sol*2,1,fa*2,mi*2,du*2,1,la,sol,1,1,1,mi*2,du*2,1,sol,1,1,si,1,la,fa*2,1,fa*2,la,1,1,1,ti,fa*2,1,fa*2,fa*2,mi*2,1,re*2,sol,mi,1,mi,du,1,1,1,du*2,du*2,1,du*2,1,
du*2,re*2,1,mi*2,du*2,1,la,sol,1,1,1,du*2,du*2,1,du*2,1,du*2,re*2,1,1,1,1,1,1,1,1,du*2,du*2,1,du*2,1,du*2,re*2,1,mi*2,du*2,1,la,sol,1,1,1,mi*2,mi*2,1,mi*2,1,du*2,
mi*2,1,sol*2,1,1,1,sol,1,1,1,mi*2,du*2,1,sol,1,1,si,1,la,fa*2,1,fa*2,la,1,1,1,ti,la*2,1,la*2,la*2,sol*2,1,fa*2,mi*2,du*2,1,la,sol,1,1,1,mi*2,du*2,1,sol,1,1,si,1,la,
fa*2,1,fa*2,la,1,1,1,ti,fa*2,1,fa*2,fa*2,mi*2,1,re*2,sol,mi,1,mi,du,1,1,1,0}; 

flash int as4=466, c5=523, d5=587, e5=659, f5=698, g5=784, gs5=831, a5=880,as5=932,c6=1047, cs6=1109, ds6=1245, f6=1397, rest=0;
flash int starwars[176] = {as4, 8, as4, 8, as4, 8, f5, 2, c6, 2, as5, 8, a5, 8, g5, 8, f6, 2, c6, 4, as5, 8, a5, 8, g5, 8, f6, 2, c6, 4, as5, 8, a5, 8, as5, 8, g5, 2, c5, 8, 
c5, 8, c5, 8, f5, 2, c6, 2, as5, 8, a5, 8, g5, 8, f6, 2, c6, 4, as5, 8, a5, 8, g5, 8, f6, 2, c6, 4, as5, 8, a5, 8, as5, 8, g5, 2, c5, -8, c5, 16, d5, -4, d5, 8, as5, 8, 
a5, 8, g5, 8, f5, 8, c6, -8, g5, 16, g5, 2, rest, 8, c5, 8, d5, -4, d5, 8, as5, 8, a5, 8, g5, 8, f5, 8, f5, 8, g5, 8, a5, 8, g5, 4, d5, 8, e5, 4, c6, -8, c6, 16, f6, 4, 
ds6, 8, cs6, 4, c6, 8, as5, 4, gs5, 8, g5, 4, f5, 8, c6, 1};


void tono (float frec)
{
    float Cuentas;
    unsigned int CuentasEnt;
    DDRB.1=1,
    TCCR1A=0x40;
    Cuentas= 500000.0/frec;
    CuentasEnt=Cuentas+0.5;
    OCR1AH =(CuentasEnt-1)/256;
    OCR1AL=(CuentasEnt-1)%256;
    TCCR1B=0x09; //CK
}

void noTono(){
    TCCR1A=0;
    TCCR1B=0;
    PORTB.1=0; // APAGAR EL TIMER
}

unsigned int i;

void main(void)
{
CLKPR=0x80;
CLKPR=0x04; 
PORTC=0x03;

while (1)
    {  
    if (PINC.0 == 0 && PINC.1 == 1)
        {  
        for(i=0;i<591;i++)
        {    
            if (PINC.0 == 1 && PINC.1 == 0){break;}
            if(MarioBros[i]!=1)
            {
                tono(MarioBros[i]);
                delay_ms(100);
                noTono();
            }
            else
            delay_ms(100);
        }   
    }
    else if (PINC.1 == 0 && PINC.0 == 1)
    {
        for(i=0;i<176;i++)
        {           
            if (PINC.1 == 1 && PINC.0 == 0){break;}
            if(starwars[i]!=1)
            {
                tono(starwars[i]);
                delay_ms(100);
                noTono();
            }
            else
                delay_ms(100);
            }      
        }
    }
}