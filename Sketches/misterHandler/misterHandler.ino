const int misterPin = 3;
const int WEATHER_SUNNY = 0;
const int WEATHER_CLOUDY = 1;
const int WEATHER_MIST = 2;
const int WEATHER_LO_RAIN = 3;
const int WEATHER_HI_RAIN = 4;
const int WEATHER_DUNDER = 5;

int mode = 0; //adjust this later m8
int dayEh = false;

void setup() {
  pinMode(misterPin, OUTPUT);
}

void loop() {
  if (mode >= WEATHER_LO_CLOUDY) {
    analogWrite(misterPin, (mode * 20 ) + 5);
  }
  if (mode == WEATHER_SUNNY){
    analogWrite(misterPin, 0);
  }
  
}
