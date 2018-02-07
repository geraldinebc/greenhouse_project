import processing.serial.*;

Serial puerto;
int header, most1, least1, high, low, data1, D1, D2;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200); //El [0] se cambia segun el puerto en cuestion
  size(1250,900);
}

void draw(){
background(0);
  while(puerto.available() > 0){ //Recibo [11110001   0D1D2AAAAA   0AAAAAAA]
    header = puerto.read();      //Encabezado 11110001=241
    most1 = puerto.read();       //Leo el segundo bloque de la trama
    least1 = puerto.read();      //Leo el tercer bloque de la trama
    D1 = (most1>>6)&1;           //Aislo el bit correspondiente al primer sensor digital
    D2 = (most1>>5)&1;           //Aislo el bit correspondiente al segundo sensor digital
    println("Encabezado: " + header);
    println("Sensor digital 1: " + D1);
    println("Sensor digital 2: " + D2);
    println("Bits mas significativos del sensor analogico: " + most1);
    println("Bits menos significativos del sensor analogico: " + least1);
    high = most1 & 31;          //Aislo los bits correspondientes al sensor analogico [0D1D2AAAAA]&[00011111]=[000HHHHH]
    conversion(high, least1);
  }
}

void conversion(int valor1, int valor2){
  high = valor1<<7;               //Pongo los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  low  = valor2;                  //Mantengo los bits menos significativos en el mismo lugar [0LLLLLLL]
  data1 = high|low;               //Obtenengo la data1 completa (valor de 12 bits) [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  println("Sensor analogico: " + data1);
}