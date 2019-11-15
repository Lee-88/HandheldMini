#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/**************************************************************************
http://www.boldnobold.com/handheld
 **************************************************************************/
#define Scr_Wth 128 // OLED display width, in pixels
#define Scr_Ht 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(Scr_Wth, Scr_Ht, &Wire, OLED_RESET);

//Global Variable List------------------------------
int iB = 0; //serial input data store
int GameLevel = 1;
int BtnA = 2;
int BtnB = 3;
int BtnC = 5;
int buttonState = 0;         
int buttonState2 = 0;
int buttonState3 = 0;
int testa = 0;
int testb = 0;
int testc = 0;
#define COL SSD1306_WHITE
//-----------
//rect
int Rx0 = -10, Ry0 = 1, Wt=25,Ht=3;
//-----------
//line
int Lx0 = 64, Ly0 = 32, Lx1 = 50, Ly1 = 27;
//-----------
//pixel
int Px0 = Lx1-4, Py0 = Ly1-2;
//-----------
//circle
int Cx0 = 64, Cy0 = 38, Cr0 = 12;
//-----------
//anticircle

int AnCx0 = 64, AnCy0 = 32, AnCr0 = 14;
//-----------
//text
//HELD
//--------------------------------------------------
void setup() {
  pinMode(BtnA, INPUT);
  pinMode(BtnB, INPUT);
  pinMode(BtnC, INPUT);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {Serial.println(F("SSD1306 allocation failed")); for(;;);}//looks for correct display, needed.
  display.clearDisplay();// Clear the buffer
  display.display();
  delay(2000);
}

void loop() {
  buttonState = digitalRead(BtnA);
  buttonState2 = digitalRead(BtnB);
  buttonState3 = digitalRead(BtnC);
  if (buttonState == HIGH) {
    // turn LED on:
    testa = 1;
  } else {
    // turn LED off:
    testa = 0;
  }
  
  if (buttonState2 == HIGH) {
    // turn LED on:
    testb = 1;
  } else {
    // turn LED off:
    testb = 0;
  }
  
  if (buttonState3 == HIGH) {
    // turn LED on:
    testc = 1;
  } else {
    // turn LED off:
    testc = 0; 
  }
  drawGame();
  if (Rx0 < 140){Rx0 = Rx0 + GameLevel;}
  else {Rx0 = 0;}
  // send data only when you receive data:
  if (Serial.available() > 0) {
  // read the incoming byte:
  iB = Serial.read();Serial.print("iB: ");Serial.println(iB);
  }
          
if (testa == 1){a();Serial.print("button A\n");}
else if (testb == 1){d();Serial.print("button B\n");}
else if (testc == 1){s();Serial.print("button C\n");}
          
          //Serial Inputs To Run Functions, For debugging mostly. Will be removed after button implamentation. iB global is linked.
          if (iB == 61){}//=
          else if (iB == 97){a();}//a
          else if (iB == 115){s();}//s
          else if (iB == 100){d();}//d
          else if (iB == 119){w();}//w
          else if (iB == 113){w();}//q
          delay(100);
}

void drawGame()
{
  display.clearDisplay();
  drawGun();
  drawPlane();
  drawBullet();
  drawText();drawText2();
  display.display();
}

void drawGun(void) {display.drawLine(Lx0,Ly0,Lx1,Ly1,COL);display.drawCircle(Cx0,Cy0,Cr0,COL);}
void drawPlane(void) {display.drawRect(Rx0,Ry0,Wt,Ht,COL);}
void drawBullet(void) {display.drawPixel(Px0,Py0,COL);}
void drawText(void) {
  display.setTextSize(0.5);             // Normal 1:1 pixel scale
  display.setTextColor(COL);        // Draw white text
  display.setCursor(1,25);             
  display.println(F("LvL: "));
}
void drawText2(void) {
  display.setTextSize(0.5);             // Normal 1:1 pixel scale
  display.setTextColor(COL);        // Draw white text
  display.setCursor(25,25);             
  display.println(GameLevel);
  
}
void a(void) {if(Lx1 > 15 && Ly1 < 30 && Lx1 < 81){if(Lx1>64){Lx1 = Lx1-3;Ly1=Ly1-1;}else{Lx1 = Lx1-3;Ly1=Ly1+1;}}Serial.print(Lx1);Serial.println(Ly1);Px0 = Lx1-4, Py0 = Ly1-2;}
void s(void) {while(Py0 >1){Py0 = Py0-1;drawGame();}Px0 = Lx1-4, Py0 = Ly1-2;if(Px0>Rx0 && Px0 < Rx0+Wt){Serial.print("HIT\n");GameLevel=GameLevel+1;Rx0=-40;}else{Serial.print("MISS\n");}}
void d(void) {if(Lx1 > 15 && Ly1 < 31 && Lx1 < 80){if(Lx1>64){Lx1 = Lx1+3;Ly1=Ly1+1;}else{Lx1 = Lx1+3;Ly1=Ly1-1;}}Serial.print(Lx1);Serial.println(Ly1);Px0 = Lx1-4, Py0 = Ly1-2;}
void w(void) {}
void q() {}
void e() {}
