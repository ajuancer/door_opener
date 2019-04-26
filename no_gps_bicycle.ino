/*
Developed by Juan Cerdeño on 4/24/19
Updates will be uploaded (hopefully) to www.github.com/ajuancer/door_opener
The libraries needed are listed below:
  - RCSwitch, to control the 433MHz module.
  - Software Serial, for the communication of the modules.

Obtain more details, schematics and support in the GitHub repostory www.github.com/ajuancer/door_opener

Connection to the Arduino Uno board are the follow:
 Digital pin 6   -->  Data pin of the 433MHz receiver module
Also, depending on your type of door, choose one of the follow:
 Digital pin 10  -->  Data pin of 433MHz send module
 Digital pin 11  -->  Coonected instead of the button of the cloned door remote

To facilitate the detection of errors, the integrated LED is also active when the door should open.
*/

// LIBRARIES
#include <SoftwareSerial.h>
#include <RCSwitch.h>

// CONSTANTS
RCSwitch sendModule = RCSwitch();
RCSwitch receiveModule = RCSwitch();

// SETUP
void setup() {
  Serial.begin(9600);
  receiveModule.enableReceive(6);
  sendModule.enableTransmit(10);
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

// LOOP
void loop() {

  int received = receiveModule.getReceivedValue();

  if(received = "11101") {
    sendModule.switchOn("11111", "00010");      // For static code
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(11, LOW);                      // For rolling code
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    sendModule.switchOff("11111", "00010");
    digitalWrite(11, LOW);
  }

}
