#include <Ethernet.h>
#include <SPI.h>

const int pumpPin = 5;
const int misterPin = 3;
const int RedLEDpin = 11; 
const int BlueLEDpin = 10; 
const int GreenLEDpin = 9; 
const int blackLightPin = 3;
const int WEATHER_SUNNY = 0;
const int WEATHER_CLOUDY = 1;
const int WEATHER_MIST = 2;
const int WEATHER_LO_RAIN = 3;
const int WEATHER_HI_RAIN = 4;
const int WEATHER_DUNDER = 5;

int mode = 0;
int dayEh = false;

byte server[] = { 76,126,25,74 };

String location = "./ HTTP/1.0";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

char inString[32];
int stringPos = 0;
boolean startRead = false;

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(misterPin, OUTPUT);
  pinMode(RedLEDpin, OUTPUT);
  pinMode(BlueLEDpin, OUTPUT);
  pinMode(GreenLEDpin, OUTPUT);
  pinMode(blackLightPin, OUTPUT);
  Ethernet.begin(mac);
  Serial.begin(9600);
}

void loop() {
  String pageValue = connectAndRead();
  
  if (pageValue == "01d" || pageValue == "01n" || pageValue == "02d" || pageValue == "02n") {
    mode = 0;
  } else if (pageValue == "03d" || pageValue == "03n" || pageValue == "04d" || pageValue == "04n" || pageValue == "13d" || pageValue == "13n") {
    mode = 1;
  } else if (pageValue == "09d" || pageValue == "09n" || pageValue == "10d" || pageValue == "10n") {
    mode = 2;
  } else if (pageValue == "11d" || pageValue == "11n") {
    mode = 3;
  } else if (pageValue == "50d" || pageValue == "50n") {
    mode = 4;
  }
  
  Serial.println(pageValue);
  
  if (mode >= WEATHER_LO_RAIN) {
    analogWrite(pumpPin, mode * 51); 
  }
  if (mode < WEATHER_LO_RAIN) {
    analogWrite(pumpPin, 0);
  }
  if (mode >= WEATHER_LO_CLOUDY) {
    analogWrite(misterPin, (mode * 20 ) + 5);
  }
  if (mode == WEATHER_SUNNY){
    analogWrite(misterPin, 0);
  }
  if (dayEh) {
    analogWrite(); // RGB led's have  3 pins, so I need to make it yellow for daytime
    analogWrite(); 
    analogWrite(); 
  }
  
  if (mode == WEATHER_DUNDER) {
      delay(50);//try every 50 milliseconds 
      if(random(100) == 1) {//1 in 100 chance @ 20 hertz 
        thunder(random(100, 255));
      }
  } 
  delay(30000); // Five minutes
}

void thunder(int x) {
  analogWrite(blackLightPin, x);
  delay(random(10, 300));
  analogWrite(blackLightPin, 0);
}  

String connectAndRead(){

  Serial.println("connecting...");
  
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();

    return readPage();

  }else{
    return "connection failed";
  }

}

String readPage(){
  
  stringPos = 0;
  memset( &inString, 0, 32 );

  while(true){

    if (client.available()) {
      char c = client.read();

      if (c == '<' ) {
        startRead = true;
      }else if(startRead){

        if(c != '>'){
          inString[stringPos] = c;
          stringPos ++;
        }else{
          startRead = false;
          client.stop();
          client.flush();
          Serial.println("disconnecting.");
          return inString;

        }

      }
    }

  }

}

