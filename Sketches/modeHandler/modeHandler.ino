#include <Ethernet.h>
#include <SPI.h>

int mode = 0;

byte server[] = { 76,126,25,74 };

String location = "./ HTTP/1.0";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

char inString[32];
int stringPos = 0;
boolean startRead = false;

void setup(){
  Ethernet.begin(mac);
  Serial.begin(9600);
}

void loop(){
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

  delay(30000); // Five minutes
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
