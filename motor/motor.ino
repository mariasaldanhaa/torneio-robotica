// motor

// Pinos motor esquerdo
int IN1 = 5;
int IN2 = 6;
int ENA = 5; // PWM - controla velocidade do motor

// Pinos motor direito
int IN3 = 9;
int IN4 = 10;
int ENB = 7; // PWM - controla velocidade do motor

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// função para frente
void frente(int velocidade) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

// função parar
void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// função ré
void tras(int velocidade) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

// girar para direita
void direita(int velocidade) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void loop() {
  frente(200);
  delay(2000);

  direita(200);
  delay(500);

  tras(200);
  delay(1000);

  parar();
  delay(1000);
}