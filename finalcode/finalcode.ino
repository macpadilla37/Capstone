#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

const int pinLaser1 = 2;
const int pinLaser2 = 3;
const int pinReceiver1 = 5;
const int pinReceiver2 = 6;

unsigned long startTime = 0;
unsigned long endTime = 0;
float elapsedTime = 0;
double friction = 0;
double velo = 0;
double distance = 0;

bool measurementDone = false;

void setup() {
  Serial.begin(9600);
  
  // MPU6050 setup
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0) { } // Halt if MPU6050 connection failed
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // Calculate offsets for MPU6050
  Serial.println("Done!\n");
  
  // Laser setup
  pinMode(pinLaser1, OUTPUT);
  pinMode(pinLaser2, OUTPUT);
  pinMode(pinReceiver1, INPUT);
  pinMode(pinReceiver2, INPUT);
  digitalWrite(pinLaser1, HIGH); // Turn on laser 1
  digitalWrite(pinLaser2, HIGH); // Turn on laser 2
}

void loop() {
  // MPU6050 readings
  mpu.update();
  if (mpu.getAccX() < -1.5){
    Serial.print("Attack angle : ");
    Serial.println(mpu.getAngleY());
    Serial.print("Face Angle : ");
    Serial.println(mpu.getAngleZ());
    // Removed the return statement to allow the loop to continue
  }

  // Laser timing logic
  if (!measurementDone) {
    int value1 = digitalRead(pinReceiver1);
    int value2 = digitalRead(pinReceiver2);

    if (value1 == LOW && value2 == HIGH) {
      startTime = millis();
    }

    if (value1 == HIGH && value2 == LOW) {
      endTime = millis();
      elapsedTime = endTime - startTime;
      Serial.print("###############################\n");
      Serial.print(elapsedTime);
      Serial.print(" ms\n");
      friction = 0.983 / 8;
      velo = 4 / ((elapsedTime / 1000) * 12);
      Serial.print(velo, 6);
      Serial.print(" f/s\n");
      distance = (pow(velo, 2)) / (2 * friction * 32.2) + 0.5;
      Serial.print(distance);
      Serial.print(" feet\n");
      Serial.print("###############################");
      measurementDone = true;
    }
  }

  delay(10); // Adjust this delay as needed
}
