//pins
int triggerPin = PIN_PC0;
int cyclePin = PIN_PA1;
int modePin = PIN_PB0;
int NmosOutput = PIN_PA5;
int BreakOutput = PIN_PB5;
//logic
bool mode = 1;
bool shooting = 0;
bool brk = 0;
//timers
unsigned long int startBreak=0;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, INPUT_PULLUP);
  pinMode(cyclePin, INPUT);
  pinMode(modePin, INPUT);
  pinMode(NmosOutput, OUTPUT);
  pinMode(BreakOutput, OUTPUT);
  analogWrite(NmosOutput, 0);
  digitalWrite(BreakOutput, 0);
  attachInterrupt(digitalPinToInterrupt(triggerPin), Start_shoot, FALLING);
  attachInterrupt(digitalPinToInterrupt(cyclePin), Cycle_finish, RISING);
  delay(1000);
}

void Start_shoot() {
  if (shooting == false) {
    brk = 0;
    digitalWrite(BreakOutput, 0);
    analogWrite(NmosOutput, 255);
    shooting = true;
  }
}

void Cycle_finish() {
  if (shooting == true)
  {
    if (mode == 1) {
      analogWrite(NmosOutput, 0);
      shooting = false;
      brk = 1;
    } else if (digitalRead(triggerPin) == 1) {
      analogWrite(NmosOutput, 0);
      shooting = false;
      brk = 1; 
    }
  }
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
  
  if (analogRead(modePin) > 55) mode = 0; else mode = 1;  //0=fullauto , 1=semiauto
}