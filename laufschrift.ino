
/*
 * Lights random pixels on the LED marquee.
 * Has the appearance of digital campfire.
 */

#define START 2 // start pin (D2)
#define OUT 11  // output signal pin
#define CLK 12

#define COLS 60
#define ROWS 7

uint8_t values[COLS];


void setup() {
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
      digitalWrite(CLK, LOW);      
    }
}

void loop() {

  long mycol = random(0, COLS);
  long newVal = random(0, 255);
  //long newVal = 255;

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
