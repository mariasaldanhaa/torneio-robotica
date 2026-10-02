// ================= SENSOR ULTRASSÔNICO =================
int trigPin = 4;
int echoPin = 2;

// ================= INFRAVERMELHO =================
int irLeft = 11;
int irRight = 3;

// ================= MOTOR =================
int IN1 = 8;
int IN2 = 12;
int ena = 5;

int in3 = 9;
int in4 = 10;
int enb = 6;

// ================= VELOCIDADES =================
#define BUSCA_SPEED 160
#define ATAQUE_SPEED 200
#define FINAL_SPEED 220

// ================= TEMPO =================
unsigned long startTime;
unsigned long ignorarBordaAte = 0;

// ================= BUSCA =================
bool buscaEsquerda = true;
unsigned long trocaBusca = 0;

// ================= ATAQUE =================
bool alvoDetectado = false;
unsigned long ultimoAvistamento = 0;

// ================= DISTÂNCIA =================
long dist = 0;

// =====================================================
// ULTRASSÔNICO
// =====================================================
long distanciaCM() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
        return 999;

    return duration * 0.034 / 2;
}

// =====================================================
// MOVIMENTAÇÃO
// =====================================================
void frente(int v) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(ena, v);
    analogWrite(enb, v);
}

void tras(int v) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(ena, v);
    analogWrite(enb, v);
}

void girarDireita(int v) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(ena, v);
    analogWrite(enb, v);
}

void girarEsquerda(int v) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(ena, v);
    analogWrite(enb, v);
}

void parar() {

    analogWrite(ena, 0);
    analogWrite(enb, 0);
}

// =====================================================
// SETUP
// =====================================================
void setup() {

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ena, OUTPUT);

    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enb, OUTPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(irLeft, INPUT);
    pinMode(irRight, INPUT);

    startTime = millis();
}

// =====================================================
// LOOP
// =====================================================
void loop() {

    // =====================================
    // ESPERA DE 5 SEGUNDOS
    // =====================================
    if (millis() - startTime < 5000) {

        parar();
        return;
    }

    // =====================================
    // BORDA - PRIORIDADE MÁXIMA
    // Preto = HIGH
    // Branco = LOW
    // =====================================
    if (millis() > ignorarBordaAte) {

        bool bordaE = (digitalRead(irLeft) == LOW);
        bool bordaD = (digitalRead(irRight) == LOW);

        if (bordaE || bordaD) {

            // Cancela qualquer ataque
            alvoDetectado = false;

            ignorarBordaAte = millis() + 700;

            // Ré
            tras(FINAL_SPEED);
            delay(250);

            // Giro para dentro da arena
            if (bordaE && !bordaD) {

                girarDireita(FINAL_SPEED);
                delay(250);
            }
            else if (bordaD && !bordaE) {

                girarEsquerda(FINAL_SPEED);
                delay(250);
            }
            else {

                girarDireita(FINAL_SPEED);
                delay(350);
            }

            return;
        }
    }

    // =====================================
    // DETECÇÃO DO ADVERSÁRIO
    // =====================================
    dist = distanciaCM();

    // Detectou oponente
    if (dist > 0 && dist <= 40) {

        alvoDetectado = true;
        ultimoAvistamento = millis();
    }

    // Mantém o ataque por 1 segundo
    // mesmo se perder a leitura
    if (alvoDetectado) {

        frente(ATAQUE_SPEED);

        if (millis() - ultimoAvistamento > 1000) {

            alvoDetectado = false;
        }

        return;
    }

    // =====================================
    // BUSCA
    // =====================================
    if (millis() - trocaBusca > 1000) {

        buscaEsquerda = !buscaEsquerda;
        trocaBusca = millis();
    }

    if (buscaEsquerda) {

        girarEsquerda(BUSCA_SPEED);
    }
    else {

        girarDireita(BUSCA_SPEED);
    }
}