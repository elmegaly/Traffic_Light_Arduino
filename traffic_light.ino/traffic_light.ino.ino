int yellow = 2;
int green  = 3;
int red    = 4;

void setup() {
  Serial.begin(9600);

  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  digitalWrite(yellow, HIGH);
  delay(1000);
  digitalWrite(yellow, LOW);

  digitalWrite(green, HIGH);
  delay(1000);
  Serial.println("Elmegaly..!");
  digitalWrite(green, LOW);

  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
}
