#include <mega328p.h>
#include <io.h>
#include <stdio.h>

int day, month, year, diasemana;
char sep1, sep2;

void main(void)
{
    UCSR0A = 0x02;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    UBRR0H = 0x00;
    UBRR0L = 0x0C;
    
    while (1)
        {       
            printf("Fecha en formato dd-mm-yyyy ->");
            scanf("%i%c%i%c%i",&day,&sep1,&month,&sep2,&year);
            
            if((sep1 == '-') && (sep2 == '-'))
            {
                if((day >= 1) && (day <= 31) && (month >= 1) && (month <= 12) && (year >= 1))
                {
                    if(month <= 2)
                    {  
                        month = month + 12;
                        year--;
                    } 
                    diasemana = (day + ((month + 1) * 26) / 10 + year + year / 4 + 6 * (year / 100) + year / 400) % 7;
                    printf("El dia de la semana es: ");
                    
                    switch(diasemana)
                    {
                        case 0:
                            printf("SABADO \n\r");
                            break; 
                        case 1:
                            printf("DOMINGO \n\r");
                            break; 
                        case 2:
                            printf("LUNES \n\r");
                            break; 
                        case 3:
                            printf("MARTES \n\r");
                            break;
                        case 4:
                            printf("MIERCOLES \n\r");
                            break;  
                        case 5:
                            printf("JUEVES \n\r");
                            break;
                        case 6:
                            printf("VIERNES \n\r");
                            break; 
                    }
                }
                else
                    printf("Formato No Valido \n\r");

        }
    }
}