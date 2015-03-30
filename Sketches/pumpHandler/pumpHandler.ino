const int pumpPin = 5;
const int WEATHER_SUNNY = 0;
const int WEATHER_CLOUDY = 1;
const int WEATHER_RAIN = 2;
const int WEATHER_DUNDER = 3;
const int WEATHER_MIST = 4;

int mode = 0 //adjust this later m8

void setup() {
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  if (mode >= WEATHER_LO_RAIN) {
    analogWrite(pumpPin, mode * 51); 
  }
  if (mode < WEATHER_LO_RAIN) {
    analogWrite(pumpPin, 0);
  }
}
