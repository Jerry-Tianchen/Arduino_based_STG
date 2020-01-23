        // To use this library, initial the Serial to 9600.
#define BotUp 2
#define BotRight 3
#define BotDown 4
#define BotLeft 5
//#define BotStart  6
//#define BotEnd  7

#define Stan2x 501
#define Stan2y 515
#define theshold 150      
uint8_t Send2 = 0;// Send2 use the last four bits
int Count = 100;
        
        void setup() {
          Serial.begin(74880);
          pinMode (BotUp,INPUT);
          pinMode (BotRight,INPUT);
          pinMode (BotDown,INPUT);
          pinMode (BotLeft,INPUT);
          //pinMode (BotStart,INPUT);
          //pinMode (BotEnd,INPUT);

          digitalWrite(BotUp, HIGH);
          digitalWrite(BotRight, HIGH);
          digitalWrite(BotDown, HIGH);
          digitalWrite(BotLeft, HIGH);
          //digitalWrite(BotStart, HIGH);
          //digitalWrite(BotEnd, HIGH);
        }
        
        void loop(){
            Send2 = 0;
            Count --;
            int Sx = analogRead(A0);
            int Sy = analogRead(A1);
            Sx = Sx - Stan2x;
            Sy = Sy - Stan2y;
            /*
            Serial.print(Sy);    //Debug OutPut
            Serial.print("  ");
            Serial.print(Sx);
            Serial.print("  ");
            */
            if (Sx > theshold)
                       {
                       if (Sy > theshold){ Send2 =  5;}                           //00000101;             //"+1+1";
                       else if (Sy < (-1)*(theshold)){ Send2 = 7;}           //00000111;             // "+1-1";
                       else{ Send2 = 4;}                                                 //00000100;            // "+1+0";
                        }
            else if (Sx < (-1)*(theshold))
                      {
                       if (Sy > theshold){ Send2 =  13;}                         //00001101;              //"-1+1";
                       else if (Sy < (-1)*(theshold)){ Send2 = 15;}        //00001111;               //"-1-1";
                       else{ Send2 =  12;}                                           //00001100;                //"-1+0";
                      }
                       
            else{
                   if (Sy > theshold){ Send2= 1;}                                 //00000001;            //"+0+1";
                   else if (Sy < (-1)*(theshold)){ Send2 = 3;}             //00000011;              //"+0-1";
                   else{ Send2= 0;}                                                    //00000000;              //"+0+0";
                   }

               //Bottom Part
                    if (digitalRead(BotUp) == LOW){Send2 = Send2 + 16;}             //00010000
                    else if (digitalRead(BotRight) == LOW){Send2 = Send2 + 32;}         //00100000
                    else if (digitalRead(BotLeft) == LOW){Send2 = Send2 + 64;}          //01000000
                    else if (digitalRead(BotDown) == LOW){Send2 = Send2 + 128;}          //10000000
                    //if (digitalRead(BotDown) == LOW){Send2 = 6;}        //0110
                    //if (digitalRead(BotStart) == LOW){Send2 = 10;}   //1010
                    //if (digitalRead(BotEnd) == LOW){Send2 = 11;}      //1011

              //Send Part
              if (Count == 0){
                    Serial.write(Send2);
                    //Serial.println(Send2);
                    Count = 100;
              }
          }
