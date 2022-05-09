#include <io.h>
#include <display.h>
#include <delay.h>
#include <stdio.h>
#include <ff.h>

#asm
  .equ __lcd_port=0x02
  .equ __lcd_EN=1
  .equ __lcd_RS=0
  .equ __lcd_D4=2
  .equ __lcd_D5=3
  .equ __lcd_D6=4
  .equ __lcd_D7=5
#endasm
  
//Código base que reproduce A001.WAV que es un WAV, Mono, 8-bit, y frec de muestreo de 22050HZ
//Trep = 1/22050 = 45.35useg
//Proyecto a 8MHz
//Timer 0: Fast PWM se usa para DAC (Digital to Analog Converter)
//Timer 1: Interrupción periódica para la SD cada 10mseg
//Timer 2: Modo CTC. Interrupción periódica cada periodo de reproducción (Trep = 45.35useg)
char bufferL[256];
char bufferH[256];
char NombreArchivo[] = "0:A004.wav";
unsigned int i=0;
bit LeerBufferH,LeerBufferL;
unsigned long muestras;
int p, j = 0;
char nombre[16], artista[16];

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
  disk_timerproc();
  /* MMC/SD/SD HC card access low level timing function */
}

//Interrupción que se ejecuta cada T=1/Fmuestreo_Wav
interrupt [TIM2_COMPA] void timer2_compa_isr(void)
{
  if (i<256)
  OCR0A=bufferL[i++];
  else
  {
    OCR0A=bufferH[i-256];
    i++;
  }
  if (i==256)
    LeerBufferL=1;
  if (i==512)
  {
    LeerBufferH=1;
    i=0;
  }
}

void main()
{
  unsigned int br;
  /* FAT function result */
  FRESULT res;
  /* will hold the information for logical drive 0: */
  FATFS drive;
  FIL archivo; // file objects
  CLKPR=0x80;
  CLKPR=0x01; //Cambiar a 8MHz la frecuencia de operación del micro
  // Código para hacer una interrupción periódica cada 10ms
  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Clock value: 1000.000 kHz
  // Mode: CTC top=OCR1A
  // Compare A Match Interrupt: On
  TCCR1B=0x0A; //CK/8 10ms con oscilador de 8MHz
  OCR1AH=0x27;
  OCR1AL=0x10;
  TIMSK1=0x02;
  //PWM para conversión Digital Analógica WAV->Sonido
  // Timer/Counter 0 initialization
  // Clock source: System Clock
  // Clock value: 8000.000 kHz
  // Mode: Fast PWM top=0xFF
  // OC0A output: Non-Inverted PWM
  TCCR0A=0x83;
  DDRB.7=1; //Salida bocina (OC0A)
  Diseño de sistemas en chip 09 de junio de 2021
  // Timer/Counter 2 initialization
  // Clock source: System Clock
  // Clock value: 1000.000 kHz
  // Mode: CTC top=OCR2A
  ASSR=0x00;
  TCCR2A=0x02;
  TCCR2B=0x02;
  OCR2A=0x2C; //Este valor cambia por cada recuencia de muestreo diferente que se tenga (2C = 44
  = 45 cuentas (45useg)
  // Timer/Counter 2 Interrupt(s) initialization
  TIMSK2=0x02;
  #asm("sei")
  disk_initialize(0); /* Inicia el puerto SPI para la SD */
  delay_ms(500);
  SetupLCD();
  /* mount logical drive 0: */
  if ((res=f_mount(0,&drive))==FR_OK)
  {
    while(1)
    {
      /*Lectura de Archivo*/
      res = f_open(&archivo, NombreArchivo, FA_OPEN_EXISTING | FA_READ);
      if (res==FR_OK)
      {
        f_read(&archivo, bufferL, 44,&br); //leer encabezado
        //Obtener la frecuencia de muestreo para calcular el valor OCR2A
        //Se puede comparar BufferL[24] y/o BufferL[25]
        muestras = (long)bufferL[43]*16777216 + (long)bufferL[42]*65536 + (long)bufferL[41]*256 +
        bufferL[40];
        f_lseek(&archivo, muestras + 44);
        f_read(&archivo, bufferH, 100, &br);
        //bufferH está la info de la canción
        //Imprimir el nombre de la canción en el LCD
        j = 0;
        for(p = 20; bufferH[p] != 0x00; p++)
        {
          nombre[j] = bufferH[p];
          j++;
        }
        MoveCursor(0,0);
        StringLCDVar(nombre);
        for(p; bufferH[p] != 0x54; p++)
        {
          
        }
        p = p + 5;
        j = 0;
        for(p; bufferH[p] != 0x00; p++)
        {
          artista[j] = bufferH[p];
          j++;
        }
        MoveCursor(0,1);
        StringLCDVar(artista);
        //Imprimir el nombre del artista en el LCD
        f_lseek(&archivo, 44);
        f_read(&archivo, bufferL, 256,&br); //leer los primeros 512 bytes del WAV
        f_read(&archivo, bufferH, 256,&br);
        LeerBufferL=0;
        LeerBufferH=0;
        TCCR0B=0x01; //Prende sonido
        do
        {
          while((LeerBufferH==0)&&(LeerBufferL==0));
          if (LeerBufferL)
          {
            f_read(&archivo, bufferL, 256,&br); //leer encabezado
            LeerBufferL=0;
          }
          else
          {
            f_read(&archivo, bufferH, 256,&br); //leer encabezado
            LeerBufferH=0;
          }
        //Código para estatus switches
        }while(br==256);
        TCCR0B=0x00; //Apaga sonido
        f_close(&archivo);
      }
    }
  }
  f_mount(0, 0); //Cerrar drive de SD
  while(1);
}
