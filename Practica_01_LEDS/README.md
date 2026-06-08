# Práctica 01 - LEDs

## Descripción general

En esta práctica se trabajó con el microcontrolador **PIC16F887** para controlar salidas digitales mediante LEDs.

La práctica está dividida en tres actividades:

1. Encendido y apagado simultáneo de 4 LEDs.
2. Contador binario con 6 LEDs.
3. Caminata de LEDs.

El objetivo principal fue comprender el uso de los puertos digitales del PIC, la configuración de salidas y el manejo básico de secuencias mediante programación en C.

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
- LEDs
- Resistencias de 220Ω o 330Ω
- Cristal de 8 MHz
- Protoboard
- Cables jumper
- PICkit 3

---

## Actividad 1 - Encendido y apagado de 4 LEDs

### Objetivo

Encender y apagar 4 LEDs al mismo tiempo utilizando salidas digitales del PIC16F887.

### Descripción

En esta actividad se configuró un puerto del microcontrolador como salida digital. Posteriormente, se enviaba un valor lógico alto para encender los LEDs y un valor lógico bajo para apagarlos.

Se utilizó un retardo para que el cambio entre encendido y apagado pudiera observarse claramente.

### Funcionamiento esperado

Los 4 LEDs deben encenderse al mismo tiempo, permanecer encendidos durante un momento y después apagarse juntos. Este ciclo se repite continuamente.

---

## Actividad 2 - Contador binario con 6 LEDs

### Objetivo

Realizar un contador binario utilizando 6 LEDs conectados al PIC16F887.

### Descripción

En esta actividad se utilizó una variable contador que incrementa su valor de manera continua. El valor del contador se envía al puerto de salida, permitiendo visualizar el conteo en formato binario mediante los LEDs.

Como se utilizaron 6 LEDs, el conteo va desde **0 hasta 63**, ya que 6 bits permiten representar 64 valores diferentes.

### Funcionamiento esperado

Los LEDs representan el valor binario del contador. El conteo avanza de uno en uno hasta llegar a 63 y posteriormente vuelve a iniciar desde 0.

Ejemplo de conteo:

- 000000
- 000001
- 000010
- 000011
- ...
- 111111

---

## Actividad 3 - Caminata de LEDs

### Objetivo

Crear una secuencia de desplazamiento en los LEDs, conocida como caminata.

### Descripción

En esta actividad se encendió un LED a la vez, desplazando el bit activo de una posición a otra. La secuencia permite observar cómo la luz avanza de un LED al siguiente.

La caminata se realiza avanzando de un extremo al otro y después regresando en sentido contrario.

### Funcionamiento esperado

Los LEDs deben encenderse uno por uno en orden, creando un efecto visual de movimiento.

---

## Archivos incluidos

En esta carpeta se incluyen los archivos correspondientes a la práctica:

- Código fuente en C.
- Simulación en Proteus.
- Evidencias del funcionamiento físico o simulado.

---

## Resultado

Se logró controlar correctamente los LEDs mediante el PIC16F887.

Las tres actividades permitieron comprobar el funcionamiento de las salidas digitales, la representación binaria y el uso de secuencias con desplazamiento de bits.
