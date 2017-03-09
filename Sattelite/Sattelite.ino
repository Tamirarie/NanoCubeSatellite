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

#define BEACON_INTERVAL 3600 // Time between transmissions
#define ROCKBLOCK_RX_PIN 18
#define ROCKBLOCK_TX_PIN 19
#define ROCKBLOCK_SLEEP_PIN 6
#define ROCKBLOCK_BAUD 19200
#define GPS_RX_PIN 3
#define GPS_TX_PIN 4
#define GPS_BAUD 4800
#define CONSOLE_BAUD 115200
#define BNO055_SAMPLERATE_DELAY_MS (5000)

SoftwareSerial ssIridium(ROCKBLOCK_RX_PIN, ROCKBLOCK_TX_PIN);
SoftwareSerial ssGPS(GPS_RX_PIN, GPS_TX_PIN);
SoftwareSerial cameraconnection = SoftwareSerial(9, 10);//for RX2 and TX2
IridiumSBD isbd(Serial1, ROCKBLOCK_SLEEP_PIN);
TinyGPSPlus tinygps;
SdFatSdio SD;

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

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);

  /* Display some basic information on this sensor */
 /* displaySensorDetails();
   Optional: Display current status 
  displaySensorStatus();
  */

  bno.setExtCrystalUse(true);
  
  // Setup the RockBLOCK
   isbd.attachConsole(Serial); 
   isbd.attachDiags(Serial);
   isbd.begin();
   isbd.setPowerProfile(1);  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.print("Succes!");
}

void loop(){
  // put your main code here, to run repeatedly:
  GetEvent();
  //SnapShot();
  //IridiumBegin();
  Getphotocell();
}
