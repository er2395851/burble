// MultiArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with

#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 11
#define numLeds NUM_LEDS_PER_STRIP*6

CRGB uni1[NUM_LEDS_PER_STRIP];
CRGB uni2[NUM_LEDS_PER_STRIP];
int ledarray[numLeds];
// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip


// Example 5 - Receive with start- and end-markers combined with parsing

const byte numChars = 170*18;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;

//============

void setup() {
    Serial.begin(9600);
    Serial.println("This demo expects a large amount of data, 340 pixels worth per line");
    Serial.println("Enter data in this style <r,g,b,r,g,b,r,g,b...>  ");
    Serial.println();
      // tell FastLED universe 1 is on pin 2
  FastLED.addLeds<NEOPIXEL, 2>(uni1, NUM_LEDS_PER_STRIP);

  // tell FastLED universe 2 is on pin 5
  FastLED.addLeds<NEOPIXEL, 5>(uni2, NUM_LEDS_PER_STRIP);
    FastLED.show();
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first data point from the array
    ledarray[0] = atoi(strtokIndx);     // place this point at the start of the array

    
    for (int i=1; i<numLeds;i++){
      strtokIndx = strtok(NULL, ",");
      ledarray[i] = atoi(strtokIndx); 
    }

}

//============

void showParsedData() {
    update_leds();
}

void update_leds(){
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      uni1[i] = CRGB(ledarray[i*3],ledarray[i*3+1],ledarray[i*3+2]);
      uni2[i] = CRGB(ledarray[(i+NUM_LEDS_PER_STRIP)*3],ledarray[(i+NUM_LEDS_PER_STRIP)*3+1],ledarray[(i+NUM_LEDS_PER_STRIP)*3+2]);
      FastLED.show();
    }
}

