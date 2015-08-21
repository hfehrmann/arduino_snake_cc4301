

int left = 11;
int right = 12;
int puller = 10;

void setup(){
 
 Serial.begin(9600); 
  
 //pinMode(left,INPUT);
 pinMode(right,INPUT);
 pinMode(puller,OUTPUT);
 
 digitalWrite(puller, HIGH);
}

void loop(){
  //int l = digitalRead(left);
  int r = digitalRead(right);

  //Serial.print("El valor de la izquierda es: ");
  //Serial.println(l);
  Serial.print(", El valor de la deracha es: "); 
  Serial.println(r);
  delay(1000);
}
