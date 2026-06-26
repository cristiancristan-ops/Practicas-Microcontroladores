# Proyecto Final - Juego tipo Dinosaurio con dos PIC16F887

## Descripción

Este proyecto consiste en un juego parecido al dinosaurio de Google cuando no hay internet.

Se utilizaron dos microcontroladores PIC16F887. El primer PIC se encarga de leer el joystick y mandar las instrucciones al segundo PIC mediante comunicación serial.

El segundo PIC controla la pantalla LCD, el personaje, los obstáculos, el LED rojo y el buzzer.

El objetivo del juego es saltar los obstáculos y evitar chocar con ellos.

## Funcionamiento

Al encender el circuito, en la pantalla aparece el mensaje:

```text
PRESIONA BOTON
PARA INICIAR
```

Al presionar el botón del joystick comienza el juego.

El personaje se encuentra en la parte inferior de la pantalla y los obstáculos aparecen desde el lado derecho y se mueven hacia la izquierda.

Cuando el joystick se mueve hacia arriba, el personaje salta y después baja automáticamente.

Cada vez que se logra esquivar un obstáculo, aumenta la puntuación y poco a poco el juego se vuelve más rápido.

Si el personaje choca con un obstáculo:

- Se enciende el LED rojo.
- Suena el buzzer.
- Aparece el mensaje `GAME OVER`.
- Se muestra la puntuación obtenida.
- Es necesario presionar nuevamente el botón para reiniciar.

## Materiales utilizados

- 2 PIC16F887
- Pantalla LCD 16x2
- Joystick
- LED rojo
- Resistencia de 220 Ω o 330 Ω
- Buzzer
- Potenciómetro de 10 kΩ para el contraste de la LCD
- Cristal de 8 MHz
- Resistencia de 10 kΩ para MCLR
- Cables
- Protoboard
- Fuente de 5 V

En este proyecto uno de los PIC utiliza un cristal externo de 8 MHz y el otro utiliza el oscilador interno de 8 MHz.

## Comunicación entre los PIC

La comunicación se realiza mediante UART.

El PIC 1 manda los siguientes caracteres:

```text
U = Joystick hacia arriba
D = Joystick hacia abajo
S = Joystick en el centro
B = Botón presionado
```

Para el juego se utilizan principalmente `U` para saltar y `B` para iniciar o reiniciar.

## Osciladores

### PIC 1

Utiliza un cristal externo de 8 MHz conectado entre los pines 13 y 14.

### PIC 2

Utiliza el oscilador interno de 8 MHz, por lo que los pines 13 y 14 se dejan sin conectar.

## Archivos del proyecto

El proyecto incluye:

```text
PIC1
Main.c

PIC2
Main.c
lcd.c
lcd.h
```

El archivo del PIC 1 contiene la lectura del joystick y el envío de datos.

El archivo del PIC 2 contiene la lógica del juego, el manejo de la LCD, los obstáculos, el personaje, la puntuación, el LED y el buzzer.

## Programas utilizados

- MPLAB X IDE
- Compilador XC8
- Proteus
- PICkit 3

## Integrantes

- Cristian
- Edgar
