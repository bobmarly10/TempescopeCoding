const int misterPin = 5;

void setup() {
  pinMode(misterPin, OUTPUT);
}

int misterState = 0;

void loop() {
  if (misterState == HIGH) {
    analogWrite(misterPin, HIGH);
  }
  if (misterState == LOW) {
    analogWrite(misterPin, LOW);
  }
}
