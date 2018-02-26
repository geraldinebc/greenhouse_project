import processing.serial.*;

Serial puerto;
int header, most1, least1, high, low, data, D1, D2, prev=0, a=10, j=0;
int[] grafic = new int[a];	

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200);
  size(800, 400);   // Tamano de la ventana: Width, Height
  cuadricula();
}

void draw(){
  while(puerto.available() > 0){            //Recibo [11110001   0D1D2AAAAA   0AAAAAAA]
      for(int i=0;i<a;i++){
        if(puerto.read() == 241){           //Verifico que se haya leido el header
          most1 = puerto.read();            //Leo el segundo bloque de la trama
          least1 = puerto.read();           //Leo el tercer bloque de la trama
          D1 = (most1>>6)&1;                //Aislo el bit correspondiente al primer sensor digital
          D2 = (most1>>5)&1;                //Aislo el bit correspondiente al segundo sensor digital
          high = most1 & 31;                //Aislo los bits correspondientes al sensor analogico [0D1D2AAAAA]&[00011111]=[000HHHHH]
          data = conversion(high, least1);  //Uno los bits mas y menos significativos de la+ medida del sensor analogico
          grafic[i] = (int)map(data, 0, 4096, height/2, height); //Valor, ini1, fin1, ini2, fin2
        }
     }
    println("Sensor digital 1: " + D1);
    println("Sensor digital 2: " + D2);
    imprimir(grafic);
  }
}

int conversion(int valor1, int valor2){
  high = valor1<<7;               //Se ubican los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  low  = valor2;                  //Mantengo los bits menos significativos en el mismo lugar [0LLLLLLL]
  data = high|low;                //Obtengo la data1 completa (valor de 12 bits) [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  return data;
}

void imprimir(int arreglo[]){
  for(int h=0;h<a-1;h++){
    if(arreglo[h]>0){
      println("Sensor analogico: " + arreglo[h]);
      println("x " + j);
      strokeWeight (3);             // Grosor del trazo
      stroke(0, 0, 255);            // Grafico azul
      if(h==0)line(j, prev, j+1, arreglo[h]); 
      if(h>=1 && h<(a-1))line(j, arreglo[h-1], j+1, arreglo[h]);
      if(h==a-2){
        line(j, arreglo[h], j+1, arreglo[h+1]);
        prev=arreglo[h+1];          //Guardo el ultimo dato como referencia
      }
      j = j+1;
      if (j > width){               //Borro la pantalla y hago de nuevo la cuadricula
        j = 0;
        cuadricula();
      }
    }
  }
}
 
void cuadricula() {
  background(255);                 // Fondo de color blanco
  for (int k=0; k<=width-50; k+=50){
    //fill(0, 0, 0);               // Letras negras
    //text(k/2, k-10, height-15);  // Texto, coord X, Coord Y
    strokeWeight (0);              // Grosor del trazo
    stroke(1);                     // Lineas verticales negras
    line(k, height-30, k, 0);
  }
  for (int z=0; z<height; z+=140){
    //fill(0, 0, 0);               // Letras negras
    //text(5-z/(height/10), 5, z); // Texto, coord X, Coord Y
    strokeWeight (0);              // Grosor del trazo
    stroke(0);                     // Lineas horizontales negras
    line(15, z, width-10, z);
  }
}
