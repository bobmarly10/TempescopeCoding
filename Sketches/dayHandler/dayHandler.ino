const int RedLEDpin = 11; 
const int BlueLEDpin = 10; 
const int GreenLEDpin = 9; 
int dayEh = false;

void setup() {
  pinMode(RedLEDpin, OUTPUT);
  pinMode(BlueLEDpin, OUTPUT);
  pinMode(GreenLEDpin, OUTPUT);
}

void loop() {
  if (dayEh) {
    analogWrite(); // RGB led's have  3 pins, so I need to make it yellow for daytime
    analogWrite(); 
    analogWrite(); 
  }
}
