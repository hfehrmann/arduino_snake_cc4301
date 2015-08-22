
int clk4017 = 3;
int rst4017 = 4;

int clk74595 = 6;
int latchPin =7;
int dataPin = 8;

int wait = 3;

int cara[]= {66,
             231,
             66,
             0,
             24,
             24,
             129,
             129,
             66,
             60};

void setup() {       
  pinMode(clk4017, OUTPUT);
  pinMode(rst4017, OUTPUT);
  
  pinMode(clk74595, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
}

void loop() {
  for (int i = 0; i<10 ; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin,clk74595,MSBFIRST,cara[i]);
    digitalWrite(latchPin,HIGH);
    digitalWrite(clk4017, LOW);
    delay(wait);
    digitalWrite(clk4017, HIGH); 
  } 
}
