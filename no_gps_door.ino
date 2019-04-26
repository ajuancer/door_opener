/*
Developed by Juan Cerdeño on 4/24/19
Updates will be uploaded (hopefully) to www.github.com/ajuancer/door_opener
The libraries needed are listed below:
  - RCSwitch, to control the 433MHz module.
  - Software Serial, for the communication of the modules.

Obtain more details, schematics and support in the GitHub repostory www.github.com/ajuancer/door_opener

Connection to the Arduino Uno board are the follow:
 Digital pin 10  -->  Data pin of 433MHz send module

*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
}

void loop() {
  mySwitch.switchOn("11101");

}
