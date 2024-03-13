/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  
  //if((millis()-timer)>10){ // print data every 10ms
  //Serial.print(2);
  //Serial.print(", ");
  //Serial.print(-0.5);
  //Serial.print(", ");

	//Serial.print("X : ");
	//Serial.print(mpu.getAngleX());
  //Serial.println(mpu.getAccX());
	//Serial.print("\tY : ");
	//Serial.print(mpu.getAngleY());
  //Serial.print(mpu.getAccY());
	//Serial.print("\tZ : ");
	//Serial.println(mpu.getAngleZ());
  //Serial.print(mpu.getAccZ());
	//timer = millis();  
  //}

  if (mpu.getAccX() < -1.5){
    Serial.print("Attack angle : ");
    Serial.println(mpu.getAngleY());
    Serial.print("Face Angle : ");
    Serial.println(mpu.getAngleZ());
    return;
  }
}
