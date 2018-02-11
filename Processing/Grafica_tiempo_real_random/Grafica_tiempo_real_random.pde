float prevY;        // Se inicializa la variable a graficar como cero 
 
void setup() {
  size(800, 700);   // Tamano de la ventana: Width, Height
  frameRate(30);    // Para graficar a 30 puntos por segundo
  cuadricula();
}
void draw() {
  float plotVar = random(height);    // Esta es la variable que se desea graicar
  strokeWeight (2);   // Grosor del trazo
  stroke(0, 0, 255);  // Grafico azul
  translate(15, 0);   // Traslado 15 hacia la derecha
  line(frameCount-1, prevY, frameCount, plotVar);  //X1, Y1, X2, Y2
  prevY = plotVar;    // El punto desde donde comienza la linea sera la muestra anterior
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
    stroke(0);                    // Lineas horizontales negras
    line(15, j, width-10, j);
  }
}