/*
  WriteVoltage - adapted for the Feather ATWINC boards from the ThingSpeak WriteVoltage example
  
  Reads an analog voltage from pin 0, and writes it to a channel on ThingSpeak every 20 seconds.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize and 
  analyze live data streams in the cloud.
  
  Copyright 2017, The MathWorks, Inc.
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the extras/documentation folder where the library was installed.
  See the accompaning licence file for licensing information.
*/

#include "ThingSpeak.h"
#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "<ssid here>";     //  your network SSID (name) 
char pass[] = "<password here>";   // your network password
WiFiClient  client; 

/*
  *****************************************************************************************
  **** Visit https://www.thingspeak.com to sign up for a free account and create
  **** a channel.  The video tutorial http://community.thingspeak.com/tutorials/thingspeak-channels/ 
  **** has more information. You need to change this to your channel, and your write API key
  **** IF YOU SHARE YOUR CODE WITH OTHERS, MAKE SURE YOU REMOVE YOUR WRITE API KEY!!
  *****************************************************************************************/
unsigned long myChannelNumber = -1; //Put your channel number in here
const char * myWriteAPIKey = "<API KEY HERE>"; //Put your API key in here

String hostName = "www.google.com";
int pingResult;

void setup() {
  Serial.begin(57600);   // Make sure that the number in the bottom right of the Serial Monitor matches this
  while( !Serial) {;}    // Wait until the Serial port is ready so we don't miss any output
  WiFi.setPins(8,7,4,2); // Setup the WiFi on the Feather boards

  /* Start the WiFi connection */
  Serial.println("Starting..."); 
  Serial.println("Connecting to WiFi");  
  int conn = WiFi.begin(ssid, pass);
  if( conn == WL_CONNECTED )        { Serial.println("OK!");}
  else if( conn == WL_IDLE_STATUS ) {Serial.println("Idle");}
  else                              {Serial.println("Unknown response");}

  /* Now connect to ThingSpeak */
  ThingSpeak.begin(client);
  Serial.println("Started");
}

void loop() {
  
  /* First of all, get the data and calculate the voltage */
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  //The voltage can be between 0 and 3.3v, and gives readings from 0 to 2013
  float voltage = sensorValue * (3.3 / 1024.0); 

  /* Now, test the wifi connection by trying to connect to a server that we know works */
  Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");
  pingResult = WiFi.ping(hostName);

  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }

  //Check that a channel number has been set
  if( myChannelNumber < 0 ) { Serial.println("Warning! No channel number set!"); }

  /* 
   * Finally, try to write to ThingSpeak
   * There are up to 8 fields in a channel, allowing you to store up to 8 different
   * pieces of information.  Here, we write to field 1. 
   */
  Serial.print("Writing voltage " );
  Serial.print(voltage);
  Serial.print(" to field 1 of channel " );
  Serial.println(myChannelNumber);
  int resp = ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  Serial.print("Response: ");
  Serial.println(resp);
  delay(2000); // ThingSpeak will only accept updates every 15 seconds.

}
