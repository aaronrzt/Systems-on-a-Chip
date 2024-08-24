#asm
.equ __lcd_port = 0x0B
.equ __lcd_EN = 3
.equ __lcd_RS = 2
.equ __lcd_D4 = 4
.equ __lcd_D5 = 5
.equ __lcd_D6 = 6
.equ __lcd_D7 = 7
#endasm

#include <delay.h>
#include <display.h>
#include <mega328p.h>

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0 << REFS1) | (1 << REFS0) | (0 << ADLAR))

	// Read the AD conversion result
	unsigned int
	read_adc(unsigned char adc_input)
{
	ADMUX = adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	delay_us(10);
	// Start the AD conversion
	ADCSRA |= (1 << ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1 << ADIF)) == 0)
		;
	ADCSRA |= (1 << ADIF);
	return ADCW;
}

unsigned char pmOpen[] = {0x0E, 0x1D, 0x1E, 0x1C, 0x1E, 0x1F, 0x0E, 0x00};

unsigned char pmClosed[] = {0x0E, 0x1D, 0x1F, 0x1F, 0x1E, 0x1F, 0x0E, 0x00};

unsigned char pmOpenL[] = {0x0E, 0x17, 0x0F, 0x07, 0x0F, 0x1F, 0x0E, 0x00};

unsigned char pmClosedL[] = {0x0E, 0x17, 0x1F, 0x0F, 0x1F, 0x1F, 0x0E, 0x00};

unsigned char closed = 0;
unsigned char open = 1;
unsigned char closedL = 2;
unsigned char openL = 3;
unsigned char line = 0;

signed char i = 0;

void DelayPacMan()
{
	delay_ms(read_adc(0));
}

void main(void)
{

	// ADC initialization
	// ADC Clock frequency: 125.000 kHz
	// ADC Voltage Reference: AVCC pin
	// ADC Auto Trigger Source: ADC Stopped
	// Digital input buffers on ADC0: Off, ADC1: On, ADC2: On, ADC3: On
	// ADC4: On, ADC5: On
	DIDR0 = (0 << ADC5D) | (0 << ADC4D) | (0 << ADC3D) | (0 << ADC2D) | (0 << ADC1D) | (1 << ADC0D);
	ADMUX = ADC_VREF_TYPE;
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRB = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);

	// setup c1 port as switch
	DDRC = 0x02;
	PORTC = 0x02;

	SetupLCD();
	CreateChar(closed, pmClosed);
	CreateChar(open, pmOpen);
	CreateChar(closedL, pmClosedL);
	CreateChar(openL, pmOpenL);

	while (1)
	{

		if (i == 0 && !line)
		{
			MoveCursor(6, 0);
			StringLCD("Hello");
			MoveCursor(4, 1);
			StringLCD("Mr PacMan");
		}

		MoveCursor(i, line);
		CharLCD(PINC.1 ? open : openL);
		DelayPacMan();
		MoveCursor(i, line);
		CharLCD(PINC.1 ? closed : closedL);
		DelayPacMan();
		MoveCursor(i, line);
		CharLCD(' ');

		if (PINC.1)
		{
			i++;
			if (i >= 16)
			{
				i = 0;
				line = !line;
			}
		}
		else
		{
			i--;
			if (i < 0)
			{
				i = 15;
				line = !line;
			}
		}
	}
}