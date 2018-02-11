import processing.serial.*;

Serial puerto;
int header, most1, least1, high, low, data, D1, D2, prevdata;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200);
  size(800, 700);   // Tamano de la ventana: Width, Height
  frameRate(30);    // Para graficar a 30 puntos por segundo
  cuadricula();
}

void draw(){
  while(puerto.available() > 0){ //Recibo [11110001   0D1D2AAAAA   0AAAAAAA]
    header = puerto.read();      //Encabezado 11110001=241
    most1 = puerto.read();       //Leo el segundo bloque de la trama
    least1 = puerto.read();      //Leo el tercer bloque de la trama
    D1 = (most1>>6)&1;           //Aislo el bit correspondiente al primer sensor digital
    D2 = (most1>>5)&1;           //Aislo el bit correspondiente al segundo sensor digital
    println("Encabezado: " + header);
    println("Sensor digital 1: " + D1);
    println("Sensor digital 2: " + D2);
    high = most1 & 31;           //Aislo los bits correspondientes al sensor analogico [0D1D2AAAAA]&[00011111]=[000HHHHH]
    data = conversion(high, least1);
    println("Sensor analogico: " + data);
  }
  plot(data);
}

int conversion(int valor1, int valor2){
  high = valor1<<7;               //Pongo los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  low  = valor2;                  //Mantengo los bits menos significativos en el mismo lugar [0LLLLLLL]
  data = high|low;                //Obtenengo la data1 completa (valor de 12 bits) [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  return data;
}
 
void plot(int data){
  int newdata = data;           // Esta es la variable que se desea graicar
  strokeWeight (2);             // Grosor del trazo
  stroke(0, 0, 255);            // Grafico azul
  translate(15, 0);             // Traslado 15 hacia la derecha
  line(frameCount-1, prevdata, frameCount, newdata);  //X1, Y1, X2, Y2
  prevdata = newdata;           // El punto desde donde comienza la linea sera la muestra anterior
}
 
void cuadricula() {
  background(255);               // Fondo de color blanco
  for (int i = 0; i <= width-50; i += 50) {
    fill(0, 0, 0);               // Letras negras
    text(i/2, i-10, height-15);  // Texto, coord X, Coord Y
    stroke(0);                   // Lineas verticales negras
    line(i, height-30, i, 0);
  }
  for (int j = 0; j < height; j += 140) {
    fill(0, 0, 0);               // Letras negras
    text(10-j/(height/10), 5, j);
    stroke(0);                   // Lineas horizontales negras
    line(15, j, width-10, j);
  }
}