#include "SoftwareSerial.h"

SoftwareSerial BTserial(10,11); // RX | TX

int sensorPin = A0;
int sensorValue = 0;
int flag = 0;

void setup() {

  Serial.begin(9600);
  BTserial.begin(9600); }

void loop() {

//  sensorValue = analogRead(sensorPin);

//IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;

//(every Value has to be seperated through a comma (',') and the message has to

//end with a semikolon (';'))
//
//  BTserial.print("1234");
//  BTserial.print(",");
//  BTserial.print("1234.0");
//  BTserial.print(",");
//  BTserial.print("1234 hPa");
//  BTserial.print(",");
//  BTserial.print("500 ml/s");
//  BTserial.print(",");
//  if (flag == 0){
//    BTserial.print(analogRead(A4));
//    BTserial.print(",");
//    flag = 1;
//  }
//  else if (flag == 1){
//    BTserial.print("0");
//    BTserial.print(",");
//    flag = 0;
//  }
//  BTserial.print(";");
//  BTserial.print("Hello my name is Amy");
//  BTserial.print(";");
  BTserial.println("Apple");
  delay(2000);
  BTserial.println("Water");
  delay(2000);

}
