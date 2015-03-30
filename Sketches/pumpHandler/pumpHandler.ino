const int pumpPin = 5;
const int WEATHER_SUNNY = 0;
const int WEATHER_CLOUDY = 1;
const int WEATHER_MIST = 2;
const int WEATHER_LO_RAIN = 3;
const int WEATHER_HI_RAIN = 4;
const int WEATHER_DUNDER = 5;

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
