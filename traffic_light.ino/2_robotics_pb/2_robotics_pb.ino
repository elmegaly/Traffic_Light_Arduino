int red=2;
int yellow=3;
int green=4;
int pb=5;
int reading;
int counter;
void setup(){
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);
}
void loop(){
  reading=digitalRead(pb);
  if(reading==1){
    counter++;
    delay(250);
  }
  if(counter==1){
    digitalWrite(2,1);
    digitalWrite(3,0);
    digitalWrite(4,0);
  }
  if(counter==2){
    digitalWrite(2,0);
    digitalWrite(3,1);
    digitalWrite(4,0);
  }
  if(counter==3){
    digitalWrite(2,0);
    digitalWrite(3,0);
    digitalWrite(4,1);
    counter=0;
  }
}