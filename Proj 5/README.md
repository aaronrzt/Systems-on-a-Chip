# Reproductor Música
Nuestro circuito cuenta con dos push buttons destinados a la selección de la canción a reproducir, estos van conectados a los puertos de entrada, en este caso PC0 y PC1, siendo PC0 la canción de Mario Bros y PC1 la de Star Wars. Nuestra salida se encuentra en el pin PB1 con una resistencia al buzzer, esto permite que, al presionar un botón, la canción se pare y comience la otra. Se incluyen las librerías necesarias, en este caso mega328p y delay, para después declarar los tonos necesarios para la canción de Mario Bros y la de Star Wars. Cabe mencionar que los tonos para las canciones están almacenados en la memoria ROM. Con estos tonos se crea el arreglo de la secuencia de tonos para ambas canciones. Declaramos condicionales if conectados a nuestros botones de entrada para seleccionar la canción que se quiere reproducir con ayuda del timer 1. Por último, nos gustaría mencionar que las melodías se podrían escuchar mucho mejor si tuviéramos una bocina dedicada y no buzzer.

[Demo](https://youtu.be/hIc4RdrYW6Q?fbclid=IwAR140yh-L9UHWN_HgjH0fe0pA7YLWTK0xb4_IsYltp7f2KV6k0MfWeUAnW0)

## Archivos
* player.jpeg: Diagrama eléctrico del circuito.
* player.c: Listado del programa en C.

# Music Player
Our circuit has two push buttons for selecting the song to play, these are connected to the input ports, in this case PC0 and PC1, PC0 being the Mario Bros song and PC1 the Star Wars song. Our output is located on pin PB1 with a resistor to the buzzer, this allows that, when one button is pressed, the song stops and the other starts. The necessary libraries are included, in this case mega328p and delay, to later declare the necessary tones for the Mario Bros. song and the Star Wars song. It is worth mentioning that the tones for the songs are stored in the ROM memory. With these tones the tone sequence arrangement for both songs is created. We declare if conditionals attached to our input buttons to select the song to play with the help of timer 1. Finally, we would like to mention that the melodies could be heard much better if we had a dedicated speaker and not a buzzer.

## Files
* player.jpeg: Electrical Circuit Diagram.
* player.c: Program listing in C.


