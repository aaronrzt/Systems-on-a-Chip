# Reloj Digital
Para la implementación física del circuito utilizamos un microcontrolador AtMega328P con un reloj de 16 MHz. Estas dos características las tiene ya embebidas el Arduino nano, por lo que fue nuestra elección. A nuestros puertos de entrada añadimos 5 botones con sus respectivas resistencias de pull-up, estos botones nos permiten mover las horas, minutos, segundos y resetear nuestro reloj. También, tenemos un display de cuarzo líquido de 16x2 en la salida del micro para enseñar la hora. El display tiene un potenciómetro para calibrar el brillo de fondo. En el programa básicamente empleamos las variables de segundos, minutos y horas para incrementar conforme al tiempo. Para medir el tiempo conforme al reloj embebido en el Arduino nano, empleamos contador por CTC para que no nos afecte el tiempo de ejecución del programa en el conteo del tiempo. Teniendo en cuenta que el oscilador que usamos no es exacto, pusimos a funcionar el micro por un par de horas y vimos el error que tiene. En el programa se ajustó las cuentas de CTC para que sea exacto.

[Demo](https://drive.google.com/file/d/1Iimfxjbr-VUG93yNUK0Sy-rBvHo3wn3d/view?usp=sharing)

## Archivos
* clock.jpeg: Diagrama eléctrico del circuito.
* clock.c: Listado del programa en C.

# Digital Clock
For the physical implementation of the circuit we use an AtMega328P microcontroller with a 16 MHz clock. These two characteristics are already embedded in the Arduino nano, so it was our choice. To our input ports we add 5 buttons with their respective pull-up resistors, these buttons allow us to move the hours, minutes, seconds and reset our clock. Also, we have a 16x2 liquid quartz display at the exit of the micro to show the time. The display has a potentiometer to calibrate the background brightness. In the program we basically use the seconds, minutes and hours variables to increment with time. To measure the time according to the clock embedded in the Arduino nano, we use a CTC counter so that the execution time of the program does not affect the time count. Taking into account that the oscillator we use is not exact, we put the micro to work for a couple of hours and we saw the error that it has. In the program, the CTC accounts were adjusted to be accurate.

## Files
* clock.jpeg: Electrical Circuit Diagram.
* clock.c: Program listing in C.


