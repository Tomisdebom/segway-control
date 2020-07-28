
float last_error;
float integrated_error = 0;
float pTerm;
float iTerm;
float dTerm;
float time = 0;
float last_time = 0;
int GUARD_GAIN = 10;

int PID() {
  
  float Kp = 10.5; 
  //float Ki = 0.1;
  //float Kd = 100;
  float K = 1;

  time = millis();
  float delta_time = time - last_time;
  float angle_error = readAngles();
  integrated_error = integrated_error + (angle_error * delta_time);

  // PROPORTIONAL
  pTerm = Kp * angle_error;

  // INTEGRATIONAL
  // iTerm = Ki * constrain(integrated_error, -GUARD_GAIN, GUARD_GAIN);         

  // DIFFERENTIAL
  // dTerm = Kd * (angle_error - last_error)/delta_time;                                 

  last_error = angle_error;
  last_time = time;

  float total_power = constrain(K * (pTerm + iTerm + dTerm), -210, 210);
  return total_power;                           

}
