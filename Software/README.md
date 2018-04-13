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
A continuación, se muestran dos imágenes de la interfaz gráfica donde se pueden apreciar los distintos estados:

![Interfaz_grafica_cold](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_cold.png)

![Interfaz_grafica_hot](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_hot.png)


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

Después de obtener las medidas de los sensores analógicos se procede a mapear dichos valores para que se adapten a las animaciones que se describen más adelante.

## Requisitos
La implementación fue desarrollada y probada en Windows 7 de 32 y 64 bits.

## Software
Se utilizó la versión 3.3.6 de Processing 
