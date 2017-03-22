
//just iridium function
void IridiumBegin(char outBuffer[]) {
  
  Serial.println("Beginning to talk to the RockBLOCK...");
  //ssIridium.listen();
  if (isbd.begin() == ISBD_SUCCESS)
  {
    Serial.print("Transmitting message: ");
    Serial.println(outBuffer);
    isbd.sendSBDText(outBuffer);
  }
}



