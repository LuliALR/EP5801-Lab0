# EP5801-Lab0
Laboratorio 0 de la materia de Sistemas Embebidos 1

### Objetivos a cubrir:
     - Introducción a los entornos de desarrollo Visual Studio Code y MPLAB x IDE
     - Estructura básica de un programa en C
     - Uso de las directivas del preprocesador
     - Librerías estándar de C (`stdint.h, stdio.h`)
     - Tipos de datos (char, int, float, double)
     - Redefinición de los datos (`typedef`)
     - Estructuras (`Structures`), Enumeraciones (`Listing`) y Uniones (`Unions`)
     - Pilas (`Stack`)

### Descripción del laboratorio:

El presente sirve como base para afianzar los conceptos que se utilizarán a lo largo del curso, estudiando así la aplicación de los aspectos fundamentales de la programación en lenguaje C.
Para el desarrollo del mismo se utilizarán los ambientes de programación (Visual Studio Code y MPLAB x IDE), para permitir el aprendizaje del proceso de la: Redacción, compilación, depuración y ejecución del código; tanto en plataforma PC, como en el PIC 18F47Q10.
Además, se han de introducir ejemplos para el manejo del primer tipo abstracto de datos del curso, las Pilas (`Stack`).

### Apartado 1: Tipos de Datos y Estructuras.

En este primer inciso se busca trabajar con los tipos básicos de datos encontrados en el lenguaje C, tal como en los tipos adicionales disponibles en el archivo de cabecera `stdint.h`; con esto en mente, se plantea el siguiente problema:    

1. Sea un sistema embebido que se encarga de la medición del nivel de agua en un hogar; para ello, se tiene un microcontrolador de 8 bits conectado a un sensor especifico de dirección 0xA0 en los puertos SDA y SCL utilizando el protocolo de comunicación `i2c`. Al solicitarle una medición (al sistema), el mismo envía un paquete de 12 bytes, que según las especificaciones del fabricante se corresponden con los siguientes valores:

| Posición de los bytes    | Significdo                            | Signo de la variable |
| ------------------------ | ------------------------------------- | -------------------- |
| 0                        | Nivel de Batería del dispositivo      | Sin signo            |
| 1-2                      | Temperatura                           | Con signo            |
| 3-4-5                    | Nivel del tanque de agua de reserva   | Con signo            |
| 6-7-8-9                  | Nivel del tanque de agua principal    | Sin signo            |
| 10-11                    | Checksum                              | Sin signo            |

2. Una función inherente al sistema se encarga de pedir y convertir la información, entregando asi de esta manera un arreglo (`array[N]`) de longitud `N = 12`. Dicho arreglo es la entrada de una función que Usted debe implementar con las siguientes características:
    - El argumento de entrada corresponden a un arreglo o puntero de tipo `uint8_t`.
    - Devuelve una estructura con los tipos que Usted considere pertinentes para ordenar la información según los requerimientos.
    - Debe contener al menos una redefinición de variable usando `typedef`.

El uso de Uniones es opcional en este inciso; pero, se considerarán las implementaciones que las contengan para puntos adicionales.

#### SOLUCION:

La solución de este apartado se encuentra en los siguientes archivos:
- `lab0_structs`: Se implementa la solución únicamente a través de estructuras.
- `lab0_unions`: Se implementa la solución haciendo uso de uniones.

### Apartado 2: Tipos Abstractos de Datos - Pilas (`Stack`)

En este apartado se producrá la implementación propia de una Pila (`stack`), siguiendo el planteamiento explicado en las clases y que es complementado con la información disponible en la imagen 1 e imagen 2. Esta Pila debe ser implementada tanto de manera estática como dinámica en dos archivos separados(`static_stack.c` y  `dynamic_stack.c`). Con estas implementaciones se resolverá el siguiente problema:

1. En un dispositivo embebido se tienen configuradas una serie de interrupciones externas asociadas a los diversos pines de entrada de proposito general (`GPIO`).  Un vector de interrupción manejado por el microcontrolador se encargará de entregar las interrupciones de forma individual a la Pila implementada anteriormente. Se debe entonces diseñar una función que cumpla con los siguientes requerimientos:
     
     - La entrada de la función corresponde a la salida de los items en una Pila. 
     - La función acepta de entrada una referencia a una estructura de tipo item.
     - La salida de la función será de tipo entero y dependerá de la interrupción ejecutada.
     - La entrada es un arreglo de tamaño N y puede contener cualquiera de las siguientes instrucciones en un orden aleatorio:

| Instrucción | Acción a tomar                                            |               
| ----------- | --------------------------------------------------------- |
| 0x00        | Hacer toggle de una variable booleana para el pin 1       |    
| 0x01        | Imprimir el valor del pin 1                               |                       
| 0x02        | Aumentar un contador de tipo `size_t`                     |
| 0x03        | Imprimir el contador                                      |
| 0x05        | Verificar el número de items en la pila                   |
| 0x06        | Si la pila está llena, finaliza la ejecución del programa |                      

Se fomenta el uso de enumeraciones para este inciso, pues es una herramienta de mucha utilidad en casos como estos. 

#### SOLUCION:

La solución de este apartado se encuentra en los siguientes archivos:
- `static_stack`: Se implementa la solución de la pila estática
- `dynamic_stack`: Se implementa la solución de la pila dinámica

Ambos archivos contienen la misma lógica de funcionamiento y, en su mayoría, el mismo código. La diferencia radica en que, al momento de definir la estructura correspondiente a la pila, la forma estática define directamente el arreglo con el máximo tamaño posible, mientras que la forma dinámica define un puntero a la dirección de la pila.