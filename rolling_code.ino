/*
Developed by Juan Cerdeño on 4/24/19
Updates will be uploaded (hopefully) to www.github.com/ajuancer/door_opener
The libraries needed are listed below:
  - TinyGPS, for being able to control de module.
  - Software Serial, for the communication of the modules.

Obtain more details, schematics and support in the GitHub repostory www.github.com/ajuancer/door_opener

Connection to the Arduino Uno board are the follow:
 Digital pin 3   -->  RX pin of GPS module
 Digital pin 4   -->  TX pin of GPS module
 Digital pin 10  -->  Coonected instead of the button of the cloned door remote

To facilitate the detection of errors, the integrated LED is also active when the door should open.
*/

// LIBRARIES
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// CONSTANTS
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);
static const double DOOR_LAT = 00.000000, DOOR_LON = 00.000000;   // Location of the door

// SETUP
void setup() {
  Serial.begin(115200);
// If you find an error with the GPS moule,
// probably you have selected the wrong baud rate
  ss.begin(9600);                                                // Baud of GPS
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);

}

// LOOP
void loop() {

  unsigned long distanceMToDoor =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      DOOR_LAT,
      DOOR_LON);
  printInt(distanceMToDoor, gps.location.isValid(), 9);

  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  if(distanceMToDoor < 20.00000) {                                 // Put the distance in meters
    digitalWrite(10, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(10, LOW);
  }

}


// SMART DELAY
static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

// PRINT FLOAT
static void printFloat(float val, bool valid, int len, int prec) {
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

// PRINT LINE
static void printInt(unsigned long val, bool valid, int len) {

  char sz[32] = "*****";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

// PRINT STRING
static void printStr(const char *str, int len) {
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
