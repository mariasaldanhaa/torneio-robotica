const int pinoSensorDireito = 3;
const int pinoSensorEsquerdo = 11;

const int trig = 4;
const int echo = 2;

void setup() {
  Serial.begin(9600);

  pinMode(pinoSensorDireito, INPUT);
  pinMode(pinoSensorEsquerdo, INPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

long distanciaCM() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 10000);

  if (duration == 0)
    return 999;

  long cm = duration * 0.034 / 2;

  return cm;
}

void loop() {

  int leituraDireito = digitalRead(pinoSensorDireito);
  int leituraEsquerdo = digitalRead(pinoSensorEsquerdo);

  long dist = distanciaCM();

  Serial.print("Sensor Esquerdo: ");
  Serial.println(leituraEsquerdo);

  Serial.print("Sensor Direito: ");
  Serial.println(leituraDireito);

  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.println(" cm");

  Serial.println("---------------------");

  delay(2000);
}