# Useful things when using ThingSpeak

## Account creation
Before you can do anything, you need to make an account on ThingSpeak.com. Then, create a channel. Once you have made a channel, you should be able to go to https://thingspeak.com/channels/<channel number>/edit and get useful info about your channel. Generally, you will need:
* Channel Number - it's in the URL, and in the Channel Settings tab.
* API Key - Write API key in the API Keys tab.

## Channels and fields

A channel roughly represents a single device. Different fields represent different inputs for that device

## Setting up Arduino IDE
* Install the ThingSpeak library by doing Sketch -> Include Library -> Manage Libraries, then search for ThingSpeak.
* Restart to see the examples

## Modifying the examples for the Feather boards
The Feather boards are slightly different to other Arduinos, so there are some small changes that need to be made to the examples to make them run. The ThingspeakConnection sketch in this repository has had those modifications made, so you have some code that will work. If you want to run the other examples (which contain setup code for lots of boards), do the following:
* uncomment `#define USE_WIFI101_SHIELD`
* if it is an example that uses `VOLTAGE_MAX` and `VOLTAGE_MAXCOUNTS`, make sure that you have the following lines at the top of your code, outside any `#ifdef` lines:
```arduino
#define VOLTAGE_MAX 3.3
#define VOLTAGE_MAXCOUNTS 1023.0  
```

## ThingSpeak
When you call `ThingSpeak.writeField()` it will return a number to tell you what happened. This is what those numbers mean:
* 200: OK / Success
* 400: Incorrect API key (or invalid ThingSpeak server address)
* 404: Incorrect API key (or invalid ThingSpeak server address)
* -101: Value is out of range or string is too long (> 255 bytes)
* -201: Invalid field number specified
* -210: setField() was not called before writeFields()
* -301: Failed to connect to ThingSpeak
* -302: Unexpected failure during write to ThingSpeak
* -303: Unable to parse response
* -304: Timeout waiting for server to respond
* -401: Point was not inserted (most probable cause is the rate limit of once every 15 seconds)
