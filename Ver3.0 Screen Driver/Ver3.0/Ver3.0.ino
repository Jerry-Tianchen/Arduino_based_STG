#include <gamma.h>
#include <RGBmatrixPanel.h>

#define CLK  11   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);


int8_t X; 
uint8_t Y;
uint8_t SizeX;
uint8_t SizeY;
uint16_t Col = 0;
uint8_t Type;
uint8_t ID;
uint8_t Start;


void setup(){
  Serial.begin(74880);
  matrix.begin();
  delay(1000);
  
  for (int i = 0; i <40; i++){
      matrix.drawLine(0,i,31,i,63488);
      matrix.drawLine(0,i-4,31,i-4,31);
      matrix.drawLine(0,i-8,31,i-8,2016);
      delay(20);
      matrix.drawLine(0,i,31,i,0);
      matrix.drawLine(0,i-4,31,i-4,0);
      matrix.drawLine(0,i-8,31,i-8,0);
    }

   matrix.fillScreen(0);
   delay(1000);
//////////////////////////////////////Start Up Screen
  while (Serial.available()==0){
    matrix.drawLine(31,29,30,29,65000);
    delay(500);
    matrix.drawLine(31,29,30,29,0);
    delay(500);
    }   
}
//////////////////////////////////////
void loop(){

  
ID = 0;
if (Serial.available()>0){
  ID = Serial.read();
    if (ID == 254){
      while (Serial.available()<7){
        delayMicroseconds(2);
      }
         X = Serial.read();
         Y = Serial.read();
         SizeX = Serial.read();
         SizeY = Serial.read();
         Col = Serial.read();
         Col = Col*(256) + Serial.read();
         Type = Serial.read();

       if (Type == 0){
         matrix.drawPixel(X,Y,Col);
       }
       if (Type == 1){
         matrix.drawCircle(X,Y,SizeX,Col);
       }
       if (Type == 2){  
       matrix.drawRect(X,Y,SizeX,SizeY,Col);
        }
       if (Type == 3){  
       matrix.drawLine(X,Y,SizeX,SizeY,Col);
        }
       if (Type == 4){  
       matrix.fillScreen(Col);
        }
       if(Type == 5){
       matrix.fillRect(X,Y,SizeX,SizeY,Col);
        }
    }
  }
}
