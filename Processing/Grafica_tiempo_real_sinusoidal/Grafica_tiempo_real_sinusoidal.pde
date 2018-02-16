import processing.serial.*;

Serial puerto;
int header, most1, least1, high, low, data, D1, D2, prevdata,i;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200);
  size(800, 400);   // Tamano de la ventana: Width, Height
  frameRate(30);    // Para graficar a 30 puntos por segundo
  cuadricula();
}

void draw(){
  while(puerto.available() > 0){ //Recibo [11110001   0D1D2AAAAA   0AAAAAAA]
  if(puerto.read() == 241){      //Verifico que se haya leido el header
    most1 = puerto.read();       //Leo el segundo bloque de la trama
    least1 = puerto.read();      //Leo el tercer bloque de la trama
    D1 = (most1>>6)&1;           //Aislo el bit correspondiente al primer sensor digital
    D2 = (most1>>5)&1;           //Aislo el bit correspondiente al segundo sensor digital
    println("Sensor digital 1: " + D1);
    println("Sensor digital 2: " + D2);
    high = most1 & 31;                //Aislo los bits correspondientes al sensor analogico [0D1D2AAAAA]&[00011111]=[000HHHHH]
    data = conversion(high, least1);  //Uno los bits mas y menos significativos de la medida del sensor analogico
    if(data!=-1){
    println("Sensor analogico: " + data);
    int grafic = (int)map(data, 0, 4000, 200, 60); 
    plot(grafic);                             //Grafico la medida del sensor analogico a tiempo real
    
    }  
   }
  }
}

int conversion(int valor1, int valor2){
  high = valor1<<7;               //Se ubican los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  low  = valor2;                  //Mantengo los bits menos significativos en el mismo lugar [0LLLLLLL]
  data = high|low;                //Obtenengo la data1 completa (valor de 12 bits) [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  return data;
}
 
void plot(int datos){
  int newdata = datos;             // Esta es la variable que se desea graicar
  strokeWeight (2);             // Grosor del trazo
  stroke(0, 0, 255);            // Grafico azul
  translate(15, 0);             // Traslado 15 hacia la derecha
  line(frameCount-1, prevdata, frameCount, newdata);  //X1, Y1, X2, Y2
  prevdata = newdata;           // El punto desde donde comienza la linea sera la muestra anterior
}
 
void cuadricula() {
  background(255);                 // Fondo de color blanco
  for (int i = 0; i <= width-50; i += 50) {
    //fill(0, 0, 0);               // Letras negras
    //text(i/2, i-10, height-15);  // Texto, coord X, Coord Y
    stroke(0);                     // Lineas verticales negras
    line(i, height-30, i, 0);
  }
  for (int j = 0; j < height; j += 140) {
    fill(0, 0, 0);                 // Letras negras
    //text(5-j/(height/10), 5, j); // Texto, coord X, Coord Y
    stroke(0);                     // Lineas horizontales negras
    line(15, j, width-10, j);
  }
}