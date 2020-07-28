//INCLUDE LIBRARIES
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <HX711.h>
#include <Filters.h>

//MOTOR DEFINITIONS
#define md03_Address_1 0x58 // ADRRESS FOR MD03 1
#define md03_Address_2 0x59 // ADRRESS FOR MD03 2
#define md03_Command 0x00   // 0 FOR STOP, 1 FORWARDS, 2 BACKWARDS
#define md03_Speed 0x02     // 0-255 (0x00 - 0xFF)
#define md03_Accel 0x03     // 0-255 (0x00 - 0xFF)
#define md03_Temp 0x04      // TEMP REG
#define md03_Software 0x07  // SOFTWARE REG
#define ACCEL 10            // ACCELERATION VALUE
#define STOP 0
#define FORWARDS 1
#define BACKWARDS 2

//SENSOR CONFIGURATIONS
Adafruit_BNO055 bno = Adafruit_BNO055();
HX711 scale(6, 7); 
float calibration_factor = 105; //load cell
float units;
float TARGET_ANGLE;

//LED CONFIGURATIONS
int ledlinks = 4;
int ledrechts = 5;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

//SETUP
void setup(void) {

  Serial.begin(9600);

  //I2C INITIALISATION
  Wire.begin();

  //LED INITIALISATION
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setColor(0, 0, 255); 

  //LOAD-CELL CALIBRATION
  scale.tare();
  long zero_factor = scale.read_average();  
  scale.set_scale(calibration_factor);


  //IMU SETUP
  if (!bno.begin()) {
    while (1);
  }
  delay(2);
  bno.setExtCrystalUse(true);

  //MOTOR SETUP
  setupMotorStop();
  delay(100);

  //TARGET ANGLE CALCULATION
  TARGET_ANGLE = calibrateSetpoint();
}

void loop() {

  //STATUS LED TO GREEN
  setColor(0, 255, 0);

  //CALCULATE ANGLE ERROR FROM THE READANGLES FUNCTION
  float angle_error = readAngles(); 

  //READS OUT LOAD-CELL FOR STEERING
  units = scale.get_units(), 10;
  if (units > -500 && units < 500) {
    units = 0;
  }
  units = map(units, -5000, 5000, -30, 30);


  //SETS POWER TO THE MOTORCONTROLLERS DEPENDING ON THE PID FUNCTION
  if (PID() < 0) {
    setData(md03_Address_1, md03_Command, BACKWARDS);
    setData(md03_Address_2, md03_Command, BACKWARDS);
    delay(10);
    setData(md03_Address_1, md03_Speed, (abs(PID())));
    setData(md03_Address_2, md03_Speed, (abs(PID())));
  }
  else {
    setData(md03_Address_1, md03_Command, FORWARDS);
    setData(md03_Address_2, md03_Command, FORWARDS);
    delay(10);
    setData(md03_Address_1, md03_Speed, (PID() + (units))); 
    setData(md03_Address_2, md03_Speed, (PID() - (units)));

  }
}



