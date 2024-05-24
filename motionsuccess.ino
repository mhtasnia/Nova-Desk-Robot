#include "DFRobot_DF2301Q.h"
#include <U8g2lib.h>
#include <Stepper.h>
#include <AFMotor.h>
#include <Servo.h>
#include <AccelStepper.h>

AF_DCMotor motor1(2);
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; 
const int stepsPerRevolution = 20;  // Change this to fit the number of steps per revolution for your motor

// Initialize the stepper library on pins 8 through 11
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
DFRobot_DF2301Q_I2C asr;

// Initialize the U8g2 library for the SH1106 display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
static const unsigned char image_paint_0_bits[] U8X8_PROGMEM = {0x1f,0x0e,0x04};
static const unsigned char image_paint_1_bits[] U8X8_PROGMEM = {0x01,0x03,0x07,0x03,0x01};

void setup() {
  Serial.begin(115200);
  motor1.setSpeed(200);
   myservo.attach(12); 
  motor1.run(RELEASE);

  while (!asr.begin()) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  asr.setVolume(25);
  asr.setMuteMode(0);
  asr.setWakeTime(20);

  u8g2.begin();
}

void loop() {
  uint8_t CMDID = asr.getCMDID();
  Serial.print("Received CMDID: ");
  Serial.println(CMDID);

  switch (CMDID) {


    case 5: //start walking forward
      draw2();
      delay(200);
      draw3();
      delay(200);
      draw2();
      moveForward();
      servoright();
      break;

    case 7://reverse
      drawnormal1();
      delay(100);
      //moveBackward();
      drawnormal2();
      delay(100);
    
    case 8://left
      drawnormal1();
      servoleft();
      //turnleft();
      delay(100);
      drawnormal2();
      delay(100);

    case 9://right
      drawnormal1();
      servoleft();
      //turnright();
      delay(100);
      drawnormal2();
      delay(100);  
    case 12: //tired
      drawsleep2();
      delay(300);
      drawsleep();
      delay(300);
      drawsleep2();
      delay(300);
      drawsleep();
      break;
    case 14: //right
      draw2();
      moveForward();
      break;
    case 13://dance
      drawsmile1();
      delay(500);
      drawsmile2();
      servoright();
      delay(500);
      drawsmile1();
      delay(500);
      drawsmile2();
      servoleft();
      delay(500);
      drawsmile1();
      delay(500);
      drawsmile2();
      servoright();
      delay(500);
      drawsmile1();
      delay(500);
      drawsmile2();
      break;
    case 11://ready
      draw3();
      servoleft();
      delay(300);
      draw2();
      delay(300);
      servoright();
      //draw6();
      delay(500);
      break;
    case 16://sad
      drawsad1();
      delay(200);
      servoleft();
      drawsad2();
      delay(200);
      drawsad1();
      delay(200);
      break;

    case 15://hello
      drawhello2();
      delay(12);
      drawhello1();
      delay(15);
      drawhello2();
      break;


    default:
      if (CMDID != 0) {
        draw("Unknown command", CMDID);
      }
  }
  delay(300);
}

void draw(const char* message, uint8_t CMDID) {
  u8g2.clearBuffer();                 // Clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a suitable font
  u8g2.drawStr(0, 10, message);       // Write something to the internal memory
  u8g2.setCursor(0, 20);
  u8g2.print("CMDID: ");
  u8g2.print(CMDID);
  u8g2.sendBuffer();                  // Transfer internal memory to the display
}
void draw2() {
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_5x8_tr);
u8g2.drawStr(40, 83, "Convert");
u8g2.drawStr(0, 83, "Code");
u8g2.drawXBM(40, 93, 5, 3, image_paint_0_bits);
u8g2.drawXBM(4, 93, 5, 3, image_paint_0_bits);
u8g2.drawStr(40, 90, "images");
u8g2.drawStr(0, 90, "preview");
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(166, 31, "Fonts");
u8g2.drawXBM(188, 26, 3, 5, image_paint_1_bits);
u8g2.drawBox(19, 17, 20, 16);
u8g2.drawBox(88, 17, 20, 16);
u8g2.drawStr(91, 87, "U8G2");
u8g2.drawFrame(87, 79, 23, 11);
u8g2.drawFilledEllipse(65, 49, 21, 1);
u8g2.drawStr(116, 87, "ADAFRUIT");
u8g2.drawStr(156, 87, "FLIPPER");
u8g2.drawFrame(113, 79, 37, 11);
u8g2.drawFrame(153, 79, 33, 11);
u8g2.sendBuffer();                // Transfer internal memory to the display
}

void draw3() {
 u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_5x8_tr);
