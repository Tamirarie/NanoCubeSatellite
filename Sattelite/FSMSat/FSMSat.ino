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
    String Input = Serial.readString();
    if(Input== "Regular")SatelliteStateMachine.transitionTo(Regular);
    else if(Input== "Sleep")SatelliteStateMachine.transitionTo(Sleep);
    else if(Input=="Error")SatelliteStateMachine.transitionTo(Error);
    else if(Input=="Reset")SatelliteStateMachine.transitionTo(Reset);
    else if(Input=="Trans")SatelliteStateMachine.transitionTo(Transmit);
    else if(Input=="Laser")SatelliteStateMachine.transitionTo(Laser);
    else if(Input=="Photo")SatelliteStateMachine.transitionTo(Photo);
    else if(Input=="FullBat")SatelliteStateMachine.transitionTo(FullBatt);
    else if(Input=="ChargeBat")SatelliteStateMachine.transitionTo(ChargeBatt);
    else if(Input=="LowBat")SatelliteStateMachine.transitionTo(LowBatt);
    
  }
  SatelliteStateMachine.update();
  //Machine Want to change State (Low Battery,Etc...) 
   
}


//utility functions
void RegularMode(){
  Serial.println("regular");
  
  /*Sensors Display*/
  GetEvent();
  DisplayInfo();
  Getphotocell();
  
  /*Capture Gps Data*/  
  //getGPSData();
  
  /*Send Through Iridium*/
  //IridiumSend();
  
  }
void SleepMode(){}
void ErrorMode(){}
void ResetMode(){}
void TransMode(){}
void LaserMode(){}
void PhotoMode(){
  SnapShot();
  }
void FullMode(){}
void ChargeMode(){}
void LowMode(){}

//end utility functions
