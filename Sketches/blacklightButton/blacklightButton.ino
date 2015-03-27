const int blackLightButton = 2;
const int blackLightPin = 3;

void setup() {
  pinMode(blackLightButton, INPUT);
  pinMode(blackLightPin, OUTPUT);
}

int on = 0;
int buttonState = 0;

void loop() {
  buttonState = digitalRead(blackLightButton);
  if (buttonState == HIGH) {
    on = 1 - on;
  }
  if (on == 1) {
    analogWrite(blackLightPin, HIGH);
  }
  if (on == 0) {
    analogWrite(blackLightPin, LOW);
  }
}
