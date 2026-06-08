# Práctica 02 - Matriz LED 8x8

## Descripción general

En esta práctica se trabajó con una **matriz LED 8x8** utilizando el microcontrolador **PIC16F887**.

La práctica consistió en controlar la matriz mediante el barrido de filas y columnas para formar figuras y letras. Se realizaron dos actividades principales:

1. Dibujar una X en la matriz LED.
2. Mostrar las primeras dos letras de los nombres de los integrantes del equipo: Cristian y Edgar.

---

## Integrantes

- Cristian
- Edgar

---

## Microcontrolador utilizado

- PIC16F887

---

## Software utilizado

- MPLAB X IDE
- XC8 Compiler
- Proteus
- PICkit 3 Programmer

---

## Material utilizado

- PIC16F887
- Matriz LED 8x8
- Resistencias de 220Ω o 330Ω
- Cristal de 8 MHz
- Protoboard
- Cables jumper
- PICkit 3

---

## Actividad 1 - Dibujo de una X en la matriz LED

### Objetivo

Mostrar una figura en forma de X utilizando una matriz LED 8x8 controlada por el PIC16F887.

### Descripción

En esta actividad se utilizó el método de multiplexado para encender LEDs específicos de la matriz.  
El programa activa una fila a la vez y envía el patrón correspondiente a las columnas para formar la figura.

La figura de la X se genera encendiendo los LEDs de las dos diagonales de la matriz.

### Funcionamiento esperado

La matriz debe mostrar una X formada por LEDs encendidos en diagonal.

---

## Actividad 2 - Letras de los integrantes

### Objetivo

Mostrar en la matriz LED las primeras dos letras de los nombres de los integrantes del equipo.

### Descripción

En esta actividad se programaron patrones para representar letras en la matriz LED 8x8.  
Se utilizaron arreglos de 8 posiciones, donde cada valor representa el patrón que debe mostrarse en una fila de la matriz.

Las letras mostradas corresponden a:

- C de Cristian.
- R de Cristian.
- E de Edgar.
- D de Edgar.

De esta manera, la matriz muestra las letras **C, R, E y D** de forma secuencial.

### Funcionamiento esperado

La matriz debe mostrar las letras una por una, con un retardo entre cada letra para que puedan observarse claramente.

Secuencia esperada:

C → R → E → D

---

## Archivos incluidos

En esta carpeta se incluyen los archivos correspondientes a la práctica:

- Código fuente en C.
- Simulación en Proteus.
- Evidencias del funcionamiento físico o simulado.

---

## Resultado

Se logró controlar una matriz LED 8x8 utilizando el microcontrolador PIC16F887.

En la primera actividad se mostró una figura en forma de X.  
En la segunda actividad se mostraron las letras iniciales de los nombres de los integrantes del equipo: **C, R, E y D**.

Esta práctica permitió comprender el funcionamiento del multiplexado y el uso de patrones binarios para representar figuras y letras en una matriz LED.
