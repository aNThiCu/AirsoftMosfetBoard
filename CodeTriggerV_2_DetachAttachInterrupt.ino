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
//saved values
int percent;
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
  progMode=digitalRead(triggerPin);
  
  delay(5000);
  if(progMode)
  {
  percent=EEPROM.read(0);
  attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, FALLING);
  }
  else
  attachInterrupt(digitalPinToInterrupt(triggerPin), Settings,FALLING);
}

void Settings(){
  percent=EEPROM.read(0);
  switch(firingMode){
    case 0:
    if(percent<255)
    {
      percent+=5;
      EEPROM.write(0,percent);
    }
    break;

    case 1:
    if(percent>100)
    {
      percent-=5;
      EEPROM.write(0,percent);
    break;
  }
}

void Start_shoot() {
  detachInterrupt(digitalPinToInterrupt(triggerPin));

  brk = 0;
  digitalWrite(BreakOutput, 0);
  analogWrite(NmosOutput, 255);

  attachInterrupt(digitalPinToInterrupt(cyclePin), Cycle_finish, RISING);
}

void Cycle_finish() {

  detachInterrupt(digitalPinToInterrupt(cyclePin));

  if (firingMode == 1) {//Semi-auto
    analogWrite(NmosOutput, 0);
    brk = 1;
  } else if (digitalRead(triggerPin) == 1) {//Full-auto
    analogWrite(NmosOutput, 0);
    brk = 1; 
  }

  attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, FALLING);
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
  noInterrupts();
  if (brk == 1 && digitalRead(BreakOutput)==0)
    Start_break();
  interrupts();

  if(digitalRead(BreakOutput)==1 && millis()-startBreak>=100)
    Stop_break();

  if (analogRead(modePin) > 55) firingMode = 0; else firingMode = 1;  //0=fullauto , 1=semiauto
}