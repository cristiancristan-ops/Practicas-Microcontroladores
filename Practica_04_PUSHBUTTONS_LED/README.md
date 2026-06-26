# Práctica 04 - Entradas digitales

## Descripción

En esta práctica se utilizaron botones como entradas digitales para controlar LEDs y un contador con displays de 7 segmentos.

## Clase - Botones y LEDs

Se conectaron tres botones al puerto B y tres LEDs en otro puerto.

Cada botón controla un LED diferente. Al presionar un botón, se enciende el LED que le corresponde y al soltarlo se apaga.

Se utilizaron las resistencias pull-up internas del PIC para los botones.

## Actividad 1 - Contador de 0 a 99

Se realizó un contador con dos displays de 7 segmentos.

El circuito tiene tres botones:

- Un botón suma una unidad.
- Un botón resta una unidad.
- Un botón reinicia el contador en 0.

Cuando el contador llega a 99 y se vuelve a sumar, regresa a 0. Si está en 0 y se resta, pasa a 99.

## Archivos incluidos

- Código de los botones y LEDs.
- Código del contador de 0 a 99.
