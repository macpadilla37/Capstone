const int pinLaser1 = 2; // output signal pin of laser module/laser pointer 1 (closest to the starting ball position)
const int pinLaser2 = 3; // output signal pin of laser module/laser pointer 2 (farthest away)
const int pinReceiver1 = 5; // input signal pin of receiver/detector 1 (the used module does only return a digital state)
const int pinReceiver2 = 6; // input signal pin of receiver/detector 2 (the used module does only return a digital state)

unsigned long startTime = 0;
unsigned long endTime = 0;
float elapsedTime = 0;
double friction = 0;
double velo = 0;
double distance = 0;

bool measurementDone = false;

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;


void setup() {
  pinMode(pinLaser1, OUTPUT); // set laser 1 pin to output mode
  pinMode(pinLaser2, OUTPUT); // set laser 2 pin to output mode
  pinMode(pinReceiver1, INPUT); // set laser 1 pin to output mode
  pinMode(pinReceiver2, INPUT); // set laser 2 pin to output mode
  digitalWrite(pinLaser1, HIGH); // emit red laser 1
  digitalWrite(pinLaser2, HIGH); // emit red laser 2
  Serial.begin(9600); // Setup serial connection for print out to console
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

  if (mpu.getAccX() < -1.5){
    Serial.print("Attack angle : ");
    Serial.println(mpu.getAngleY());
    Serial.print("Face Angle : ");
    Serial.println(mpu.getAngleZ());
    return;
  }

  if (!measurementDone) {
    int value1 = digitalRead(pinReceiver1); // receiver/detector send either LOW or HIGH (no analog values!)
    int value2 = digitalRead(pinReceiver2); 
  //Serial.println(value2);// receiver/detector send either LOW or HIGH (no analog values!)

  if (value1 == LOW && value2 == HIGH) {
    startTime = millis();
  }

  if (value1 == HIGH && value2 == LOW) {
    endTime = millis();
    elapsedTime = endTime - startTime;
    Serial.print("###############################\n");
    Serial.print(elapsedTime);
    Serial.print(" ms\n");
    friction = 0.983/(8);
    velo = 4/((elapsedTime/1000)*12);
    Serial.print(velo,6);
    Serial.print(" f/s\n");
    distance = (pow(velo,2))/(2*friction*32.2)+0.5;
    Serial.print(distance);
    Serial.print(" feet\n");
    Serial.print("###############################");
    measurementDone = true;
   }
  }

}
