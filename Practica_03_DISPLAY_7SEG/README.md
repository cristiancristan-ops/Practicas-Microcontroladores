# Práctica 03 - Display de 7 Segmentos

## Descripción general

En esta práctica se trabajó con un **display de 7 segmentos** utilizando el microcontrolador **PIC16F887**.

La práctica consistió en controlar los segmentos del display mediante salidas digitales del PIC para representar números y caracteres hexadecimales.

Se realizaron dos actividades principales:

1. Conteo del 0 al 9 en un display de 7 segmentos.
2. Conteo hexadecimal del 0 a la F en un display de 7 segmentos.

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
- Display de 7 segmentos
- Resistencias de 220Ω o 330Ω
- Cristal de 8 MHz
- Protoboard
- Cables jumper
- PICkit 3

---

## Actividad 1 - Conteo del 0 al 9

### Objetivo

Mostrar un conteo decimal del **0 al 9** utilizando un display de 7 segmentos controlado por el PIC16F887.

### Descripción

En esta actividad se programaron los patrones necesarios para encender los segmentos correspondientes a cada número decimal.

El microcontrolador envía al display la combinación de bits necesaria para formar cada dígito, comenzando desde el 0 hasta llegar al 9.

Al terminar el conteo, la secuencia se reinicia nuevamente desde 0.

### Funcionamiento esperado

El display debe mostrar los números en el siguiente orden:

0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9

Después de mostrar el 9, el conteo vuelve a iniciar desde 0.

---

## Actividad 2 - Conteo hexadecimal del 0 a la F

### Objetivo

Mostrar un conteo hexadecimal desde **0 hasta F** utilizando un display de 7 segmentos controlado por el PIC16F887.

### Descripción

En esta actividad se amplió el conteo para incluir valores hexadecimales.  
Además de los números del 0 al 9, se agregaron las letras necesarias para representar los valores del 10 al 15 en hexadecimal.

Al finalizar la secuencia en F, el conteo se reinicia nuevamente desde 0.

### Funcionamiento esperado

El display debe mostrar la siguiente secuencia:

0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → A → B → C → D → E → F

Después de mostrar la F, el conteo vuelve a iniciar desde 0.

---

## Archivos incluidos

En esta carpeta se incluyen los archivos correspondientes a la práctica:

- Código fuente en C.
- Simulación en Proteus.
- Evidencias del funcionamiento físico o simulado.

---

## Resultado

Se logró controlar un display de 7 segmentos mediante el microcontrolador PIC16F887.

En la primera actividad se realizó un conteo decimal del **0 al 9**.  
En la segunda actividad se realizó un conteo hexadecimal del **0 a la F**.

Esta práctica permitió comprender cómo se representan números y caracteres mediante la activación de segmentos individuales en un display de 7 segmentos.
