//GPS function for sat
void getGPSData() {
  
  bool fixFound = false;
  unsigned long loopStartTime = millis();

  // Step 1: Reset TinyGPS++ and begin listening to the GPS
  Serial.println("Beginning to listen for GPS traffic...");
  tinygps = TinyGPSPlus();

  // Step 2: Look for GPS signal for up to 7 minutes
  for (unsigned long now = millis(); !fixFound && millis() - now < 7UL * 60UL * 1000UL;)
    if (Serial3.available())
    {
      tinygps.encode(Serial3.read());
      fixFound = tinygps.location.isValid() && tinygps.date.isValid() &&
        tinygps.time.isValid() && tinygps.altitude.isValid();
    }
    Serial.println(fixFound ? F("A GPS fix was found!") : F("No GPS fix was found."));

//declare the buffer
    char outBuffer[60]; // Always try to keep message short
    if (fixFound)
    {
      sprintf(outBuffer, "%d%02d%02d%02d%02d%02d,",
        tinygps.date.year(), tinygps.date.month(), tinygps.date.day(),
        tinygps.time.hour(), tinygps.time.minute(), tinygps.time.second());
      int len = strlen(outBuffer);
      PString str(outBuffer, sizeof(outBuffer) - len);
      str.print(tinygps.location.lat(), 6);
      str.print(",");
      str.print(tinygps.location.lng(), 6);
      str.print(",");
      str.print(tinygps.altitude.meters());
      str.print(",");
      str.print(tinygps.speed.knots(), 1);
      str.print(",");
      str.print(tinygps.course.value() / 100);

      //saveToCSV(tinygps);
    }
    else
    {
      sprintf(outBuffer, "No GPS fix found!");
    }

     Serial.println(outBuffer);

}

