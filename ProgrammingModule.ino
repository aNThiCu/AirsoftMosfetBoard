#include <EEPROM.h>;
//!!!!!!!
//   * =EEPROM address
//!!!!!!!
int   rof=255;               //influences the rpm , *0
bool  activeBreak=true;      //stops the motor after it finishes firing , *1
bool  preCocking=false;      //stops the motor in a cocked position , improves trigger response , *2
bool  binaryTrigger=false;   //fires on both pressing and releasing the trigger , *3
bool  smartTrigger=false;    //first shot's rpm is max speed the next is the ROF's value ,better trigger response , *4

int   firstPos=1;   //Firing mode positions , *5
int   secondPos=2;  //1=Semi-Auto,2=Full-Auto,3=Burst , *6

int   burstAmount=3; //number of bb's shot in a burst,MAX=5, *7

void setup() {
  EEPROM.put(0,rof);
  EEPROM.put(1,activeBreak);
  EEPROM.put(2,preCocking);
  EEPROM.put(3,binaryTrigger);
  EEPROM.put(4,smartTrigger);
  EEPROM.put(5,firstPos);
  EEPROM.put(6,secondPos);
  EEPROM.put(7,burstAmount);
}

void loop() {
}
