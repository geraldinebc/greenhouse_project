import processing.serial.*;

Serial puerto;
int bloque1, bloque2, bloque3, bloque4, bloque5, bloque6, D1, D2, D3, D4, data, acele, temp, analog1, analog2, prev, x;	
PImage termocold, termohot;
int valor;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200);
  size(600, 1000);                       // Dimensiones de la ventana: Width, Height
  cuadricula();
}

void draw(){
  while(puerto.available() > 4){        // Recibo la trama codificada [11110011   0D1D2AAAAA   0aaaaaaa 0D3D4BBBBB   0bbbbbbb 000CCCCC 0 ccccccc ]
    if(puerto.read() == 243){           // Verifico que se haya leido el header
      bloque1 = puerto.read();          // Leo los bloques de la trama
      bloque2 = puerto.read();
      bloque3 = puerto.read();
      bloque4 = puerto.read();
      bloque5 = puerto.read();
      bloque6 = puerto.read();
      
      // Decodificacion //
      D1 = (bloque1>>6)&1;               // Aislo los bits correspondientes a los sensores digitales
      D2 = (bloque1>>5)&1;
      D3 = (bloque3>>6)&1;
      D4 = (bloque3>>5)&1;
      
      println("Sensor de humedad: "+D1);  // Imprimo los valores de los sensores digitales
      println("Sensor de luz: "+D2);
      println("Sensor de temperatura: "+D3);
      println("Sensor de vibraciones: "+D4);
      
      // Aislo los bits correspondientes al sensor analogico, bloque & 31 = [0D1D2AAAAA] & [00011111] = [000HHHHH]
      analog1 = conversion((bloque1&31), bloque2);           // Se unen los bits mas y menos significativos de la medida del acelerometro
      acele = (int)map(analog1, 0, 4096, 3*height/4, 150);   // Se transforman los valores a una escala adecuada para graficar
      imprimir(acele);                                       // Se utiliza una funcion para graficar a tiempo real la senal medida por el acelerometro
      analog2 = conversion((bloque3&31), bloque4);           // Uno los bits mas y menos significativos de la medida del sensor de temperatura
      temp = (int)(map(analog2, 0, 4096, 0, -340));          // Variable, Escala 1, Escala 2
      printerm(temp);                                        // Se utiliza una funcion para graficar un termometro que muestra temperatura medida
      }
  }
}

//valor = (((data*0.015625)/(65536))/58)*1000000; //Regla de tres tomando en cuenta que el tiempo maximo del evento capture es 0.015625s y equivale a 2^16=65536

int conversion(int high, int low){
  high = high<<7;               // Se ubican los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  data = high|low;              // Obtengo la lectura completa de 12 bits [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  return data;
}

void imprimir(int data){
  println("Acelerometro: " +data);
  strokeWeight (3);               // Grosor del trazo
  stroke(0, 0, 255);              // Grafico azul
  line(x, prev, x+1, data);       // Hago una linea desde el valor previo hasta el siguiente
  prev = data;                    // Guardo una referencia para hacer la siguiente linea
  x = x+1;                        // Se aumenta el contador x (eje horizontal)
  if (x > width){                 // Borro la pantalla y hago de nuevo la cuadricula
    x = 0;
    cuadricula();
  }
}

void printerm(int temp){
    if(temp>-250){            //Se pinta el termometro azul (baja temperatura)
    image(termocold, 0, 0);
    fill(1, 144, 233);
    stroke(1, 144, 233);
    rect(125, 405, 36, temp);
    fill(255);
    textSize(35);
    text(+(-temp/8), 215, 525); 
    text("°C", 255, 525); 
    }
    if(temp<-250){            //Se pinta el termometro rojo (alta temperatura)
    image(termohot, 0, 0);
    fill(253, 47, 26);
    stroke(253, 47, 26);
    rect(125, 405, 36, temp);
    fill(255);
    textSize(35);
    text(+(-temp/8), 215, 525); 
    text("°C", 255, 525); 
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
  for (int z=0; z<height; z+=100){
    //fill(0, 0, 0);               // Letras negras
    //text(5-z/(height/10), 5, z); // Texto, coord X, Coord Y
    strokeWeight (0);              // Grosor del trazo
    stroke(0);                     // Lineas horizontales negras
    line(15, z, width-10, z);
  }
}
