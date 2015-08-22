
int clk4017 = 6;
int rst4017 = 7;


int wait = 3;

void setup() {       
  pinMode(clk4017, OUTPUT);
  pinMode(rst4017, OUTPUT);
  
}

void loop() {
  for (int i = 0; i<10 ; i++){b
    digitalWrite(clk4017, LOW);
    delay(wait);
    digitalWrite(clk4017, HIGH); 
  } 
}