u8g2.drawStr(40, 83, "Convert");
u8g2.drawStr(0, 83, "Code");
u8g2.drawXBM(40, 93, 5, 3, image_paint_0_bits);
u8g2.drawXBM(4, 93, 5, 3, image_paint_0_bits);
u8g2.drawStr(40, 90, "images");
u8g2.drawStr(0, 90, "preview");
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(166, 31, "Fonts");
u8g2.drawXBM(188, 26, 3, 5, image_paint_1_bits);
u8g2.drawBox(19, 17, 20, 7);
u8g2.drawBox(88, 17, 20, 7);
u8g2.drawStr(91, 87, "U8G2");
u8g2.drawFrame(87, 79, 23, 11);
u8g2.drawFilledEllipse(65, 49, 21, 1);
u8g2.drawStr(116, 87, "ADAFRUIT");
u8g2.drawStr(156, 87, "FLIPPER");
u8g2.drawFrame(113, 79, 37, 11);
u8g2.drawFrame(153, 79, 33, 11);
u8g2.sendBuffer();
}

void draw4() {
u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_5x8_tr);
u8g2.drawStr(0, 83, "Code");
u8g2.drawStr(40, 83, "Convert");
u8g2.drawXBM(4, 93, 5, 3, image_paint_0_bits);
u8g2.drawXBM(40, 93, 5, 3, image_paint_0_bits);
u8g2.drawStr(0, 90, "preview");
u8g2.drawStr(40, 90, "images");
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(166, 31, "Fonts");
u8g2.drawBox(88, 17, 19, 14);
u8g2.drawBox(19, 17, 21, 14);
u8g2.drawXBM(188, 26, 3, 5, image_paint_1_bits);
u8g2.drawStr(91, 87, "U8G2");
u8g2.drawEllipse(62, 48, 9, 6);
u8g2.drawFrame(87, 79, 23, 11);
u8g2.drawStr(116, 87, "ADAFRUIT");
u8g2.drawStr(156, 87, "FLIPPER");
u8g2.drawFrame(113, 79, 37, 11);
u8g2.drawFrame(153, 79, 33, 11);
u8g2.sendBuffer();
}

void draw5(){
  static const unsigned char image_paint_0_bits[] U8X8_PROGMEM = {0x1f,0x0e,0x04};
static const unsigned char image_paint_1_bits[] U8X8_PROGMEM = {0x01,0x03,0x07,0x03,0x01};
static const unsigned char image_weather_humidity_white_bits[] U8X8_PROGMEM = {0x20,0x00,0x20,0x00,0x30,0x00,0x50,0x00,0x48,0x00,0x88,0x00,0x04,0x01,0x04,0x01,0x82,0x02,0x02,0x03,0x01,0x05,0x01,0x04,0x02,0x02,0x02,0x02,0x0c,0x01,0xf0,0x00};
u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_5x8_tr);
u8g2.drawStr(0, 83, "Code");
u8g2.drawStr(40, 83, "Convert");
u8g2.drawXBM(4, 93, 5, 3, image_paint_0_bits);
u8g2.drawXBM(40, 93, 5, 3, image_paint_0_bits);
u8g2.drawStr(0, 90, "preview");
u8g2.drawStr(40, 90, "images");
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(166, 31, "Fonts");
u8g2.drawBox(85, 15, 22, 12);
u8g2.drawBox(19, 15, 22, 12);
u8g2.drawXBM(188, 26, 3, 5, image_paint_1_bits);
u8g2.drawStr(91, 87, "U8G2");
u8g2.drawFrame(87, 79, 23, 11);
u8g2.drawXBM(36, 29, 11, 16, image_weather_humidity_white_bits);
u8g2.drawPixel(93, 19);
u8g2.drawStr(116, 87, "ADAFRUIT");
u8g2.drawFilledEllipse(64, 51, 20, 1);
u8g2.drawStr(156, 87, "FLIPPER");
u8g2.drawFrame(113, 79, 37, 11);
u8g2.drawFrame(153, 79, 33, 11);
u8g2.sendBuffer();
}

void draw6(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_5x8_tr);
u8g2.drawStr(0, 83, "Code");
u8g2.drawStr(40, 83, "Convert");
u8g2.drawXBM(4, 93, 5, 3, image_paint_0_bits);
u8g2.drawXBM(40, 93, 5, 3, image_paint_0_bits);
u8g2.drawStr(0, 90, "preview");
u8g2.drawStr(40, 90, "images");
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(166, 31, "Fonts");
u8g2.drawXBM(188, 26, 3, 5, image_paint_1_bits);
u8g2.drawStr(91, 87, "U8G2");
u8g2.drawFrame(87, 79, 23, 11);
u8g2.drawLine(17, 14, 33, 20);
u8g2.drawStr(116, 87, "ADAFRUIT");
u8g2.setFont(u8g2_font_t0_15b_tr);
u8g2.drawStr(60, 51, "w");
u8g2.drawLine(31, 21, 18, 25);
u8g2.drawLine(86, 19, 103, 25);
u8g2.setFont(u8g2_font_4x6_tr);
u8g2.drawStr(156, 87, "FLIPPER");
u8g2.drawLine(104, 12, 86, 19);
u8g2.drawFrame(113, 79, 37, 11);
u8g2.drawFrame(153, 79, 33, 11);
u8g2.sendBuffer();
}

