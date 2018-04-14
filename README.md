# Anteproyecto: Invernadero inteligente con reutilización de recursos

En el presente proyecto se expone un prototipo de invernadero inteligente con sistema de reutilización de recursos con el fin de solventar las dificultades que se presentan a la hora de realizar un cultivo. Se propone un invernadero debido a que este permite tener un mayor control sobre las variables ambientales que afectan la siembra. La razón de que sea inteligente es el ahorro recursos naturales y económicos, de forma que se aprovechen al máximo la cantidad de luz y agua, así como la disminución de la intervención de mano de obra.

El objetivo del proyecto es lograr la automatización del sistema para que este se adapte a los factores ambientales que se presenten en la región de forma inmediata, debido a que en ocasiones ocurren variaciones en el ambiente que afectan el cultivo negativamente. Se plantea que estos procesos se pueden realizar tanto de forma automática como manual, con la posibilidad de que se pueda administrar por un usuario de forma remota mediante el uso de un dispositivo electrónico, en el cual se puede visualizar los factores de interés.

Los procesos que se desean automatizar son el sistema de riego, el control de temperatura y de iluminación. Estos procesos se adaptarán a las condiciones ambientales a través del uso de un conjunto de sensores distribuidos en lugares estratégicos del invernadero; los cuales permiten cuantificar los parámetros de interés, brindando la información que será enviada a un controlador central para la ejecución de una acción programada o una acción “manual”. Las acciones a realizar son:

Sistema de riego: se quiere controlar la frecuencia de riego mediante acciones programadas según las necesidades del cultivo en cuestión, estas pueden realizarse de forma automática, ya que se plantea contar con una base de datos de forma que sólo se realicen los ajustes necesarios o manual, impuesta por un usuario que recibirá informes con las condiciones de la siembra. De esta forma se podrá detectar cuando es necesario activar el sistema de bombeo para el riego y el almacenamiento de agua en el tanque, la cual puede ser de lluvia, reutilizada o proveniente de las tuberías. Los factores a considerar son la humedad del suelo y la lluvia.

Para medir la humedad del suelo se emplea un higrómetro FC-28, que aprovecha la conductividad en sus placas. Este sensor se puede usar con una salida digital o analógica, dependiendo de los requerimientos del usuario. Los valores típicos de un suelo húmedo varían entre 600 y 700, mientras que un suelo seco varía desde 800 a 1023; siendo lo más húmedo 0. A pesar de no ser tan preciso, es un dispositivo que es fácil de implementar, por lo que es ampliamente utilizado para el control de riego automatizado. El valor que arroja dependerá del tipo de suelo, los elementos químicos y agentes presentes, por lo que debe calibrarse.

Además de considerar la humedad del suelo, para la activación de sistema de riego es necesario tener el volumen mínimo de líquido en el tanque para humedecer todo el suelo del invernadero uniformemente, es por ello que se usará un sensor ultrasónico SRF04 para conocer el nivel de agua dentro del tanque. El sensor utiliza un emisor y un receptor, y emite un tren de ocho (8) pulsos ultrasónicos de 40Khz, y espera hasta recibir el eco de la señal al rebotar en un objeto. Con el tiempo de retardo de la señal se puede calcular la distancia entre el objeto y el sensor, donde el área de operación viene restringida por el tiempo mínimo (100us) y máximo (25ms) de espera.  Si el tanque no tiene el nivel mínimo de líquido es necesario accionar una válvula para que permita el ingreso de agua a través de las tuberías, pero como se desea reducir el consumo de agua limpia se contará con un sistema de reciclaje que aprovechara tanto el agua residual del cultivo como la de lluvia.

El agua residual del cultivo entrará constantemente en el tanque para su almacenamiento mientras que para aprovechar el agua de lluvia se contará con un conjunto de sensores piezoeléctricos que permitan detectar las precipitaciones.

Apertura del sistema de ventilación: a través del sensor de temperatura LM35 se pueden ejecutar acciones referentes al control del sistema de ventilación para refrescar el invernadero en el caso de que la temperatura sea muy elevada, mantener la temperatura en caso de condiciones óptimas o cerrar las ventanas y aumentar la temperatura a través de un sistema de calefacción. El LM35 es un sensor de temperatura con precisión calibrada cuya salida es lineal y cada grado Celsius equivale a 10 mV, tiene un rango de medición de -55 °C a 150 °C y no requiere de circuitos de calibración.

Luminosidad del invernadero: dependiendo de la intensidad de luz recibida a través de una fotorresistencia, se disminuye la resistividad del material. De esta forma dependiendo de la cantidad de radiación incidente se desplegará un techo sobre el cultivo sí la radiación es muy alta, de lo contrario se encenderá un sistema interno de iluminación artificial que provee la cantidad de luz necesaria.

Con el sistema planteado anteriormente se garantiza que bajo cualquier condición climática el invernadero se podrá autorregular para adaptarse a condiciones ambientales específicas, de esta manera se hace posible cultivar en épocas del año en las cuales se presentan condiciones desfavorables para el cultivo. Es por ello que este sistema se puede implementar en cualquier invernadero debido a que los parámetros de entrada son ingresados dependiendo del tipo de cultivo.
