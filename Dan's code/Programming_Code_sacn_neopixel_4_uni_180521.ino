/*
* ESP8266_Test.ino - Simple sketch to listen for E1.31 data on an ESP8266 
*                    and print some statistics.
*
* Project: E131 - E.131 (sACN) library for Arduino
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#include <ESP8266WiFi.h>
#include <ESPAsyncE131.h>
#include <Adafruit_NeoPixel.h>

#define UNIVERSE 1                      // First DMX Universe to listen for
#define UNIVERSE_COUNT 4                // Total number of Universes to listen for, starting at UNIVERSE
#define PIN            2
#define PIN2            5
#define NUMPIXELS      250

const char ssid[] = "WirelessDimmers";         // Replace with your SSID
const char passphrase[] = "abbafishnewt";   // Replace with your WPA2 passphrase

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    delay(10);
    
    // Make sure you're in station mode    
    WiFi.mode(WIFI_STA);

    Serial.println("");
    Serial.print(F("Connecting to "));
    Serial.print(ssid);

    if (passphrase != NULL)
        WiFi.begin(ssid, passphrase);
    else
        WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    pixels.begin(); // This initializes the NeoPixel library.
    pixels2.begin();

    Serial.println("");
    Serial.print(F("Connected with IP: "));
    Serial.println(WiFi.localIP());
    
    // Choose one to begin listening for E1.31 data
    //if (e131.begin(E131_UNICAST))                               // Listen via Unicast
    if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT))   // Listen via Multicast
        Serial.println(F("Listening for data..."));
    else 
        Serial.println(F("*** e131.begin failed ***"));
}

void loop() {
    if (!e131.isEmpty()) {
        e131_packet_t packet;
        e131.pull(&packet);     // Pull packet from ring buffer
        if (htons(packet.universe)==1) {
          
        for (int i = 0; i < 170; i++) {
             pixels.setPixelColor(i, pixels.Color(packet.property_values[i*3+1],packet.property_values[i*3+2],packet.property_values[i*3+3]));

    
             
          }
           // This sends the updated pixel color to the hardware.
        }
if (htons(packet.universe)==2) {
  
        for (int i = 0; i < 33; i++) {
             pixels.setPixelColor(i+170, pixels.Color(packet.property_values[i*3+1],packet.property_values[i*3+2],packet.property_values[i*3+3]));

            
          }
        }
        if (htons(packet.universe)==3) {
          
        for (int i = 0; i < 170; i++) {
             pixels2.setPixelColor(i, pixels2.Color(packet.property_values[i*3+1],packet.property_values[i*3+2],packet.property_values[i*3+3]));

             
          }
        }
        if (htons(packet.universe)==4) {
          
        for (int i = 0; i < 28; i++) {
             pixels2.setPixelColor(i+170, pixels2.Color(packet.property_values[i*3+1],packet.property_values[i*3+2],packet.property_values[i*3+3]));

             
          }
        }
        
       
    }
    pixels.show();` 
    pixels2.show();
}

