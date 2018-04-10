import processing.serial.*;
Serial puerto;
int bloque1, bloque2, bloque3, bloque4, bloque5, bloque6, D1, D2, D3, D4, data, acele, temp, analog1, analog2, analog3, prev, level,  x, valor, nivel;
PImage termocold, termohot, tank, tempcold, temphot, moist, dry, sun, cloud, rain, norain;
ArrayList<Bubble> bubbles;
int add = 0;
int initial = 10,t,T,promtemp,promlevel=0,promlevelant, promedio;

void setup(){
  puerto = new Serial(this, Serial.list()[0], 115200);
  size(800,820);                       // Dimensiones de la ventana: Width, Height
  termocold = loadImage("termocold.png");
  termohot = loadImage("termohot.png");
  tempcold = loadImage("tempcold.png");
  tank = loadImage("tanque.png");
  temphot = loadImage("temphot.png");
  moist = loadImage("moist.png");
  dry = loadImage("dry.png");
  cloud = loadImage("cloud.png");
  sun = loadImage("sun.png");
  rain = loadImage("rain.png");
  norain = loadImage("norain.png");
  image(termocold, 0, 0);
  image(tank, 400, 0);
  cuadricula();
  bubbles = new ArrayList<Bubble>();
}

void draw(){
    while(puerto.available() > 4){       // Recibo la trama codificada [11110011 0D1D2AAAAA 0aaaaaaa 0D3D4BBBBB 0bbbbbbb 000CCCCC 0ccccccc]
    if(puerto.read() == 243){            // Verifico que se haya leido el header
      bloque1 = puerto.read();           // Acelerometro
      bloque2 = puerto.read();
      bloque3 = puerto.read();           // Sensor de temperatura
      bloque4 = puerto.read();
      bloque5 = puerto.read();           // Sensor ultrasonico
      bloque6 = puerto.read();
      
      // Decodificacion //
      D1 = (bloque1>>6)&1;               // Sensor de luz
      D2 = (bloque1>>5)&1;               // Sensor de humedad
      D3 = (bloque3>>6)&1;               // Sensor de sismo
     
      image(tempcold, 715, 480);   
      // Se notifica el estado del sensor digital
      if (D1==1) image(cloud, 415, 480);
      else image(sun, 415, 480);
      if (D2==1) image(dry, 515, 480);
      else image(moist, 515, 480);
      if (D3==1) image(norain, 615, 480);
      else image(rain, 615, 480);

      // Aislo los bits correspondientes al sensor analogico, bloque & 31 = [0D1D2AAAAA] & [00011111] = [000HHHHH]
      analog1 = conversion((bloque1&31), bloque2);           // Se unen los bits mas y menos significativos de la medida del acelerometro
      acele = (int)map(analog1, 0, 4096, 700, 0);            // Se transforman los valores a una escala adecuada para graficar
      printacele(acele);                                     // Se utiliza una funcion para graficar a tiempo real la senal medida por el acelerometro
      analog2 = conversion((bloque3&31), bloque4);           // Uno los bits mas y menos significativos de la medida del sensor de temperatura
      temp = (int)(map(analog2, 0, 190, 0, -350));           // Variable, Escala 1, Escala 2
      if(t!=100) promtemp = promtemp + temp;                 // Se toman 100 muestras de temperatura para hacer un promedio
      else{
        promtemp = promtemp/100;
        t=0;
        printerm(promtemp);                                  // Se utiliza una funcion para graficar un termometro que muestra temperatura medida
        image(tempcold, 715, 480);
        if(promtemp<-241)  image(temphot, 715, 480);   
      }
      t++;
      analog3 = conversion((bloque5&31), bloque6);           // Uno los bits mas y menos significativos de la medida del sensor ultrasonico
      level = int(map(analog3, 0, 250, -300, 0));            // Variable, Escala 1, Escala 2
      if(T!=100) promlevel = promlevel + level;             // Se toman 100 muestras de temperatura para hacer un promedio
      else{
        promedio = promlevel/100;
        T=0;
        promlevel=0;
        if (abs(promlevelant-promedio)<5){                  // Filtro digital del sensor ultrasonico
          if(promedio<0) printank(promedio);               // Se utiliza una funcion para graficar un tanque que muestra el nivel de agua
          printbubble();
        }
      promlevelant = promedio; 
      }
      T++;                              
      }
   }
}
int conversion(int high, int low){
  high = high<<7;               // Se ubican los bits mas significativos en el lugar que corresponde [HHHHH0000000]
  data = high|low;              // Obtengo la lectura completa de 12 bits [HHHHH0000000]|[0LLLLLLL]=[HHHHHLLLLLLL]
  return data;
}

