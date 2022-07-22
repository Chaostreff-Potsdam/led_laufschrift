/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 3"
  https://create.arduino.cc/cloud/things/d9dd4d87-a60e-438c-ae55-7b0ad1805f4c 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String message;
  int highlightColumn;
  int uptime;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include "alphabet.h"
#define START 2 // start pin (D2)
#define OUT 11  // output signal pin
#define CLK 12

#define COLS 60
#define ROWS 7

#define DEBUG 1

uint8_t values[COLS];

char myMessage[8];



#if !( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )
  #error This code is designed to run on SAMD21/SAMD51 platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "SAMDTimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
// Don't define TIMER_INTERRUPT_DEBUG > 2. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "SAMDTimerInterrupt.h"
#include "SAMD_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS      10

// Depending on the board, you can select SAMD21 Hardware Timer from TC3, TC4, TC5, TCC, TCC1 or TCC2
// SAMD51 Hardware Timer only TC3

// Init SAMD timer TIMER_TC3
SAMDTimer ITimer(TIMER_TC3);

// Init SAMD_ISR_Timer
// Each SAMD_ISR_Timer can service 16 different ISR-based timers
SAMD_ISR_Timer ISR_Timer;

#define TIMER_INTERVAL_2MS               2L
#define TIMER_INTERVAL_1S             1000L

void TimerHandler(void)
{
  ISR_Timer.run();
}

int current_row = 0;

int current_loop = 0;

void doingSomething1()
{
  //digitalWrite(current_row+2, HIGH);
  // fill the shift registers of the current line
  current_row++;
  
  if (current_row >= ROWS) current_row = 0;
  
  for (uint8_t i=0; i<COLS; i++) {
    uint8_t b = values[COLS - i];  // inverted index logic b/c of the shift registers

    digitalWrite(OUT, bitRead(b, current_row));
        
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
    //delay(10);
  }

  // show line
  digitalWrite(current_row+2, LOW);
  delay(1);
  digitalWrite(current_row+2, HIGH);
}

void tick() {
   // shift matrix contents by one column to get marquee effect
   for (uint8_t i=COLS; i>0; i--) {
    values[i] = values[i - 1];
   }

   values[0] = 0;

#if DEBUG
  debugPrintValues();
#endif
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(150); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  setup_pins();
  setup_timer();
}

void loop() {
  current_loop++;
  
  if (current_loop == 10) {
    long pre = millis();
    ArduinoCloud.update();
    long post = millis();
    
    //Serial.println(post - pre);  
    //uptime = millis() / 1000;
    uptime = post - pre;
    
    current_loop = 0;
  }


  
  uint8_t mycol = random(0, COLS);
  uint8_t myrow = random(0, ROWS);
  uint8_t newstate = random(0, 1);
  
  //set_led(myrow, mycol, newstate);
  //updateDisplay();
  
  //loop_pins();
  
  uint8_t newVal = random(0, 255);
  //values[mycol] = newVal;
  delay(500);
  
  // TEST
  char falsch[8] = "FALSCH";
  
  //PrintText(falsch);
  
}


void PrintText(char *str)
{
  clearDisplay();
  
  for (uint8_t letter=0; letter < 7; letter++) {
    for (uint8_t i=0; i<8; i++) {
      if (str[letter]==32) {  // space
        values[COLS-(letter*8+(8-i))-1] = SPACE[i];
        
      } else if (str[letter]>=65 && str[letter]<=90) {  // uppercase characters
        values[COLS-(letter*8+(8-i))-1] = Alphabet[int(str[letter])-65][i];
        
      } else if (str[letter]>=97 && str[letter]<=122) {  // lowercase characters -> uppercase
        values[COLS-(letter*8+(8-i))-1] = Alphabet[int(str[letter])-97][i];
        
      } else {  // all else
        values[COLS-(letter*8+(8-i))-1] = REPLACEMENT_CHARACTER[i];
      }
    }
  }
  
#if DEBUG
  String debugOutput = String();
  for (uint8_t j=0;j<ROWS;j++) {
    for (uint8_t i=0;i<COLS;i++) {
      if (get_led(ROWS - j - 1 , COLS - i - 1)) {
        debugOutput = debugOutput + 'x';
      } else {
        debugOutput = debugOutput + '.';
      }
    }
    debugOutput = debugOutput + '\n';
  }
  Serial.println(debugOutput);
#endif
}

/*
  Since Uptime is READ_WRITE variable, onUptimeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onUptimeChange()  {
  // Add your code here to act upon Uptime change
}

void setup_timer() {
  
  Serial.print(F("\nStarting TimerInterruptLEDDemo on ")); Serial.println(BOARD_NAME);
  Serial.println(SAMD_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));
  
  // Interval in microseconds
  if (ITimer.attachInterruptInterval(1500, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2MS,  doingSomething1);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S,   tick);
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
  clearDisplay();
  
  
  
  //highlightColumn = 13;
}

void clearDisplay() {
    for (uint8_t i=0; i<COLS; i++) {
      digitalWrite(OUT, 0);    
      digitalWrite(CLK, HIGH);
      delay(1);
      //delayMicroseconds(1);
      digitalWrite(CLK, LOW);      
    }
}

void loop_pins() {
  
  //newVal = newVal + random(0, 32);
  //long newVal = 255;

  //if (newVal > 255) newVal = 0;

  //long mycol = 13; //random(0, COLS);
  //long newVal = random(0, 255);
  //long newVal = COLS;
  
  //highlightColumn = 13;


  //values[mycol] = newVal;
  
  
}

/*
  Since HighlightColumn is READ_WRITE variable, onHighlightColumnChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHighlightColumnChange()  {
  values[highlightColumn] = 255;
  updateDisplay();
}

void updateDisplay() {
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
    
    // wahrscheinlich falsch rum
    /*digitalWrite(line+2, HIGH);
    delay(1);
    digitalWrite(line+2, LOW);*/
  }
}

uint8_t get_led(int row, int col) {
  uint8_t column = values[col];
  
  uint8_t pixel_state = bitRead(column, row);

  return pixel_state;
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

/*
  Since Message is READ_WRITE variable, onMessageChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMessageChange()  {
  Serial.println(message);
  
  for (uint8_t i=0; i < 7; i++) {
    if (message.length() > i) {
      myMessage[i] = message.charAt(i);  
    } else {
      myMessage[i] = ' ';
    } 
  }
  
  PrintText(myMessage);
}
