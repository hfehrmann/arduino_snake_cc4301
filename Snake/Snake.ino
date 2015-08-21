
int clk4017 = 3;
int rst4017 = 4;

int clk74595 = 6;
int latchPin =7;
int dataPin = 8;

int left = 11;
int right = 12;
int puller = 10;
byte director;

int wait = 3;
byte mapa[][8]= {{0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,0,0,0,0,0,0}};
byte snake[80];
byte length = 3;
byte dir = B00001000;
//8 up
//4 left
//2 down
//1 right
int selector = 0;
boolean passed = false;

void setup() {       
  Serial.begin(9600);
  
  pinMode(left,INPUT);
  pinMode(right, INPUT);
  pinMode(puller,OUTPUT);
  digitalWrite(puller,HIGH);
  
  pinMode(clk4017, OUTPUT);
  pinMode(rst4017, OUTPUT);
  
  pinMode(clk74595, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  
  digitalWrite(rst4017,HIGH);
  digitalWrite(rst4017,LOW);
  
  randomSeed(analogRead(0));
  random_on_map();
  
  snake[0] = 67;
  snake[1] = 59;
  snake[2] = 51;
  
}

void loop() {
  Serial.println(digitalRead(left));
  for(int i = 0; i<20 ; i++){
    display_cycle();
  }
  if (!passed){
    byte leftInput = digitalRead(left);  
    byte rightInput = digitalRead(right);
    director = (rightInput << 1 ) | leftInput;
    if (director > 0){
      passed = true;  
    }
  }else if ((digitalRead(left) | digitalRead(right)) == 0){
    passed = false;
    if ((director & 2) == 1){
      if (dir == 8){
        dir = 1;
      }else{
        dir = dir << 1;  
      }
    }else{
      if (dir == 1){
        dir = B00001000;
      }else{
        dir = dir >> 1;  
      }
    }
  }
  updateSnake();
  //printSnake();
}

void display_cycle(){ 
  for (int i = 0; i<10 ; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin,clk74595,LSBFIRST,calc_line(i));
    digitalWrite(latchPin,HIGH);
    digitalWrite(clk4017, LOW);
    delay(wait);
    digitalWrite(clk4017, HIGH); 
  } 
}

int calc_line(int index){
  int ret = 0;
  for (int i = 0; i<8 ; i++){
    ret = (ret << 1) | (mapa[index][i] == 2 ? 1 : mapa[index][i]); 
  }
  return ret;
}

void random_on_map(){
  int valor = random(0,80); 
  while (mapa[valor/8][valor%8] == 1){
    valor = random(0,80);
  }
  Serial.print("El resultado fue ");
  Serial.println(valor);
  mapa[valor/8][valor%8] = 2;
}

void updateSnake(){
  mapa[snake[0]/8][snake[0]%8] = (byte)0;
  for(int i=0 ; i<length-1 ; i++){
    snake[i] = (byte)snake[i+1]; 
  }
  byte next = pick_direction();
  if (mapa[next/8][next%8] == 2){
    snake[length] = next;
    mapa[next/8][next%8] = 1;
    random_on_map();
    length++;  
  }
  else if (mapa[next/8][next%8] == 1){
    lost();  
  }
  snake[length-1] = next; 
  mapa[snake[length-1]/8][snake[length-1]%8] = (byte)1;
}

byte pick_direction(){
  if (dir & 8){
    if((snake[length-1])/8 == 0){
      return snake[length-1] + 72;  
    }else{
      return snake[length-1] - 8;
    }
  }
  else if (dir & 4){
    if((snake[length-1]+1)%8 == 0){
      return snake[length-1] - 7;  
    }else{
      return snake[length-1] + 1;
    }
  }
  else if (dir & 2){
    if((snake[length-1])/8 == 7){
      return snake[length-1] - 72;  
    }else{
      return snake[length-1] + 8;
    }
  }
  else if (dir & 1){
    if((snake[length-1])%8 == 0){
      return snake[length-1] + 7;  
    }else{
      return snake[length-1] - 1;
    }
  }
}

void printSnake(){
   for (int i=0; i<length ; i++){
     Serial.print(snake[i]);
     Serial.print(" ");
   }
   Serial.println();
}

void lost(){
   while (true)
    ; 
}