void printerm(int temp){
    if(temp>=-240){
    image(termocold, 0, 0);       //Se pinta el termometro azul (baja temperatura)
    fill(1, 144, 233);
    stroke(1, 144, 233);
    rect(175, 416, 35, temp-15);  // X,Y,Width,Height
    fill(255);
    textSize(35);
    text(+(-temp/8), 300, 525); 
    text("°C", 350, 525); 
    }
    if(temp<-240){                //Se pinta el termometro rojo (alta temperatura)
    image(termohot, 0, 0);
    fill(253, 47, 26);
    stroke(253, 47, 26);
    rect(175, 416, 35, temp-15);
    fill(255);
    textSize(35);
    text(+(-temp/8), 300, 525); 
    text("°C", 350, 525); 
    }
}

void printank(int level) {
  image(tank, 400, 0);
  fill(127, 199, 239);
  stroke(127, 199, 239);
  rect(436, 447, 324, level);    //X, Y, Width, Height
  strokeWeight(2);
  stroke(71,71,71);
  ellipse(599, 448, 326, 45);
  stroke(255);
  ellipse(599, 447+level, 326, 45);
}

void printbubble(){
  bubbles.add(new Bubble(int(random(2, 15))));
  for (int i = bubbles.size()-1; i >= 0; i--){
     Bubble b = bubbles.get(i);
     b.ascend();
     b.display();
     if (b.top()){
       bubbles.remove(i);
     }
    }
}

class Bubble{
    float x, y, diameter;
    //Constructor
    Bubble(float tempD){
      x = random(445,750);
      y = 440;
      diameter = tempD;
  }
   
    //Mueve las burbujas hacia arriba y hacia los lados
    void ascend(){
      y = y - random(2, 20);  //Movimiento en y
      x = x + random(-1, 1);   //Movimiento en x
    }
   
    //Dibuja las burbujas
    void display(){
      noStroke();
      fill(231, 254, 255, 200);
      ellipse(x, y, diameter, diameter);
    }
   
    //Chequea si la burbuja esta en el tope del nivel del agua
    boolean top(){
      if (y < 475+level) return true;
      else return false;
    }
}

void printacele(int data){
  //println("Acelerometro: " +data);
  strokeWeight (3);               // Grosor del trazo
  stroke(0);                      // Linea negro
  line(x, prev, x+1, data);       // Hago una linea desde el valor previo hasta el siguiente
  prev = data;                    // Guardo una referencia para hacer la siguiente linea
  x = x+1;                        // Se aumenta el contador x (eje horizontal)
  if (x > width){                 // Borro la pantalla y hago de nuevo la cuadricula
    x = 0;
    strokeWeight (0);
    cuadricula();
  }
}

void cuadricula() {
  fill(255);                       // Rectangulo blanco
  rect(0, 550, 800, 1100);         // X, Y, Width, Height
  for (int k=0; k<=width; k+=100) {
    strokeWeight(0);               // Grosor del trazo
    stroke(0);                     // Lineas verticales negras
    line(k, height, k, 550);
  }
  for (int z=550; z<height; z+=70) {
    strokeWeight (0);              // Grosor del trazo
    stroke(0);                     // Lineas horizontales negras
    line(0, z, width, z);
  }
}
