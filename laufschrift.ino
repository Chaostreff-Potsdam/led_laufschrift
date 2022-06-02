
/*
 * Lights random pixels on the LED marquee.
 * Has the appearance of digital campfire.
 */

#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "arduino_secrets.h"

#define START 2 // start pin (D2)
#define OUT 11  // output signal pin
#define CLK 12

#define COLS 60
#define ROWS 7


unsigned int localPort = 2390; 
WiFiUDP Udp;

char packetBuffer[256]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back


char ssid[] = SECRET_SSID;                // your network SSID (name)
char pass[] = SECRET_PASS;                // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;             // the Wi-Fi radio's status
int ledState = LOW;                       //ledState used to set the LED
unsigned long previousMillisInfo = 0;     //will store last time Wi-Fi information was updated
unsigned long previousMillisLED = 0;      // will store the last time LED was updated
const int intervalInfo = 5000;            // interval at which to update the board information

uint8_t values[COLS];

void setup_wifi() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // set the LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");
}

void setup_ota() {
  //ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_pins() {
  pinMode(OUT, OUTPUT);
  pinMode(CLK, OUTPUT);

  // setup the 
  for (int i=0; i<ROWS; i++) {
     pinMode(START + i, OUTPUT);
     digitalWrite(START + i, HIGH);
  }

  //values[58] = 0x01;
  //values[59] = 0xff;

  // zero all bits in the shift register
  for (int i=0; i<COLS; i++) {
      digitalWrite(OUT, 0);    
      digitalWrite(CLK, HIGH);
      delay(1);
      //delayMicroseconds(1);
      digitalWrite(CLK, LOW);      
    }
}

void setup() {
  setup_pins();
  setup_wifi();
  setup_ota();
  Udp.begin(localPort);
}

long newVal = 0;


void loop_pins() {
  
  //newVal = newVal + random(0, 32);
  newVal = 255;

  if (newVal > 255) newVal = 0;

  long mycol = 13; //random(0, COLS);
  //long newVal = random(0, 255);
  //long newVal = COLS;

  values[mycol] = newVal;
  
  for (uint8_t line=0; line<ROWS; line++) {

    // fill the shift registers of the current line
    for (uint8_t i=0; i<COLS; i++) {
      uint8_t b = values[COLS - i];  // inverted index logic b/c of the shift registers

      digitalWrite(OUT, bitRead(b, line));
          
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
      //delay(10);
      
    }

    // show line
    digitalWrite(line+2, LOW);
    delay(1);
    digitalWrite(line+2, HIGH);
  }
}

void check_wifi() {
  unsigned long currentMillisInfo = millis();

  // check if the time after the last update is bigger the interval
  if (currentMillisInfo - previousMillisInfo >= intervalInfo) {
    previousMillisInfo = currentMillisInfo;

    Serial.println("Board Information:");
    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print your network's SSID:
    Serial.println();
    Serial.println("Network Information:");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);
    Serial.println("---------------------------------------");
  }
  
  unsigned long currentMillisLED = millis();
  
  // measure the signal strength and convert it into a time interval
  int intervalLED = WiFi.RSSI() * -10;
 
  // check if the time after the last blink is bigger the interval 
  if (currentMillisLED - previousMillisLED >= intervalLED) {
    previousMillisLED = currentMillisLED;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BUILTIN, ledState);
  }
}

void set_led(int row, int col, int new_state) {
  uint8_t old_val = values[col];
  //uint8_t new_val = new_state << (row - 1);
  uint8_t new_val;
  if (new_state == 1) {
    new_val = bitSet(old_val, row - 1);
  } else {
    new_val = bitClear(old_val, row - 1);
  }
  //uint8_t new_val =

  values[col] = new_val;
}

void processUDP() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
    
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    //int test = atoi(packetBuffer);

    String message;

    message = packetBuffer;
    Serial.println("ALS INT GEPARST: ");
    Serial.println(message);

    int firstDelim = message.indexOf(",");
    int lastDelim = message.lastIndexOf(",");
    
    int row = message.substring(0, firstDelim).toInt();
    int col = message.substring(firstDelim+1, lastDelim).toInt();
    int new_state = message.substring(lastDelim+1).toInt();
    Serial.println(row);
    Serial.println(col);
    Serial.println(new_state);


    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();


    set_led(row, col, new_state);
  }
}

void loop() {
  loop_pins();
  //check_wifi();
  //ArduinoOTA.handle();
  processUDP();
}