void drawsleep(){
u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawLine(41, 45, 84, 45);
u8g2.setFont(u8g2_font_timR14_tr);
u8g2.drawStr(66, 21, "z");
u8g2.drawBox(89, 12, 22, 18);
u8g2.setFont(u8g2_font_timR10_tr);
u8g2.drawStr(76, 11, "z");
u8g2.drawBox(15, 12, 22, 18);
u8g2.drawStr(85, 2, "z");
u8g2.sendBuffer();
}

void drawsleep2(){
 u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawLine(41, 45, 84, 45);
u8g2.setFont(u8g2_font_timR14_tr);
u8g2.drawStr(64, 24, "z");
u8g2.drawBox(89, 12, 22, 11);
u8g2.setFont(u8g2_font_timR10_tr);
u8g2.drawStr(73, 14, "z");
u8g2.drawBox(15, 12, 22, 11);
u8g2.drawStr(81, 6, "z");
u8g2.sendBuffer();
}

void drawsmile1(){
u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawFilledEllipse(63, 53, 22, 2);
u8g2.drawBox(89, 12, 22, 17);
u8g2.drawBox(15, 12, 23, 17);
u8g2.sendBuffer();
}
void drawsmile2(){
u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawFilledEllipse(63, 53, 22, 2);
u8g2.drawBox(78, 47, 7, 5);
u8g2.drawBox(42, 48, 7, 5);
u8g2.drawBox(89, 12, 21, 10);
u8g2.drawBox(16, 12, 22, 9);
u8g2.sendBuffer();
}

void drawsad(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawLine(83, 14, 110, 4);
u8g2.drawLine(84, 14, 109, 24);
u8g2.drawLine(12, 7, 37, 12);
u8g2.drawLine(40, 13, 14, 24);
u8g2.drawFilledEllipse(62, 37, 20, 2);
u8g2.drawBox(43, 39, 6, 4);
u8g2.drawBox(76, 39, 6, 4);
u8g2.sendBuffer();
}

void drawstop(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawLine(83, 14, 110, 4);
u8g2.drawLine(84, 14, 109, 24);
u8g2.drawLine(12, 7, 37, 12);
u8g2.drawLine(40, 13, 14, 24);
u8g2.drawFilledEllipse(62, 37, 20, 2);
u8g2.sendBuffer();
}

void drawsad1(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawBox(82, 10, 34, 21);
u8g2.drawBox(11, 10, 34, 21);
u8g2.drawFilledEllipse(63, 54, 29, 2);
u8g2.drawPixel(84, 55);
u8g2.drawBox(83, 54, 9, 3);
u8g2.drawBox(35, 53, 9, 4);
u8g2.sendBuffer();

}

void drawsad2(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawBox(82, 10, 34, 14);
u8g2.drawBox(11, 10, 33, 13);
u8g2.drawFilledEllipse(63, 54, 29, 2);
u8g2.drawPixel(84, 55);
u8g2.drawBox(83, 55, 9, 3);
u8g2.drawBox(35, 54, 9, 4);
u8g2.sendBuffer();
}
void drawhello1(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_timR24_tr);
u8g2.drawStr(28, 41, "hello!");
u8g2.sendBuffer();
}

void drawhello2(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.setFont(u8g2_font_timR18_tr);
u8g2.drawStr(35, 39, "hello!");
u8g2.sendBuffer();
}

void drawnormal1(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawBox(76, 10, 35, 24);
u8g2.drawBox(12, 10, 35, 24);
u8g2.drawBox(38, 46, 47, 5);
u8g2.sendBuffer();
}

void drawnormal2(){
  u8g2.clearBuffer();
u8g2.setFontMode(1);
u8g2.setBitmapMode(1);
u8g2.drawBox(76, 10, 35, 18);
u8g2.drawBox(13, 10, 34, 18);
u8g2.drawBox(38, 46, 47, 5);
u8g2.sendBuffer();
}
void moveForward() {
  static int stepCount = 0;
  const int totalSteps = 3; // Move forward by 3 steps

  if (stepCount < totalSteps) {
    // Step the motor one step forward
    myStepper.step(1);
    stepCount++;
    Serial.print("steps: ");
    Serial.println(stepCount);
    delay(10); // Adjust delay as necessary for speed control
  } else {
    // Motor movement completed
    Serial.println("Motor movement completed.");
  }
}

void servoright(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

void servoleft(){
   for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
