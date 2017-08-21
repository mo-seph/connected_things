# Getting Started with Feather boards

Adafruit Docs: https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/?view=all

## Arduino Setup

* Install Arduino SAMD Boards (Tools -> Board -> Boards Manager, search for SAMD)
* Install Adafruit SAMD Boards (Add https://adafruit.github.io/arduino-board-index/package_adafruit_index.json in Preferences -> Additional Boards Manager URLS, then search for SAMD boards again, and the Adafruit ones should be there)


## Serial
* In `setup()`, do `while(!Serial) {;}` after `Serial.begin()` to make sure that none of the output gets lost - otherwise you might miss the first few lines of output.

## WiFi
* Use the current Arduino WiFi101 library by doing Sketch -> Include Library -> Manage Libraries and search for WiFi101.
* Call WiFi.setPins(8,7,4,2); in setup(), before using the WiFi object.

## Default `setup()`
```arduino
void setup() {
  Serial.begin(57600);   // Make sure that the number in the bottom right of the Serial Monitor matches this
  while( !Serial) {;}    // Wait until the Serial port is ready so we don't miss any output
  WiFi.setPins(8,7,4,2); // Setup the WiFi on the Feather boards
  ... (all your specific setup here)
}
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
