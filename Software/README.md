# Software

## Descripción 
Interfaz gráfica del proyecto donde se recibe la información, obtenida a través del DEMOQE128, y se muestra mediante animaciones realizadas en Processing. 

## Tabla de contenidos
- [Módulos](#módulos)
- [Descripción de funciones](#descripción de funciones)
- [Requisitos](#requisitos)
- [Software](#software)

##Módulos

- [Interfaz Gráfica](https://github.com/geralbarreto/Greenhouse_Project/blob/master/Software/Interfaz_grafica_final.pde): Se muestra un termómetro que varía su estado según la temperatura medida, un tanque que muestra el nivel de agua y cuatro indicadores digitales, el primero indica si hay luz, el segundo la humedad de la tierra, el tercero indica si está lloviendo y el último si se sobrepasa el nivel de temperatura óptimo para el cultivo. Además, se muestran las perturbaciones detectadas por el acelerómetro a tiempo real.
A continuación, se muestran dos imágenes de la interfaz gráfica donde se pueden apreciar los distintos estados:

![Interfaz_grafica_cold](https://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_cold.png)

![Interfaz_grafica_hothttps://github.com/geraldinebc/greenhouse_project/blob/master/Software/Interfaz_grafica_hot.png)

## Descripción de funciones

Para extraer las medidas de los sensores de la trama se procedió a decodificar la data recibida por serial...

## Requisitos
La implementación fue desarrollada y probada en Windows 7 de 32 y 64 bits.

## Software
Se utilizó la versión 3.3.6 de Processing 
