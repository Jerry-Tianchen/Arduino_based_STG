

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//define color
typedef uint16_t color;

//define player
typedef struct{
    int x;       //x position
    int y;       //y position
    int moveX;   //x movement
    int moveY;   //y movement
    int UP;      //UP bottom
    int LEFT;    //LEFT bottom
    int RIGHT;   //RIGHT bottom
    int DOWN;    //DOWN bottom
    int HP;      
    int HP_LOSE;     
    color mycolor;  
    int BE_UP;      //bottom UP enable  
    int BE_RIGHT;    //bottom RIGHT enable
    int BE_LEFT;     //bottom LEFT enable
    int BE_DOWN;     //bottom DOWN enable
    int heavy_usage;
    int light_usage;
    double thunder_counter;
    int r;                  //thunder position
}player;

//define bomb
typedef struct{
  int x;
  int y;
  int active;
  int counter;
}heavyBomb1;

typedef struct{
  int x;
  int y;
  int active; 
  int counter; 
}heavyBomb2;

typedef struct{
  int x;
  int y;
  int active;
  int counter;
}lightBomb1;

typedef struct{
  int x;
  int y;
  int active;  
  int counter;
}lightBomb2;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//pixel 0
//circle 1
//rec   2
//line 3
//screen 4

void draw (uint8_t T, uint8_t X, uint8_t Y, uint8_t SizeX, uint8_t SizeY, uint16_t Col){
    int delaytime = 200;   //Total Time = delay*8
  
    Serial.write(254);
    Serial.write(X);
    Serial.write(Y);
    Serial.write(SizeX);
    Serial.write(SizeY);
    Serial.write(Col/256);
    Serial.write(Col%256);
    Serial.write(T);
    delayMicroseconds(delaytime);

}
  
void drawArrow(int x, int y,color Col){
   draw(3,x,y+1,x,y-1,Col);
   draw(0,x+1,y,0,0,Col);  
  
}

void reset(){
    draw(4, 0,0,0,0,ColD);
    
}


//Ram Uesage
#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory() {
char top;
#ifdef __arm__
return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
return &top - __brkval;
#else // __arm__
return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//some rubbish and junks

             
