#include <IridiumSBD.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h> // NMEA parsing: http://arduiniana.org
#include <PString.h> // String buffer formatting: http://arduiniana.org
#include <Adafruit_VC0706.h> ///Camera
#include <SPI.h> 
#include "SdFat.h"
#include <Wire.h>
#include <Adafruit_Sensor.h> //Sensors for 9DOF
#include <Adafruit_BNO055.h> ///9DOF
#include <utility/imumaths.h>
#include <FiniteStateMachine.h>

const byte NUMBER_OF_STATES = 10; //how many states are we cycling through?

#define ROCKBLOCK_SLEEP_PIN 6
#define ROCKBLOCK_BAUD 19200
#define GPS_BAUD 4800
#define CONSOLE_BAUD 115200
#define BNO055_SAMPLERATE_DELAY_MS (5000)

//SoftwareSerial ssIridium(ROCKBLOCK_RX_PIN, ROCKBLOCK_TX_PIN);
//SoftwareSerial ssGPS(GPS_RX_PIN, GPS_TX_PIN);
SoftwareSerial cameraconnection = SoftwareSerial(9, 10);//for RX2 and TX2
IridiumSBD isbd(Serial1, ROCKBLOCK_SLEEP_PIN);
TinyGPSPlus tinygps;
SdFatSdio SD;

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

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void printFloat(double f, int digits = 2);

int led = 13;
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading; 

void setup() {

  Serial.begin(CONSOLE_BAUD);
  delay(1000);
  Serial1.begin(19200);
  delay(1000);
  Serial2.begin(9600);
  delay(1000);
  Serial3.begin(9600);
  delay(1000);

}

void init(){
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  
  // Setup the RockBLOCK
   isbd.attachConsole(Serial); 
   isbd.attachDiags(Serial);
   isbd.begin();
   isbd.setPowerProfile(1);  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}
void loop(){

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
   
  //SnapShot();
  //IridiumBegin();
  //Getphotocell();
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
