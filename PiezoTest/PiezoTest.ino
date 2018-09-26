#include "Bounce2.h"

const int button = 4;
const int sampleWindow = 50; // sample window width in mS (50 mS = 20Hz)
unsigned int sample0, sample1, piezo1, piezo2;
int mic1, mic2, button_state;
int flag = 0;

// Variables will change:
int button_counter = 0;   // counter for the number of button presses         // current state of the button
int prev_button_state = 0;     // previous state of the button


Bounce bouncer = Bounce(button,10);
 
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  
}
 
 
//void loop() {
//   unsigned long startMillis= millis();  // start of sample window
//   unsigned int p0 = 0;   // peak-to-peak level
//   unsigned int p1 = 0;   // peak-to-peak level
//    
//   unsigned int signalMax0 = 0;
//   unsigned int signalMin0 = 1024;
//   unsigned int signalMax1 = 0;
//   unsigned int signalMin1 = 1024;
// 
//   // collect data for 50 mS
//   while (millis() - startMillis < sampleWindow){
//      
//      piezo0 = analogRead(0);
//      piezo1 = analogRead(1);
//      sample0 = analogRead(4);
//      sample1 = analogRead(5);

//      
//      if (sample0 < 1024){  // toss out spurious readings
//         if (sample0 > signalMax0){
//            signalMax0 = sample0;  // save just the max levels
//         }
//         else if (sample0 < signalMin0){
//            signalMin0 = sample0;  // save just the min levels
//         }
//      }
//      
//      if (sample1 < 1024){  // toss out spurious readings
//         if (sample1 > signalMax1){
//            signalMax1 = sample1;  // save just the max levels
//         }
//         else if (sample1 < signalMin1){
//            signalMin1 = sample1;  // save just the min levels
//         }
//      }
//   }
//   p0 = signalMax0 - signalMin0;  // max - min = peak-peak amplitude
//   p1 = signalMax1 - signalMin1;  // max - min = peak-peak amplitude
   
//   double volts0 = (p0 * 10.0) / 1024;  // convert to volts
//   double volts1 = (p1 * 10.0) / 1024;  // convert to volts

//   double difference = abs(volts0-volts1);
//   
//   Serial.print("First Mic \t");
//   Serial.println(volts0);
//   Serial.print("Second Mic \t");
//   Serial.println(volts1);
//   Serial.print("Difference \t");
//   Serial.println(difference);   
//
//     double piez1 = (piezo0 * 5.0) / 1024;
//     double mic1 = (sample0*5.0) / 1024;
//     Serial.print(mic1);
//     Serial.print(",");
//     Serial.println(mic2);
//   }
//}

void loop(){

      bouncer.update();
      
      int button_state = bouncer.read();
      mic1 = analogRead(A4);
      mic2 = analogRead(A5);
      piezo1 = analogRead(A0);
      piezo2 = analogRead(A1);
      

      // compare the buttonState to its previous state
      if (button_state != prev_button_state) {
        if (button_state == HIGH) {
          for (int i = 0; i < 400; i ++){
            mic1 = analogRead(A0);
            mic2 = analogRead(A1);
            piezo1 = analogRead(A4);
            piezo2 = analogRead(A5);
            Serial.print(mic1);
            Serial.print(",");
            Serial.print(mic2);
            Serial.print(",");
            Serial.print(piezo1);
            Serial.print(",");
            Serial.println(piezo2);
          }
        } 
        else if (button_state == LOW) {
          Serial.println("Off");
        }
//      delay(50);
      }
  
      prev_button_state = button_state;

//      if (button_counter % 2 == 0) {
//        Serial.println("button pressed");
//      } 
//      else {
//        Serial.println("no button press");
//      }



//      CODE FOR SENDING ALL DATA TO PYTHON - TESTING STAGE
 
//      Serial.println(mic1);
//      Serial.print(",");
//      Serial.println(mic2);



/*
 *    CODE FOR THE SWALLOWING DETECTION 
  
    if (piezo1 < 10){
      Serial.println(piezo1);
      delay(10);
    }
    else{
      Serial.println(0);
//      Serial.print(",");
//      Serial.println(piezo2);
      delay(10);
    }
    
*/

} 
