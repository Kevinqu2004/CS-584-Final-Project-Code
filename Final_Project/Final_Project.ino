#include <Servo.h>


Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo



int val;    // variable to read the value from the analog pin
int sensorValue1 = 0;  // value read from servo 1
int outputValue1 = 0;
int sensorValue2 = 0;  // value read from servo 1
int outputValue2 = 0;  
int avg1[200];
int avg2[200];

int potpin = A2;  // analog pin used to connect the potentiometer
int prevPotPin = 0;

void setup() {

  myservo1.attach(4);  // attaches the servo on pin 4 to the servo object
  myservo2.attach(5);  // attaches the servo on pin 5 to the servo object
  Serial.begin(9600);
  val = 90;
}


void loop() {

  myservo1.write(val);                  // sets the servo position according to the scaled value
  myservo2.write(val);                  // sets the servo position according to the scaled value

  // read the analog in value:
  sensorValue1 = analogRead(A0);
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);

  // read the analog in value:
  sensorValue2 = analogRead(A1);
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);

  // debug test prints
  //Serial.print("sensor1 = ");
  Serial.print(outputValue1);
  //Serial.print("\t output1 = ");
  //Serial.println(outputValue1);

  Serial.print(" ");

  //Serial.print("senso2 = ");
  Serial.print(outputValue2);
  //Serial.print("\t output2 = ");
  //Serial.println(outputValue2);

  Serial.print(" ");

  Serial.print(abs(outputValue1) - abs(outputValue2));

  Serial.print(" ");

  for(int i = 0; i < 200 - 1; i++){
    avg1[i + 1] = avg1[i];
    avg2[i + 1] = avg2[i];
  }
  avg1[0] = outputValue1;
  avg2[0] = outputValue2;

  int sum1 = 0;
  int sum2 = 0;

  for(int i = 0; i < 200; i++){
    sum1 += avg1[i];
    sum2 += avg2[i];
  }

  sum1 = sum1 / 200;
  sum2 = sum2 / 200;

  Serial.print(sum1);
  Serial.print(" ");
  Serial.print(sum2);
  Serial.println();

  /*if(abs(outputValue1) >= 15){
    val += 5;
  }

  if(abs(outputValue2) >= 15){
    val -= 5;
  }*/

  // move servos if the difference in current draw is big enough
  if(abs(abs(outputValue1) * 10 - abs(outputValue2) * 8) <= 20){
    val += (abs(outputValue1) * 10 - abs(outputValue2) * 8); // outputs are multiplied by tuning/scaling variables for optimal movement/sensing
  }
  

  if(abs(prevPotPin - map(analogRead(potpin), 0, 1023, 0, 180)) >= 10){
    val = map(analogRead(potpin), 0, 1023, 0, 180);            // reads the value of the potentiometer (value between 0 and 1023)

    prevPotPin = map(analogRead(potpin), 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  }

  // wait a few milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:

  delay(15);                           // waits for the servo to get to pos

}