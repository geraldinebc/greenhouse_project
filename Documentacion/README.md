# Proyecto: Invernadero Inteligente

## Tabla de Contenidos
- [Justificación](#justificación)
- [Descripción General](#descripción-general)
- [Implementación](#implementación)
- [Software](#software)
- [Documentación técnica](#documentación)

## Justificación

Los agricultores para la producción de frutos con altos índices de calidad, libre de enfermedades y plagas, necesitan un ambiente cerrado y controlado, donde en riego debe ser constante, y tener buena iluminación, para el buen desarrollo de las plantas, es por ello que surge la idea de los invernaderos, pero que mejor forma de controlar un invernadero que bajo sistemas automatizados con sensores para las variables necesaria para el buen funcionamiento y maximización en la producción.

Debido a todas las necesidades observadas en un invernadero, principalmente la cantidad de personal que cuiden y mantengan el área, se plantea la idea de construir un invernadero inteligente. Dicho invernadero contará con una cantidad de sensores para la mantención del mismo, con un adicional de sistema de riego con agua reciclada para disminuir gastos, y contribuir con el planeta.

## Descripción General

El invernadero contará con cinco sensores para medir las condiciones mínimas de la plantación, y a través de estas, seguir acciones programadas, garantizando las condiciones mínimas que necesita el cultivo. Las variables mínimas que se deben garantizar son: humedad de la tierra, luminosidad del ambiente y temperatura. A partir de estas variables se toman ciertas acciones que regulan el ambiente, y estabilizan las variables en los valores óptimos. Al sistema Central llega información a través de los sensores desplegados a lo largo del invernadero, en este se realiza todo el procesamiento de la información que a su vez se envía por serial al ordenador para mostrar la información relevante mediante una interfaz gráfica y establecer la lógica de control que determina qué acciones son necesarias.

El sistema depende de 5 sensores y un timer, que permiten ejecutar 5 controles. Los sensores servirán para conocer si está lloviendo (acelerómetro), si la tierra está húmeda (higrómetro) y si el nivel del tanque es el óptimo para regar la plantación (ultrasonido), si el nivel de luz es el adecuado (LDR) y si la temperatura no excede el límite establecido (sensor de temperatura).  mientras que el timer manejará la frecuencia en la que se debe regar. Control 1, acceso de agua de tuberías, al cual se habilitará si el nivel de agua del tanque no es óptimo y no está lloviendo. Control 2, acceso de agua de la lluvia, se habilita cuando el nivel de agua en el tanque no es el óptimo y está lloviendo. Control 3, ventilación que se activa si la temperatura asciende por encima del límite. Control 4, sistema de iluminación, que aumenta o disminuye la intensidad de la luz que incide sobre el terreno según sea necesario. Control 5, sistema de riego que se habilita a una misma hora todos los días. 

## Implementación

- [Firmware](https://github.com/geraldinebc/greenhouse_project/tree/master/Firmware)
- [Hardware](https://github.com/geraldinebc/greenhouse_project/tree/master/Hardware)
- [Software](https://github.com/geraldinebc/greenhouse_project/tree/master/Software)

## Requisitos principales

   **Hardware**
   
    - Tarjeta de desarrollo DEMOQE128
    - Microcontrolador Freescale MC9S08QE128
    - Acelerómetro MMA1270EG
    - Sensor de temperatura LM35
    - Sensor ultrasónico SRF04
    - Fotorresistencia
    - Higrómetro FC28

   **Software**
   
    - CodeWarrior v10.5 + Processor Expert.
    - Processing 3.6 

## Documentación técnica

[Manual de usuario DEMOQE128](https://github.com/geraldinebc/greenhouse_project/blob/master/Documentacion/DEMOQE_User_Manual.pdf)

[Manual de usuario Processor Expert]( https://github.com/geraldinebc/greenhouse_project/blob/master/Documentacion/Processor_Expert_User_Manual.PDF)
