# Software

## Descripción 
Interfaz gráfica del proyecto donde se recibe la información, obtenida a través del DEMOQE128, y se muestra mediante animaciones realizadas en Processing. 

## Tabla de contenidos
- [Módulos](#módulos)
- [Descripción de funciones](#descripción-de-funciones)
- [Requisitos](#requisitos)
- [Software](#software)

## Módulos

- [Interfaz Gráfica](https://github.com/geralbarreto/Greenhouse_Project/blob/master/Software/Interfaz_grafica_final.pde): Se muestra un termómetro que varía su estado según la temperatura medida, un tanque que muestra el nivel de agua y cuatro indicadores digitales, el primero indica si hay luz, el segundo la humedad de la tierra, el tercero indica si está lloviendo y el último si se sobrepasa el nivel de temperatura óptimo para el cultivo. Además, se muestran las perturbaciones detectadas por el acelerómetro a tiempo real.

## Descripción de funciones

Para extraer las medidas de los sensores de la trama se procedió a decodificar la data recibida por serial. Para los sensores digitales se realizó un shifteo de 6 o 7 bits a la derecha, dependiendo si correspondía al tercer o cuarto bit del bloque de la trama, y se utilizó la operación AND con 1 para aislar la medida, como se muestra a continuación:

    D1 = (bloque1>>6)&1;               // Sensor de luz
    D2 = (bloque1>>5)&1;               // Sensor de humedad

Para los sensores analógicos se implementó la función “conversión” donde se toman 2 bloques de la trama, se realiza un shifteo de 7 bits a la derecha con el primer bloque para ubicar los bits más significativos al principio del valor y posteriormente se utiliza la operación lógica OR con el siguiente bloque para unir ambas partes, como se muestra a continuación:

    int conversion(int high, int low){
      high = high<<7;               // [HHHHH0000000]
      data = high|low;              // [HHHHH0000000]|[0LLLLLLL] = [HHHHHLLLLLLL]
      return data;
    }

Después de obtener las medidas de los sensores analógicos se procede a mapear dichos valores para que se adapten a las animaciones que se describen más adelante. A su vez se utilizaron filtros digitales para promediar y eliminar las medidas erróneas de los sensores de temperatura y ultrasonido pues en el caso de la temperatura se presentaban constantes fluctuaciones pequeñas y en la implementación del proyecto no es de tanta importancia detectar cambios tan pequeños en la temperatura, en el caso del sensor ultrasónico las medidas presentaban grandes picos por lo que era necesario descartar los valores que diferían mucho de las medidas previas.

Para dibujar el termómetro se cargó la imagen de dos termómetros con una escala en grados centígrados al lado derecho, uno azul para indicar que la temperatura es adecuada y uno rojo para indicar que se sobrepasó la temperatura óptima. Para graficar la medida del termómetro se implementó la función "printerm" en la cual se pinta un rectángulo cuya posición se establece en el lugar correspondiente de la imagen del termómetro y cuya altura depende de la medida extraída de la trama recibida por serial que es mapeada para poder graficar con facilidad. Cabe destacar que como en Processing el origen de coordenadas se encuentra en la parte superior, para aumentar la altura del rectángulo realmente se disminuye el valor que establece el tope del rectángulo, por lo tanto al mapear las medidas se invierte la escala. En la animación del termómetro tambien se muestra, en la parte inferior, la medida exacta de la temperatura en grados centígrados.

![termometros](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/termometros.png)

Para visualizar el nivel del tanque de agua se cargó la imagen de un tanque vacío y se implementó la función "printank" en la cual se dibuja un rectángulo cuya posición se establece en el lugar correspondiente de la imagen del tanque y cuya altura depende de la medida de dicho sensor, que al igual que el caso anterior se mapea para poder graficar con mayor facilidad. Para hacer más realista se agregaron óvalos en la parte superior e inferior de dicho rectángulo y para hacerlo más vistoso se utilizó una función para dibujar burbujas que suben hacia el tope del agua. En el caso de detectar que se llegó a un cierto nivel óptimo se muestra un mensaje arriba del tanque.

![tank](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/tank.png)

Para dibujar la medida del acelerómetro a tiempo real se implementó la función "printacele" en la cual realiza una línea que une los puntos correspondientes a la medida anterior y actual extraída de la trama recibida por serial y cuando se llega al tope derecho de la pantalla se borra dicha línea y se comenzaba de nuevo el proceso. Para graficar las medidas correspondientes a los sensores digitales se utiliza un *if* que verifica el estado de los bits correspondientes a la luz, humedad y lluvia, si se cumple que los bits son iguales a 1 y que la temperatura es óptima se dibujan las imágenes mostradas arriba, de lo contrario, se muestran las imágenes mostradas abajo, por supuesto, cada bit digital se verifica por separado.

![digitales](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/digitales.png)

Finalmente como el cultivo se debe regar a una misma hora todos los días se utilizan las funcione hour y minute de processing para crear una función de alarma que obtiene la hora real y dibuja un esparcidor de agua en la esquina inferior derecha de la interfaz para indicar que se está regando la plantación.

A continuación, se muestran dos imágenes de la interfaz gráfica donde se pueden apreciar los distintos estados:

![Interfaz_grafica_cold](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_cold.png)

![Interfaz_grafica_hot](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_hot.png)

## Requisitos
La implementación fue desarrollada y probada en Windows 7 de 32 y 64 bits.

## Software
Se utilizó la versión 3.3.6 de Processing
