//Configuração pinagem analógica / Analog pins configuration
const int xAxisPin = A0;
const int yAxisPin = A1;

//Configuração pinagem PWM / PWM pins configuration
const int yPin = 11;
const int bPin = 10;
const int rPin = 9;
const int gPin = 6;

//Configuração da intensidade luminosa dos leds / Leds brightness configuration
int y;
int b;
int r;
int g;

//Leitura dos pinos na direção x e na y / Read values of the pins in the x-axis and y-axis
int xAxisRead;
int yAxisRead;

//Leitura dos pinos em estado neutro / Read values of the pins in the neutral states
int xAxisNeutral;
int yAxisNeutral;

//Estimando o ruído / Noise estimation
int noise = 10;

void setup() {
  
  Serial.begin(9600);
  
  //Conseguindo o valor neutro (Para meu arduino uno, isto basta, podem ser usados outros metódos visando "eliminar" a incerteza aleatória) / Retrieving the neutral value (In my arduino uno, this method is enough, but others can be used to eliminate statistical error) 
  xAxisNeutral = analogRead(xAxisPin);
  yAxisNeutral = analogRead(yAxisPin);
  
}

void loop() {
  //Lendo os valores do eixo x e y / Retrieving the values of x-axis and y-axis
  xAxisRead = analogRead(xAxisPin);
  yAxisRead = analogRead(yAxisPin);


  
  //Dependendo dos valores, calcular a intensidade do led / Calculating led intensity
  if(xAxisRead >= xAxisNeutral + noise){
    y = map(xAxisRead,xAxisNeutral,1023,0,255);
    b = 0;
  }else if(xAxisRead < xAxisNeutral + noise){
    y = 0;
    b = map(xAxisRead,xAxisNeutral,0,0,255);
  }else{
    y = 0;
    b = 0;
  }

  if(yAxisRead >= yAxisNeutral + noise){
    r = 0;
    g = map(yAxisRead,yAxisNeutral,0,0,255);
  }else if(yAxisRead < yAxisNeutral + noise){
    r = map(yAxisRead,yAxisNeutral,1023,0,255);
    g = 0;
  }else{
    r = 0;
    g = 0;
  }

  //Escrever os valores correspondentes / Writing corresponding values
  analogWrite(yPin,y);
  analogWrite(bPin,b);
  analogWrite(rPin,r);
  analogWrite(gPin,g);
}
