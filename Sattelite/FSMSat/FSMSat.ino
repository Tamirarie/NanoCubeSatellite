#include <FiniteStateMachine.h>

const byte NUMBER_OF_STATES = 10; //how many states are we cycling through?

//initialize states
State Regular = State(&RegularMode);
State Sleep = State(&SleepMode);
State Error = State(&ErrorMode);
State Reset = State(&ResetMode);
State Transmit = State(&TransMode);
State Laser = State(&LaserMode);
State Photo = State(&PhotoMode);

//Battery states
State FullBatt = State(&FullMode);
State ChargeBatt = State(&ChargeMode);
State LowBatt = State(&LowMode);

FSM SatelliteStateMachine = FSM(Regular); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {

  ///User Want to change State
  if(Serial.available()>0){
    String input = Serial.readString();
    if(input=="tamir")Serial.print("tamir");
    
  }

  //Machine Want to change State (Low Battery,Etc...) 
  
}


//utility functions
void RegularMode(){}
void SleepMode(){}
void ErrorMode(){}
void ResetMode(){}
void TransMode(){}
void LaserMode(){}
void PhotoMode(){}
void FullMode(){}
void ChargeMode(){}
void LowMode(){}

//end utility functions
