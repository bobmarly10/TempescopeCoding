const int pumpPin = 5;
int pumpOn = 0;

void setup() {
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  if (pumpOn == HIGH) {
    analogWrite(pumpPin, HIGH);
  }
  if (pumpOn == LOW) {
    analogWrite(pumpPin, LOW);
  }
}
