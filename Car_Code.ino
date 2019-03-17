// With Wires Forward
// Y=1023 for Forward
// Y=0 for Backwards
// Y=513 for Neutral
// X=0 for Left
// X=1023 for Right
// X=491 for Neutral

#include <Stepper.h>
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
Stepper stepper(STEPS, 3, 5, 4, 6);
int engineButton = 9;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// 0⸮
int forward = 3;
int left = 2;
int right = 1;
int text = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(engineButton, OUTPUT);
  stepper.setSpeed(20);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  
}

void loop() {
//  radio.startListening();
  if (radio.available()) {
//      char text[32] = "";
//      radio.read(&text, sizeof(text)); 

      
    radio.read(&text, sizeof(text));
    Serial.println(text);
      
    if(text == forward){
      digitalWrite(engineButton, HIGH);
    }
    else{
      digitalWrite(engineButton, LOW);
    }
  
    if (text == left){
      stepper.step(-3);
    }
    else {
      stepper.step(0);
    }
  
    if(text == right){
      stepper.step(3);
    }
    else {
      stepper.step(0);
    }
  }
//  radio.stopListening();
}
  /*
  //else if(xPosition >= 419 && xPosition < 950 || xPosition <= 419 && xPosition > 50){
  else if(xPosition > 80 && xPosition < 950){
    stepper.step(0);
  }*/
//  
//  
//  delay(100); // add some delay between reads
//}
