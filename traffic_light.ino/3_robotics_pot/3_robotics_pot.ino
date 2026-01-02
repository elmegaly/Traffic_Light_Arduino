int led=3;
int pot=A0;
int reading;
void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}
void loop(){
  reading=analogRead(pot);
  reading=map(reading,0,1023,0,255);
  analogWrite(led,reading);
  Serial.println(reading);
}