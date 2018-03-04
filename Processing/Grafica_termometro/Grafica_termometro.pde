PImage termocold, termohot;
int temp, valor;

void setup(){
  size(300, 540);   // Dimensiones de la ventana: Width, Height
  termohot = loadImage("termohot.png");  
  termocold = loadImage("termocold.png");
}

void draw(){
  background(0);
  valor = 1096;                               //Esta sera la medida del senor
  temp = int(map(valor,0, 4096, 0, -340));   //Variable, Escala 1, Escala 2
  if(temp>=-340) printerm(temp);             //Imprime si no se excede del valor maximo
}

void printerm(int temp){
    image(termocold, 0, 0);
    if(temp>-250){            //Se pinta el termometro azul (baja temperatura)
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