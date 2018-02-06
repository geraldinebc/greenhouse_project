import processing.serial.*;

Serial puerto;
int header, most1, least1, high, low, data1, D1, D2;
float inByte = 0;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200); //El [0] se cambia segun el puerto en cuestion
  size(1250,900);
  puerto.clear();  // Se elimina la primera lectura, en caso de que se haya comenzado a leer en el medio de una cadena
}

void draw(){
background(0);
  while(puerto.available() > 0){  //la trama leida contiene [1 1 1 1 0 0 0 1 0 D1 D2 A A A A A 0 A A A A A A A]
    header = puerto.read();    //lee el header 11110001=241
    most1 = puerto.read();     //lee los 8 bits mas significativos
    least1 = puerto.read();    //lee los 8 bits menos significativos
    D1 = most1>>6;             //Sensor digital 1
    D2 = (most1>>5)&1;         //Sensor digital 2
    println(header);           //Imprimo el header
    println(D1);               //Imprimo la lectura del primer sensor digital
    println(D2);               //Imprimo la lectura del segundo sensor digital
    high = most1 & 31;         //[0D1D2AAAAA]&[00011111]=[000HHHHH]
    conversion(high, least1);  //Uno los bits mas significativos con los menos significativos del sensor analogico
  }
}

void conversion(int valor1, int valor2){
  high = valor1<<7;               //Shifteo hacia la izquierda [HHHHH0000000]
  low  = valor2;
  data1 = high|low;               //Para obtener la data1 completa (valor de 12 bits) uso or [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  println(data1);
}