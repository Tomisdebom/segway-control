//Get via Wire.h
int getData(int Address, int Registry){
  Wire.beginTransmission(Address);
  Wire.write(Registry);
  Wire.endTransmission();
  Wire.requestFrom(Address, 1);
  while(!Wire.available());
  int Data = Wire.read();
  return(Data);
}

//Send via Wire.h
void setData(int Address, int Registry, int Value){
  Wire.beginTransmission(Address);
  Wire.write(Registry);
  Wire.write(Value);
  Wire.endTransmission();
}

void setupMotorStop(){
    // SET ACCELERATION AND DIRECTION VALUE TO ZERO AND STOP
  setData(md03_Address_1, md03_Accel, ACCEL);
  delay(10);
  setData(md03_Address_1, md03_Command, STOP);
  delay(10);
  setData(md03_Address_1, md03_Speed, STOP);
  delay(30);
  // SET ACCELERATION AND DIRECTION VALUE TO ZERO AND STOP
  setData(md03_Address_2, md03_Accel, ACCEL);
  delay(10);
  setData(md03_Address_2, md03_Command, STOP);
  delay(10);
  setData(md03_Address_2, md03_Speed, STOP);
  delay(30);
}
