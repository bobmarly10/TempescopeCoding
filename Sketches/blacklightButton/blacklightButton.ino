const int blackLightPin = 3;
const int WEATHER_SUNNY = 0;
const int WEATHER_LO_CLOUDY = 1;
const int WEATHER_HI_CLOUDY = 2
const int WEATHER_LO_RAIN = 3;
const int WEATHER_HI_RAIN = 4;
const int WEATHER_DUNDER = 5;

int mode = 0 //adjust this later m8

void setup() {
  pinMode(blackLightPin, OUTPUT);
}

void loop() { //blacklight is used for thunder, unless not bright enough, although it should be
  buttonState = digitalRead(blackLightButton);
  
  if (mode == WEATHER_DUNDER) {
      delay(50);//try every 50 milliseconds 
      if(random(100) == 1) {//1 in 100 chance @ 20 hertz 
        thunder(random(100, 255));
      }
  } 
  
}

void thunder(int x) {
  analogWrite(blackLightPin, x);
  delay(random(10, 300));
  analogWrite(blackLightPin, 0);
}  
