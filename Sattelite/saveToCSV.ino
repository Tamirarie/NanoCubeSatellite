#define SPACE ','
File myFile;

void saveToCSV(TinyGPSPlus tinygps){
myFile = SD.open("Data.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.csv...");
    myFile.print("Alt");
    myFile.print(SPACE);
    myFile.print("Lon");
    myFile.print(SPACE);
    myFile.print("Lat");
    myFile.print(',');            
    // close the file:
    myFile.println(SPACE);
    myFile.print(tinygps.location.lat(),6);
    myFile.print(SPACE);
    myFile.print(tinygps.location.lat(),6);
    myFile.print(SPACE);
    myFile.print(tinygps.altitude.meters());
    myFile.print(SPACE);
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.CSV");
  }

  // re-open the file for reading:
  myFile = SD.open("Data.csv");
  if (myFile) {
    Serial.println("Data.Csv:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.CSV");
  }

}
