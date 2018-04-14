# Hardware

## Descripción

El siguiente repositorio contiene la implementación del hardware del proyecto, se incluyen los circuitos de alimentación utilizados, la descripción del hardware del sistema central, los sensores con sus respectivos circuitos de acondicionamiento y su documentación técnica.

## Tabla de Contenidos
- [Alimentación](#alimentación)
- [Sistema central](#sistema-central)
- [Protección](#protección)
- [Sensores](#sensores)
- [Documentación Técnica](#documentación-técnica)


## Alimentación

La fuente de alimentación construida es de 5 voltios, debido a que los componentes utilizados se polarizan con 5V-0V. Se construye con un regulador de voltaje LM2990 y un conjunto de condensadores de 10µF como lo indica la imagen.

![Regulador](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/Regulador.png)

A diferencia de la configuración típica, en lugar de usar un solo condensador en la salida de 10µF, se utilizan dos condensadores en paralelo de 100µF y 100nF. Esta nueva configuración se debe a la resistencia que presenta cada condensador, ya que de ésta manera se disminuye su valor para no afectar el valor de la salida. Adicional a esto, para verificar el paso de corriente en la salida se implementa un diodo LED verdad para verificar que esté encendida la fuente.

Esta fuente debe tener una entrada superior a 6.5 Voltios para esperar en la salida 5V, no debe ser menor ya que existe una caída en los componentes y se debe garantizar el valor en la salida. Y se dice superior a 6.5V, ya que el regulador soporta altos voltajes de entradas, sin exceder los 26V.


## Sistema Central

El sistema Central es donde se procesa la información recibida de los sensores y por el usuario, para luego ejecutar las acciones necesarias para regular el ambiente del invernadero. Para el Sistema Central se usa la tarjeta de desarrollo DEMOQE128. Este sistema se desarrolla para demostrar, evaluar y depurar microcontroladores *Freescale*, y puede ser programado vía USB desde un pc o laptop, por donde también puede ser alimentada. Esta tarjeta cuenta con un analizador lógico y un puerto serial virtual mediante USB para un desarrollo rápido. Cuenta con un microcontrolador MC9S08QE128 como se muestra a continuación.

![DEMOQE128](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/DEMOQE128.png)

La programación del DEMOQE128 se hace a través del entorno de programación *Code Warrior*, el cuál utiliza C como lenguaje de programación. Además, se utiliza *Processor Expert* que es una herramienta de *Code Warrior* que utiliza componentes integrados para generar código fuente lo que facilita el proceso de programar micro controladores, ya que permite inicializar dispositivos de una manera sencilla.

En el Sistema Central se programan las rutinas para el acondicionamiento del invernadero, como la apertura de ventanas, encendido de lámparas, iniciar el sistema de riego y la apertura de válvulas que permiten el paso de agua potable o de lluvia. Debido a que no se cuenta con una maqueta y/o los implementos necesarios para tomar acciones con respecto a las medidas tomadas, se implementa el uso de los leds del DEMOQE para mostrar la acción que se debe realizar. Las acciones son: abrir o cerrar ventanas, encender o apagar lámparas, activar o desactivar el llenado del tanque (por lluvia, o por tubería), y activar o desactivar el sistema de riego. En el sistema central también se programa la captura de las señales analógicas o digitales de entrada provenientes de los sensores, así como las salidas que activan algunos de estos sensores y el envío de la información por serial, lo cual se describe en el firmware del proyecto.


## Protección

El sistema de protección del DEMOQE128 se debe a que sus entradas no soportan mayor a 4 voltios, debido a esto se usa un circuito que proteja tanto los sensores como el DEMOQE. Se aplican dos tipos de circuitos de protección, uno para las entradas digitales y otro para las entradas analógicas.

Las entradas analógicas tendrán un seguidor de voltaje para aislar impedancias, seguido de un limitador de voltaje con un zener de 3.0V y una resistencia de protección de 200Ω. De ésta manera no importa que tan grande sea el voltaje de entrada, la salida no superará los 3.0V±0.7V. 

Las entradas digitales esperan voltajes de salida de 0 o 5V, aproximadamente, como 5V es el voltaje de polarización de los elementos amplificadores y de compuertas lógicas, el máximo voltaje es de 5V. Seguido se conecta un divisor de tensión que entrega el 59.45% del voltaje de entrada, es decir, 59.45% de 5V, lo que resulta 2.97V. Luego se conecta con una protección de voltaje con un zener de 3.0V y una resistencia de 200Ω.


## Sensores

En el sistema del invernadero se implementan 5 sensores, de los cuales 2 son digitales y 3 sensores analógicos. Los sensores analógicos son aquellos que su señal de salida es procesada a través de la conversión analógico digital del DEMOQE. Los sensores que trabajan en esta modalidad son el [acelerómetro](#acelerómetro-mma1270eg), el [sensor de temperatura](#sensor-de-temperatura-lm35) y el [sensor ultrasónico](#sensor-ultrasónico-srf04). Los sensores digitales solo pueden tomar dos estados 1 o 0 lógico, es decir, 5V o 0V, respectivamente. Los sensores a utilizar son la [fotorresistencia LDR](#fotorresistencia) el [higrómetro](#higrómetro-fc-28).


## Descripción de los sensores


## Acelerómetro MMA1270EG

Se usa un acelerómetro de un solo eje para indicar si existe precipitación constante y fuerte. Esta señal se puede observar en la interfaz del usuario, para estudiar el comportamiento del acelerómetro y determinar la frecuencia de la precipitación. El sensor estará dispuesto bajo una herramienta cubierta, la cual se llena de agua hasta cierto límite, y se vacía, volviendo a su posición inicial para que pueda seguir llenando. Cada vez que la herramienta se desahogue generara un cambio de altura que es enviado al sistema central a través de la medida del acelerómetro. Dependiendo de la frecuencia en que se generen las señales se puede determinar la cantidad de precipitación.

El acondicionamiento de este sensor viene ya implementado en su tarjeta, sin embargo, para cumplir con los valores de voltaje máximos que se puede utilizar como entrada al DEMOQE se le aplica un divisor de voltaje del 59.45% del valor de la señal; de ésta manera no incurrir a sobre cargar la entrada de la tarjeta de desarrollo. A pesar de contar con un sistema de protección es importante que se aplique dicho divisor, debido a que se requiere recuperar la señal y no obtener una señal saturada.


## Sensor de temperatura LM35

El sensor LM35 es un sensor de temperatura, posee solo tres pines de conexión como se describen en la imagen. 

![LM35](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/LM35.png)

Dicho sensor trabaja con una tensión de entrada desde 4V a 20V, y tiene una precisión de 1°C. Su rango abarca hasta los 150°C, y cada 10mV equivale a un grado centígrado, lo que es perfecto ya que no es necesario hacer conversión de temperatura. Posee baja impedancia de salida, baja corriente de alimentación y bajo costo, sin embargo, tiene una precisión garantizada hasta los 25°C por lo que puede verse afectada la medida para valores superiores.

EL LM35 no requiere circuitería adicional de calibración externa, y por ser su salida lineal, se recomienda para el propósito requerido. A pesar de esto es necesario en este caso implementar un amplificador No Inversor para manejar la data más efectiva dentro del procesador. El factor de amplificación es de 5.6, debido a que un valor más alto podría saturar la salida.


## Sensor ultrasónico SRF04

Este dispositivo se emplea para hacer la medición de la cantidad de agua presente en el tanque, y poder regular el llenado del mismo a través de los otros dispositivos. El sensor detectará que tan distante se encuentra el agua del tanque respecto al tope del mismo por lo tanto se sabrá el nivel de agua.

El sensor ultrasónico, se utiliza para medir distancias entre 3 y 300 centímetros, y tiene un rango de acción efectivo de aproximadamente 30°, observe la figura de abajo. Requiere de una tensión de entrada de 5V, y un pulso de disparo de diez (10) micro segundos mínimos (TTL). 

![ecoSRF04](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/ecoSRF04.png)

El sensor funciona a una frecuencia de 40KHz, el cual emite una onda, espera respuesta (eco) y cuyo ancho es proporcional a la distancia. Este dispositivo cuenta con toda la adquisición necesaria, por lo que su salida es conectada directamente al DEMOQE a través del circuito de protección.

![SRF04](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/SRF04.png)

Para caracterizar el sensor se tomaron las siguientes medidas:

![caract-ultra](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/caract-ultra.PNG)

Se puede destacar que el error entre la medida real y la recibida se debe a que la medida real no fue muy rigurosa y que el sensor detecta otros objetos debido a su rango de captura causando variaciones en la medida.


## Fotorresistencia

![fotorresistencia](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/Fotorresistencia.png)

La resistencia variable por luz permite detectar los lúmenes pues es un componente cuya resistencia disminuye con el aumento de intensidad de luz incidente. Para esta implementación se utiliza un divisor de voltaje con la LDR en la salida, para variar el voltaje según el valor de esta resistencia, este voltaje se utiliza como referencia en un amplificador no inversor. En este caso según los cálculos realizados se necesita un valor de referencia de 1V, en la entrada inversora del amplificador operacional, y en la entrada no inversora conectar la salida del divisor de voltaje. Con esta configuración, una vez el divisor de voltaje este por debajo de 1V, la salida del OPAMP es de 5V de lo contrario permanece en 0V.


## Higrómetro FC-28

El higrómetro de suelo es un sensor que mide la humedad presente en el terreno a través de la variación de la conductividad. Los valores obtenidos van desde 0 sumergido en agua, a 1023 en el aire (o en un suelo muy seco). Un suelo ligeramente húmero daría valores típicos de 600-700. Un suelo seco tendrá valores de 800-1023.

![FC28](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/FC28.png)

El FC-28 se distribuye con una placa de medición estándar que permite obtener la medición como valor analógico o como una salida digital, activada cuando la humedad supera un cierto umbral. Éste dispositivo no tiene la precisión para realizar una medición absoluta de la humedad del suelo, sin embargo, para controlar un sistema de riego no es necesaria tal precisión por lo que se utiliza su salida como digital.

La salida digital dispara cuando el valor de humedad supera un cierto umbral, que ajustamos mediante el potenciómetro. Por tanto, obtendremos una señal LOW cuando el suelo no está húmedo, y HIGH cuando la humedad supera el valor de consigna.

## Documentación técnica

- [Acelerómetro MMA1270EG]( https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/MMA1270EG%20-%20Acelerometro.pdf)
- [Sensor de temperatura LM35](https://github.com/Fedora-Eugenio/Hardware-emisor/blob/master/XRNI53W.pdf)
- [Sensor ultrasónico SRF04](https://github.com/geraldinebc/greenhouse_project/blob/master/Hardware/SRF04%20-Ultrasonico.pdf)
