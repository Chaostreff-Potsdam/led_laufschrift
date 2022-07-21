/*
 Name:      Arduino8x8MatrixStackOverflow.ino
 Created:   3/10/2019 5:21:02 PM
 Author:    jjman (adapted by cyroxx for an 8x7 display)
 Source:    https://stackoverflow.com/a/55095132/1388240
*/

unsigned char A[] = {B00000000,B00111111,B01111111,B01001000,B01001000,B01111111,B00111111,B00000000};
unsigned char B[] = {B00000000,B00000000,B00000110,B01111001,B01001001,B01001001,B11111111,B00000000};
unsigned char C[] = {B00000000,B01000001,B01000001,B01000001,B01000001,B00100010,B00011100,B00000000};
unsigned char D[] = {B00000000,B00011100,B00100010,B01000001,B01000001,B01111111,B00000000,B00000000};
unsigned char E[] = {B00000000,B00000000,B01000001,B01001001,B01001001,B01111111,B00000000,B00000000};
unsigned char F[] = {B00000000,B00000000,B01000000,B01001000,B01001000,B01111111,B00000000,B00000000};
unsigned char G[] = {B00000000,B01000111,B01000101,B01000101,B01000001,B01111111,B00000000,B00000000};
unsigned char H[] = {B00000000,B00000000,B01111111,B00001000,B00001000,B01111111,B00000000,B00000000};
unsigned char I[] = {B00000000,B00000000,B00000000,B01000001,B01111111,B01000001,B00000000,B00000000};
unsigned char J[] = {B00000000,B00000000,B01000000,B01111111,B01000001,B00000011,B00000000,B00000000};
unsigned char K[] = {B00000000,B00000000,B01000011,B00100100,B00011000,B00001000,B01111111,B00000000};
unsigned char L[] = {B00000000,B00000000,B00000001,B00000001,B00000001,B00000001,B01111111,B00000000};
unsigned char M[] = {B00000000,B01111111,B00100000,B00010000,B00010000,B00100000,B01000000,B01111110};
unsigned char N[] = {B00000000,B00111110,B00000100,B00001000,B00010000,B00111110,B00000000,B00000000};
unsigned char O[] = {B00000000,B00111110,B01000001,B01000001,B01000001,B01000001,B00111110,B00000000};
unsigned char P[] = {B00000000,B00000000,B00110000,B01001000,B01001000,B01111111,B00000000,B00000000};
unsigned char Q[] = {B00000001,B00111110,B01000110,B01000010,B01000010,B01000010,B00111100,B00000000};
unsigned char R[] = {B00000000,B00000000,B00110111,B01001000,B01001000,B01111111,B00000000,B00000000};
unsigned char S[] = {B00000000,B00000000,B01001111,B01001001,B01001001,B01111001,B00000000,B00000000};
unsigned char T[] = {B00000000,B00000000,B01000000,B01000000,B01111111,B01000000,B01000000,B00000000};
unsigned char U[] = {B00000000,B01111100,B00000010,B00000001,B00000001,B00000010,B01111100,B00000000};
unsigned char V[] = {B00000000,B01110000,B00001110,B00000001,B00001110,B01110000,B00000000,B00000000};
unsigned char W[] = {B00000000,B01110000,B00001100,B00000010,B00011100,B00000010,B00001100,B01110000};
unsigned char X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
unsigned char Y[] = {B00000000,B00000000,B01100000,B00010000,B00001111,B00010000,B01100000,B00000000};
unsigned char Z[] = {B00000000,B00000000,B01100001,B01010001,B01001001,B01000101,B01000011,B00000000};

unsigned char *Alphabet[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
unsigned char* DisplayBuffer = nullptr;
