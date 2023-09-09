#include <EEPROM.h>;
//pins
  //input
int triggerPin = PIN_PC0;
int cyclePin = PIN_PA1;
int modePin = PIN_PB0;
  //output
int NmosOutput = PIN_PA5;
int BreakOutput = PIN_PB5;
//logic
bool firingMode = 1;
bool brk = 0;
bool progMode=0;
//values
int shotCount=0;
//saved values
int   rof;
bool  activeBreak;
bool  preCocking;
bool  binaryTrigger;
bool  smartTrigger;
int   firstPos;
int   secondPos;
int   burstAmount;
//timers
unsigned long int startBreak=0;

void setup() {
  //Input Init
  pinMode(triggerPin, INPUT_PULLUP);
  pinMode(cyclePin, INPUT);
  pinMode(modePin, INPUT);
  //Output Init
  pinMode(NmosOutput, OUTPUT);
  pinMode(BreakOutput, OUTPUT);
  //Output Value Init
  analogWrite(NmosOutput, 0);
  digitalWrite(BreakOutput, 0);
  //Saved Values Init
  EEPROM.get(0,rof);
  EEPROM.get(1,activeBreak);
  EEPROM.get(2,preCocking);
  EEPROM.get(3,binaryTrigger);
  EEPROM.get(4,smartTrigger);
  EEPROM.get(5,firstPos);
  EEPROM.get(6,secondPos);
  EEPROM.get(7,burstAmount);
  //Init Finish

  progMode=digitalRead(triggerPin);
  
  delay(5000);
  if(progMode)
  {
  if(binaryTrigger==true)
      attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, CHANGE);
    else
      attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, FALLING);
  }
  else
  attachInterrupt(digitalPinToInterrupt(triggerPin), Settings,FALLING);
}

void Settings(){
  rof=255;
  switch(firingMode){
    case 0:
    if(rof<255)
    {
      rof+=5;
      EEPROM.put(0,rof);
    }
    break;

    case 1:
    if(rof>100)
    {
      rof-=5;
      EEPROM.put(0,rof);
    break;
  }
}

void Start_shoot() {
  detachInterrupt(digitalPinToInterrupt(triggerPin));

  brk = 0;
  digitalWrite(BreakOutput, 0);
  if(smartTrigger==true)
  analogWrite(NmosOutput, 255);
  else
  analogWrite(NmosOutput, rof);

  attachInterrupt(digitalPinToInterrupt(cyclePin), Cycle_finish, RISING);
}

void Cycle_finish() {

  detachInterrupt(digitalPinToInterrupt(cyclePin));

  switch(firingMode){
    
    case 1://semi-auto
    analogWrite(NmosOutput, 0);
    brk = 1; 
    break;

    case 2://full-auto
    if(digitalRead(triggerPin)==1){
      analogWrite(NmosOutput, 0);
      brk = 1;
    }
    else
    analogWrite(NmosOutput,rof);
    break;
    
    case 3://burst
    if(shotCount>=3){
      analogWrite(NmosOutput, 0);
      brk = 1;
    }
    else
    {
    shotCount++;
    analogWrite(NmosOutput,rof);
    }
    break;
  }

  if (firingMode == 1) {//Semi-auto
    analogWrite(NmosOutput, 0);
    brk = 1;
  } else if (digitalRead(triggerPin) == 1) {//Full-auto
    analogWrite(NmosOutput, 0);
    brk = 1; 
  }

  if(binaryTrigger==true)
      attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, CHANGE);
    else
      attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, FALLING);
}

void Check_break()
{
  noInterrupts();
  if (brk == 1 && digitalRead(BreakOutput)==0)
    Start_break();
  interrupts();

  if(digitalRead(BreakOutput)==1 && millis()-startBreak>=100)
    Stop_break();
}

void Start_break()
{
  digitalWrite(BreakOutput, 1);
  startBreak=millis();
}

void Stop_break()
{
  brk=0;
  digitalWrite(BreakOutput,0);
}

void loop() {
  if (activeBreak==true) Check_break();
  if (analogRead(modePin) > 55) firingMode = secondPos; else firingMode = firstPos;  //2=fullauto , 1=semiauto
}