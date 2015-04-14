#include <Ethernet.h>
#include <SPI.h>

const int pumpPin = 3;
const int misterPin = 7;
const int RedLEDpin = 5; 
const int BlueLEDpin = 6; 
const int GreenLEDpin = 9; 
const int blackLightPin = 8;
const int WEATHER_SUNNY = 0;
const int WEATHER_CLOUDY = 1;
const int WEATHER_MIST = 2;
const int WEATHER_LO_RAIN = 3;
const int WEATHER_HI_RAIN = 4;
const int WEATHER_DUNDER = 5;

int mode = 0;
boolean dayEh = false;
boolean shiftUpGreen; //used as a fluctuation check, true is going up, false for down
boolean shiftUpRed;

int red = 0;
int green = 0;
int blue = 0;

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
        thunder(random(100, OUTPUT));
      }
  } 
  delay(30000); // Five minutes
}

void thunder(int x) {
  digitalWrite(blackLightPin, x);
  delay(random(10, 300));
  digitalWrite(blackLightPin, 0);
}  

void ambientLight(){
  if(dayEh) { //fluctuate green value
    if(green == 255) { shiftUpGreen = false; }
    if(green == 230) { shiftUpGreen = true;  } 
    red = 255;
  } else { //not day
    if (red >= 200) { shiftUpRed = false;}  //shift red
    if (red <= 120) {shiftUpRed = true;}
    if (green == 245) { shiftUpGreen = false;} //shift green
    if (green <= 224) { shiftUpGreen = true;}
    
    blue = 255;
  }
  if (shiftUpGreen == false) {
    delay(random(10, 30));
    green--;
  } else {
    delay(random(10, 30));
    green++;
  }
  if (shiftUpRed == false) {
    delay(random(10, 30));
    red--;
  } else {
    delay(random(10, 30));
    red++;
  }  
  analogWrite(redLedPin, red);
  analogWrite(greenLedPin, green);
  analogWrite(blueLedPin, blue);
  
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

