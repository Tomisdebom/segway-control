

float readAngles() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);  
  float angle_difference = euler.y() - TARGET_ANGLE;
  return angle_difference;
}

 /*if (euler.y() > 10) {
    euler.y() = 10;
  }
  if (euler.y() < -16) {
    euler.y() = -16;
  }                      

                   
  if ((euler.y() - last_angle) < -12){     //0 - 13 = -13
  euler.y() = 13;                                       
  }
if ((euler.y() - last_angle) > 12){        //0 --13 = 13
  euler.y() = -13;                        
  }
  
  last_angle = euler.y();*/

  
