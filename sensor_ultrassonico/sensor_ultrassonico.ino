// sensor ultrassonico

int trigPin = 4;
int echoPin = 2;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long distanciaCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  long cm = duration * 0.034 / 2;
  return cm;
}

void loop() {
  long dist = distanciaCM();

  Serial.print("Distância: ");
  Serial.print(dist);
  Serial.println(" cm");

  delay(200);
}