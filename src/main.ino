#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_NeoPixel.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int right = 2;
int left = 3;
int confirm = 4; 
int menu = 1;

int relay1 = 12;
int relay2 = 11;
int relay3 = 10;
int relay4 = 9;
int relay5 = 8;
int relay6 = 7;
int relay7 = 6;
int relay8 = 5;

int rtime = 150;
int cl = 606;

#define LED_PIN    6
#define LED_COUNT 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  for(int x = 0; x<LED_COUNT; x++) {
    strip.setPixelColor(x,0,255,0); // Set pixel 'c' to value 'color'
  }
  strip.show();
  pinMode(right, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(confirm, INPUT_PULLUP);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);

  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 24);
  display.println("< Choose >");
  display.display();
  delay(10); 

}
void clean(){
  digitalWrite(relay1, 1);
  delay(100);
  digitalWrite(relay2, 1);
  delay(100);
  digitalWrite(relay3, 1);
  delay(5000);
  digitalWrite(relay1, 0);
  delay(100);
  digitalWrite(relay2, 0);
  delay(100);
  digitalWrite(relay3, 0);
  delay(100);

  digitalWrite(relay4, 1);
  delay(100);
  digitalWrite(relay5, 1);
  delay(100);
  digitalWrite(relay6, 1);
  delay(5000);
  digitalWrite(relay4, 0);
  delay(100);
  digitalWrite(relay5, 0);
  delay(100);
  digitalWrite(relay6, 0);

  digitalWrite(relay7, 1);
  delay(100);
  digitalWrite(relay8, 1);
  delay(5000);
  digitalWrite(relay8, 0);
  delay(100);
  digitalWrite(relay7, 0);
  delay(100);
}

void flush(){
  digitalWrite(relay1, 1);
  delay(100);
  digitalWrite(relay2, 1);
  delay(100);
  digitalWrite(relay3, 1);
  delay(3000);
  digitalWrite(relay1, 0);
  delay(100);
  digitalWrite(relay2, 0);
  delay(100);
  digitalWrite(relay3, 0);
  delay(100);

  digitalWrite(relay4, 1);
  delay(100);
  digitalWrite(relay5, 1);
  delay(100);
  digitalWrite(relay6, 1);
  delay(3000);
  digitalWrite(relay4, 0);
  delay(100);
  digitalWrite(relay5, 0);
  delay(100);
  digitalWrite(relay6, 0);

  digitalWrite(relay7, 1);
  delay(100);
  digitalWrite(relay8, 1);
  delay(3000);
  digitalWrite(relay8, 0);
  delay(100);
  digitalWrite(relay7, 0);
  delay(100);
}

void makeDrink(int num){
  display.clearDisplay();
  display.println("One moment");
  display.display();
  switch(num){

    case 1: // Rom cola
    red();
    digitalWrite(relay1, 1);
    digitalWrite(relay2, 1);
    delay(cl*12);
    digitalWrite(relay1, 0);
    delay(cl*12);
    digitalWrite(relay2, 0);
    green();

    break;

    case 2: // Daiquiri
    red();
    digitalWrite(relay2, 1);
    digitalWrite(relay3, 1);
    delay(cl*12);
    digitalWrite(relay2, 0);
    delay(cl*8);
    digitalWrite(relay3, 0);
    green();
    break;

    case 3: // 8 shot
    red();
    digitalWrite(relay1, 1);
    delay(cl*8);
    digitalWrite(relay1, 0);
    green();

    break;

    case 4: // Gin and tonic
    red();
    digitalWrite(relay3, 1);
    digitalWrite(relay4, 1);
    delay(6*cl);
    digitalWrite(relay3, 0);
    delay(12*cl);
    digitalWrite(relay4, 0);
    green();
    break;

    case 5: // Flushing
    red();

    display.clearDisplay();
    display.setCursor(5, 24);
    display.println("Flushing..");
    display.display();
    flush();
    green();
    break;

    case 6: //clean mode
    red();
    display.clearDisplay();
    display.setCursor(5, 24);
    display.println("Cleaning..");
    display.display();
    clean();    
    green();
    break;

    default:

    break;
    }
}
void loop() {
  if(digitalRead(confirm) == 0){
    makeDrink(menu);
  }
  if(digitalRead(right) == 0){
      if(menu == 6){
        menu = 1;
      }
      else{
        menu += 1;
      }
    Serial.print(menu);
  }

  if(digitalRead(left) == 0){
      if(menu == 1){
        menu = 6;
      }
      else{
        menu -= 1;
      }
    Serial.print(menu);
  }
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30, 14);
  switch(menu) {
    case 1:
      display.clearDisplay();
      display.println("R & C");
      display.display();
      delay(rtime);

      // statements
      break;
    case 2:
      display.clearDisplay();
      display.println("Daiquiri");
      display.display();
      delay(rtime);
      // statements
      break;
    
    case 3:
      display.clearDisplay();
      display.println("Rom shot");
      display.display();
      delay(rtime);
      // statements
      break;

    case 4:
      display.clearDisplay();
      display.println("GT");
      display.display();
      delay(rtime);
      // statements
      break;

    case 5:
      display.clearDisplay();
      display.println("Flush");
      display.display();
      delay(rtime);
      // statements
      break;

    case 6:
      display.clearDisplay();
      display.println("Clean");
      display.display();
      delay(rtime);
      // statements
      break;  
    default:
    menu = 4;
      // statements
      break;
  }
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}


void red() {
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();

}
void green() {
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();

}
void blue() {
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  strip.show();

}
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}