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

void setup() {
  pinMode(pinLaser1, OUTPUT); // set laser 1 pin to output mode
  pinMode(pinLaser2, OUTPUT); // set laser 2 pin to output mode
  pinMode(pinReceiver1, INPUT); // set laser 1 pin to output mode
  pinMode(pinReceiver2, INPUT); // set laser 2 pin to output mode
  digitalWrite(pinLaser1, HIGH); // emit red laser 1
  digitalWrite(pinLaser2, HIGH); // emit red laser 2
  Serial.begin(9600); // Setup serial connection for print out to console
}

void loop() {
if (!measurementDone) {
  int value1 = digitalRead(pinReceiver1); // receiver/detector send either LOW or HIGH (no analog values!)
  int value2 = digitalRead(pinReceiver2); // receiver/detector send either LOW or HIGH (no analog values!)

if (value1 == LOW && value2 == HIGH) {
    startTime = millis();
  }

  if (value1 == HIGH && value2 == LOW) {
    endTime = millis();
    elapsedTime = endTime - startTime;
    Serial.print("###############################\n");
    Serial.print(elapsedTime);
    Serial.print(" ms\n");
    friction = 0.983/(12);
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

//.     Green speeds
//friction = 0.983/(10);
  //Time: 200ms --> /1000 to get 0.2 seconds
  //4in per 0.2 seconds ---> 5 f/s
//seconds = Time/1000;
//velo = 4/seconds;

  //distance = (pow(velo,2))/(2*friction*32.17405);

//Serial.println(distance);
//Serial.println(velo);



  //Serial.println(value1); // send value to console
  //Serial.println(value2); // send value to console