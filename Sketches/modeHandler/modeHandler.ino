int mode = 0;
// 0 - 5
// 0 = Sunny
// 1 = Cloudy
// 2 = Misty/Dark Storm (no rain)
// 3 = Light Rain
// 4 = Rain
// 5 = Heavy Rain/Thunder + Lightning

void setup() {
  Serial.setup(9600);
}

void loop() {
  // Get weather from API (webserver PHP file)
  // Not sure how to do that yet though...
}
