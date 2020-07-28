float calibrateSetpoint() {
  float calculated_setpoint = 0;
  float angle_sum = 0;
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  //CALCULATES A SUM OF ALL MEASURED ANGLES
  for (int i = 0; i < 500; i++) {
    angle_sum += euler.y();
  }

  //SHOW USER CALIBRATION IS READY
  analogWrite(3, 0);
  analogWrite(4, 0);
  delay(1000);
  analogWrite(3, 255);
  analogWrite(4, 255);

  //RETURN THE AVERAGE ANGLE MEASURED OVER 500 ITERATIONS
  calculated_setpoint = angle_sum / 500;
  return calculated_setpoint;
  }
