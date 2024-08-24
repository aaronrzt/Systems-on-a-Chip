#asm
  .equ __lcd_port = 0x02
  .equ __lcd_EN = 1
  .equ __lcd_RS = 0
  .equ __lcd_D4 = 2
  .equ __lcd_D5 = 3
  .equ __lcd_D6 = 4
  .equ __lcd_D7 = 5
#endasm

#asm
  .equ __keypad_port = 0x08
  .equ __keypad_R1 = 3
  .equ __keypad_R2 = 2
  .equ __keypad_R3 = 1
  .equ __keypad_R4 = 0
  .equ __keypad_C1 = 4
  .equ __keypad_C2 = 5
  .equ __keypad_C3 = 6
#endasm

#include <io.h>

#include <display.h>

#include <delay.h>

void SetupKeypad() {
  #asm
  SBI __keypad_port - 1, __keypad_R1 //Renglón 1 de salida   //SBI DDRC,3   //DDRC.3 = 1;
  SBI __keypad_port - 1, __keypad_R2 //salida
  SBI __keypad_port - 1, __keypad_R3 //salida
  SBI __keypad_port - 1, __keypad_R4 //salida
  SBI __keypad_port - 1, __keypad_R1 //salida
  SBI __keypad_port, __keypad_C1 //Pull-up
  SBI __keypad_port, __keypad_C2 //Pull-up
  SBI __keypad_port, __keypad_C3 //Pull-up
  #endasm

}

#pragma warn -
  char LeeTeclado() {
    #asm
    Inicio:
      SBIS __keypad_port - 2, __keypad_C1
    RJMP BarridoC1
    SBIS __keypad_port - 2, __keypad_C2
    RJMP BarridoC2
    SBIS __keypad_port - 2, __keypad_C3
    RJMP BarridoC3
    CLR R30
    RJMP Fin
    BarridoC1:
      LDI R30, '1'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    SBI __keypad_port, __keypad_R4;
    R4 = 1
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C1
    RJMP Fin
    LDI R30, '4'
    SBI __keypad_port, __keypad_R1;
    R1 = 1
    CBI __keypad_port, __keypad_R2;
    R2 = 1
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C1
    RJMP Fin
    LDI R30, '7'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    CBI __keypad_port, __keypad_R3;
    R3 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C1
    RJMP Fin
    LDI R30, '*'
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    CBI __keypad_port, __keypad_R4;
    R4 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C1
    RJMP Fin
    CLR R30
    RJMP Fin
    BarridoC2:
      LDI R30, '2'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    SBI __keypad_port, __keypad_R4;
    R4 = 1
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C2
    RJMP Fin
    LDI R30, '5'
    SBI __keypad_port, __keypad_R1;
    R1 = 1
    CBI __keypad_port, __keypad_R2;
    R2 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C2
    RJMP Fin
    LDI R30, '8'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    CBI __keypad_port, __keypad_R3;
    R3 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C2
    RJMP Fin
    LDI R30, '0'
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    CBI __keypad_port, __keypad_R4;
    R4 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C2
    RJMP Fin
    CLR R30
    RJMP Fin
    BarridoC3:
      LDI R30, '3'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    SBI __keypad_port, __keypad_R4;
    R4 = 1
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C3
    RJMP Fin
    LDI R30, '6'
    SBI __keypad_port, __keypad_R1;
    R1 = 1
    CBI __keypad_port, __keypad_R2;
    R2 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C3
    RJMP Fin
    LDI R30, '9'
    SBI __keypad_port, __keypad_R2;
    R2 = 1
    CBI __keypad_port, __keypad_R3;
    R3 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C3
    RJMP Fin
    LDI R30, '#'
    SBI __keypad_port, __keypad_R3;
    R3 = 1
    CBI __keypad_port, __keypad_R4;
    R4 = 0
    RCALL Delay1us
    SBIS __keypad_port - 2, __keypad_C3
    RJMP Fin
    CLR R30
    RJMP Fin
    Delay1us: ;
    Micro a 16 MHz, necesitamos 16 ciclos
    ;
    RCALL tarda 3 ciclos
    ;
    RET tarda 4 ciclos
    ; + 9 NOPS = 16 ciclos
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    RET
    Fin:
      CBI __keypad_port, __keypad_R1
    CBI __keypad_port, __keypad_R2
    CBI __keypad_port, __keypad_R3
    CBI __keypad_port, __keypad_R4
    #endasm
  }
#pragma warn +

  void tono(float frec) {
    float Cuentas;
    unsigned int CuentasEnt;
    DDRB .5 = 1; //PB5 de salida(Bocina)
    Cuentas = 500000.0 / frec; //Ejemplo 1 frec=293.6 Cuentas=1702.997 Ejemplo2 frec=261.6 Cuentas=1911.31
    CuentasEnt = Cuentas;
    if ((Cuentas - CuentasEnt) >= 0.5)
      CuentasEnt++;
    TCCR1A = 0x40; //Modo CTC
    TCCR1B = 0x09; // SIn Pre-escalador (CK)
    OCR1AH = (CuentasEnt - 1) / 256;
    OCR1AL = (CuentasEnt - 1) % 256;
  }

void noTono() {
  TCCR1A = 0;
  TCCR1B = 0; //Apaga timer (Stop)
}

char c;
int i = 0;
bit ren = 0;
int j = 0;
void main(void) {

  SetupLCD();
  UnderscoreCursor();
  SetupKeypad();

  while (1) {
    do //Manda char mientras esté presionado
    {
      c = LeeTeclado();
    } while (c == 0);

    if (c == '*') {
      tono(600.0); //Bocina 600Hz
      delay_ms(50);
      noTono();
      MoveCursor(0, 0);
      for (j = 0; j < 32; j++) {
        if (j == 16)
          MoveCursor(0, 1);
        CharLCD(' ');
      }
      i = 0;
      ren = 0;
      MoveCursor(0, 0);
      do //Espera a que suelte el botón
      {
        c = LeeTeclado();
      } while (c != 0);
    } else if (c == '#') {
      tono(200.0); //Bocina 200Hz
      delay_ms(50);
      noTono();
      ren = ~ren;
      MoveCursor(0, ren);
      for (j = 0; j < 16; j++) {
        CharLCD(' ');
      }
      i = 0;
      MoveCursor(0, ren);
      do //Espera a que suelte el botón
      {
        c = LeeTeclado();
      } while (c != 0);
    } else {
      CharLCD(c);
      i++;
      if (i == 16) {
        i = 0;
        ren = ~ren;
        MoveCursor(i, ren);
      }

      do //Espera a que suelte el botón
      {
        c = LeeTeclado();
        tono(400.0); //Bocina 400Hz

      } while (c != 0);
      noTono();
    }
  }
}
