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
#include <E131.h>

const char ssid[] = "29GK3";         /* Replace with your SSID */
const char passphrase[] = "YT8PP2RWT344ZQZT";   /* Replace with your WPA2 passphrase */

E131 e131;

void setup() {
    Serial.begin(115200);
    delay(10);

    /* Choose one to begin listening for E1.31 data */
    //e131.begin(ssid, passphrase);               /* via Unicast on the default port */
    e131.beginMulticast(ssid, passphrase, 1); /* via Multicast for Universe 1 */
}

void loop() {
    /* Parse a packet */
    uint16_t num_channels = e131.parsePacket();
    
    /* Process channel data if we have it */
    if (num_channels) {
        Serial.printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
                e131.data[1],              
                e131.data[2],
                e131.data[3] ,
                e131.data[4] ,
                e131.data[5] ,
                e131.data[6] ,
                e131.data[7] ,
                e131.data[8] ,
                e131.data[9] ,
                e131.data[10] ,
                e131.data[11] ,
                e131.data[12] ,
                e131.data[13] ,
                e131.data[14] ,
                e131.data[15] ,
                e131.data[16] ,
                e131.data[17] ,
                e131.data[18] ,
                e131.data[19] ,
                e131.data[20]); 
    }
}
