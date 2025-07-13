#include <Servo.h>  // Include biblioteca pentru controlul servomotoarelor

// Pinuri pentru driver-ul motorului
#define ENA 5  // Pin pentru controlul vitezei motorului stânga
#define ENB 6  // Pin pentru controlul vitezei motorului dreapta
#define IN1 3  // Pin pentru direcția motorului stânga
#define IN2 4  // Pin pentru direcția motorului stânga
#define IN3 2  // Pin pentru direcția motorului dreapta
#define IN4 7  // Pin pentru direcția motorului dreapta

// Pinuri pentru senzorul ultrasonic
#define Trig 12  // Pin pentru trimiterea semnalului
#define Echo 13  // Pin pentru recepționarea semnalului

// Pinuri pentru senzorii cu infraroșu
#define Sensor1 8  // Pin pentru senzorul 1
#define Sensor2 9  // Pin pentru senzorul 2
#define Sensor3 10 // Pin pentru senzorul 3
#define Sensor4 11 // Pin pentru senzorul 4

// Pin pentru servomotor
#define ServoPin A0  // Pin pentru controlul servomotorului

Servo myservo;  // Declararea obiectului servomotor
float distance; // Variabilă pentru stocarea distanței măsurate

// Setarea vitezei
#define carSpeed 150  // Viteză constantă pentru motor

// Declarația funcțiilor
void forward(); // Funcția pentru deplasare înainte
void back();    // Funcția pentru deplasare înapoi
void left();    // Funcția pentru deplasare spre stânga
void right();   // Funcția pentru deplasare spre dreapta
void stop();    // Funcția pentru oprirea robotului
float GetDistance(); // Funcția pentru măsurarea distanței
void lineTracing();  // Funcția pentru urmărirea liniei

// Configurație inițială
void setup() {
    pinMode(ENA, OUTPUT);  // Setare pin ENA ca ieșire
    pinMode(ENB, OUTPUT);  // Setare pin ENB ca ieșire
    pinMode(IN1, OUTPUT);  // Setare pin IN1 ca ieșire
    pinMode(IN2, OUTPUT);  // Setare pin IN2 ca ieșire
    pinMode(IN3, OUTPUT);  // Setare pin IN3 ca ieșire
    pinMode(IN4, OUTPUT);  // Setare pin IN4 ca ieșire

    pinMode(Trig, OUTPUT); // Setare pin Trig ca ieșire
    pinMode(Echo, INPUT);  // Setare pin Echo ca intrare

    pinMode(Sensor1, INPUT); // Setare pin Sensor1 ca intrare
    pinMode(Sensor2, INPUT); // Setare pin Sensor2 ca intrare
    pinMode(Sensor3, INPUT); // Setare pin Sensor3 ca intrare
    pinMode(Sensor4, INPUT); // Setare pin Sensor4 ca intrare

    myservo.attach(ServoPin); // Atașare servomotor la pinul specificat
    myservo.write(100);       // Setare poziție centrală pentru servomotor
    Serial.begin(9600);       // Inițializare comunicare serială
}

// Bucla principală
void loop() {
    distance = GetDistance();  // Măsurarea distanței

    // Evitarea obstacolelor
    if (distance < 30) {
        back(); // Deplasare înapoi
        delay(500); // Pauză de 500 ms
        stop(); // Oprire robot
        delay(300); // Pauză de 300 ms

        // Verificarea distanței la stânga și dreapta
        myservo.write(20);  // Rotirea servomotorului spre stânga
        delay(500); // Pauză de 500 ms
        float leftDistance = GetDistance(); // Măsurare distanță la stânga

        myservo.write(160); // Rotirea servomotorului spre dreapta
        delay(500); // Pauză de 500 ms
        float rightDistance = GetDistance(); // Măsurare distanță la dreapta

        myservo.write(100); // Poziționarea servomotorului în poziție centrală
        delay(500); // Pauză de 500 ms

        // Alegerea direcției în funcție de distanța măsurată
        if (rightDistance > leftDistance) {
            right(); // Deplasare spre dreapta
            delay(500); // Pauză de 500 ms
        } else {
            left(); // Deplasare spre stânga
            delay(500); // Pauză de 500 ms
        }
    } else {
        // Urmărirea liniei
        lineTracing(); // Apelarea funcției de urmărire a liniei
    }
}

// Funcția pentru măsurarea distanței
float GetDistance() {
    digitalWrite(Trig, LOW); // Setare Trig LOW pentru 2 microsecunde
    delayMicroseconds(2); 
    digitalWrite(Trig, HIGH); // Setare Trig HIGH pentru 10 microsecunde
    delayMicroseconds(10); 
    digitalWrite(Trig, LOW); // Setare Trig LOW

    return pulseIn(Echo, HIGH) / 58.0; // Conversie la cm
}

// Funcția pentru urmărirea obiectului
void lineTracing() {
    int S1 = digitalRead(Sensor1); // Citirea valorii senzorului 1
    int S2 = digitalRead(Sensor2); // Citirea valorii senzorului 2
    int S3 = digitalRead(Sensor3); // Citirea valorii senzorului 3
    int S4 = digitalRead(Sensor4); // Citirea valorii senzorului 4

    if (S1 == LOW && S2 == LOW && S3 == LOW && S4 == LOW) {
        forward(); // Deplasare înainte
    } else if (S1 == HIGH) {
        right(); // Deplasare spre dreapta
    } else if (S4 == HIGH) {
        left(); // Deplasare spre stânga
    } else if (S2 == HIGH) {
        forward(); // Deplasare înainte
    } else {
        stop(); // Oprire robot
    }
}

// Funcții pentru controlul motorului
void forward() {
    analogWrite(ENA, carSpeed); // Setare viteză pentru motorul stânga
    analogWrite(ENB, carSpeed); // Setare viteză pentru motorul dreapta
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW); 
}

void back() {
    analogWrite(ENA, carSpeed); // Setare viteză pentru motorul stânga
    analogWrite(ENB, carSpeed); // Setare viteză pentru motorul dreapta
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
}

void left() {
    analogWrite(ENA, carSpeed); // Setare viteză pentru motorul stânga
    analogWrite(ENB, carSpeed); // Setare viteză pentru motorul dreapta
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); 
    digitalWrite(IN4, HIGH);
}

void right() {
    analogWrite(ENA, carSpeed); // Setare viteză pentru motorul stânga
    analogWrite(ENB, carSpeed); // Setare viteză pentru motorul dreapta
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); 
    digitalWrite(IN4, LOW);
}

void stop() {
    analogWrite(ENA, 0); // Oprire motor stânga
    analogWrite(ENB, 0); // Oprire motor dreapta
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
