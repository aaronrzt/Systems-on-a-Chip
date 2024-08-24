#include <io.h>               //Demo con Teensy 2.0++   2MHz
#include <delay.h>
#include <stdio.h>
#include <ff.h>
#include <display.h>

#asm
    .equ __lcd_port=0x11
    .equ __lcd_EN=4
    .equ __lcd_RS=5
    .equ __lcd_D4=0
    .equ __lcd_D5=1
    .equ __lcd_D6=2
    .equ __lcd_D7=3
#endasm

char NombreArchivo[]  = "0:hola.txt";
char TextoEscritura[] = "\nA01251916\nA01702712";

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
disk_timerproc();
/* MMC/SD/SD HC card access low level timing function */
}
    

void main()
{
    unsigned int  br;
    char buffer[100];
    
    /* FAT function result */
    FRESULT res;
    
    /* will hold the information for logical drive 0: */
    FATFS drive;
    FIL archivo; // file objects
    
       
    // CÛdigo para hacer una interrupciÛn periÛdica cada 10ms
    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 1000.000 kHz
    // Mode: CTC top=OCR1A
    // Compare A Match Interrupt: On
    TCCR1B=0x09;
    OCR1AH=19999/256;
    OCR1AL=19999%256;   //20000cuentas a 0.5us por cuenta=10mseg
    TIMSK1=0x02;
    SetupLCD();
    #asm("sei")
    /* Inicia el puerto SPI para la SD */
    disk_initialize(0);
    delay_ms(200);
    
    /* mount logical drive 0: */
    if ((res=f_mount(0,&drive))==FR_OK){
        MoveCursor(0,0);
        StringLCD("Drive Detectado");
        delay_ms(1500);
    
        
        /*Lectura de Archivo*/
        res = f_open(&archivo, NombreArchivo, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
        if (res==FR_OK){
            MoveCursor(0,0);
            StringLCD("Archivo Encontrado ");
            delay_ms(1500);
            
            f_read(&archivo, buffer, 10,&br); //leer archivo
            
            MoveCursor(0,0); 
            StringLCD("El Archivo dice:   ");
            delay_ms(1500);
             
            MoveCursor(0,1);
            StringLCDVar(buffer);
            delay_ms(1500);
            
            /*Escribiendo en el mismo Arcvhivo*/
            EraseLCD();
            MoveCursor(0,0); 
            StringLCD("Escribiendo ...");
            
            /*Mover el apuntador al final del archivo*/
           
            f_lseek(&archivo,archivo.fsize);  
            
            buffer[0] = 0x0D;                //Carriage return   
            buffer[1] = 0x0A;                //Line Feed
            f_write(&archivo,buffer,2,&br);
            /*Escribiendo el Texto*/            
            f_write(&archivo,TextoEscritura,sizeof(TextoEscritura),&br);
            f_close(&archivo);           
            delay_ms(500);
            
            EraseLCD();
            MoveCursor(0,1); 
            StringLCD("Listo");  
        }              
        else{ 
            MoveCursor(0,0); 
            StringLCD("Archivo NO Encontrado");
           
        }
    }
    else{ 
         StringLCD("Drive NO Detectado");
         while(1);
    }
    f_mount(0, 0); //Cerrar drive de SD
    while(1);
}