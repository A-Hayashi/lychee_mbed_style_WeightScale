/* Derived from Adafruit RGB_matrix_Panel library */

#include "P3RGB64x32MatrixPanel.h"
#include "mbed.h"
//A0 R1
//D3 G1
//A1 B1
//A2 R2
//D4 G2
//A3 B2
//D9 CLK
//D7 LAT
//D8 OE
//A4 A
//D5 B
//A5 C
//D6 D

//P3RGB64x32MatrixPanel(PinName _pinR1, PinName _pinG1, PinName _pinB1, PinName _pinR2, PinName _pinG2, PinName _pinB2, PinName _pinCLK, PinName _pinLAT, PinName _pinOE, PinName _pinA, PinName _pinB, PinName _pinC, PinName _pinD, bool _doubleBuffer = false)
//  : Adafruit_GFX(64, 32), pinR1(_pinR1), pinG1(_pinG1), pinB1(_pinB1), pinR2(_pinR2), pinG2(_pinG2), pinB2(_pinB2), pinCLK(_pinCLK), pinLAT(_pinLAT), pinOE(_pinOE), pinA(_pinA), pinB(_pinB), pinC(_pinC), pinD(_pinD), doubleBuffer(_doubleBuffer) {
//  initMatrixBuff();
//}

P3RGB64x32MatrixPanel matrix(A0,D3,A1,A2,D4,A3,D9,D7,D8,A4,D5,A5,D6);

uint16_t Wheel(byte WheelPos);
void setup();
void loop();


int main()
{
	setup();
	while(true){
		loop();
	}

	return 0;
}

void setup() {

  matrix.begin();

  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.color444(15, 15, 15));
  wait_ms(500);

  // fix the screen with green
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.color444(0, 15, 0));
  wait_ms(500);

  // draw a box in yellow
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.color444(15, 15, 0));
  wait_ms(500);

  // draw an 'X' in red
  matrix.drawLine(0, 0, matrix.width()-1, matrix.height()-1, matrix.color444(15, 0, 0));
  matrix.drawLine(matrix.width()-1, 0, 0, matrix.height()-1, matrix.color444(15, 0, 0));
  wait_ms(500);

  // draw a blue circle
  matrix.drawCircle(10, 10, 10, matrix.color444(0, 0, 15));
  wait_ms(500);

  // fill a violet circle
  matrix.fillCircle(40, 21, 10, matrix.color444(15, 0, 15));
  wait_ms(500);

  // fill the screen with 'black'
  matrix.fillScreen(matrix.color444(0, 0, 0));

  // draw some text!
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setTextCursor(8, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  char *str = "P3indoorSMDDisplay";
  for (w=0; w<8; w++) {
    matrix.setTextColor(Wheel(w));
    matrix.writeChar(str[w]);
  }
  matrix.setTextCursor(2, 8);    // next line
  for (w=8; w<18; w++) {
    matrix.setTextColor(Wheel(w));
    matrix.writeChar(str[w]);
  }
  matrix.writeChar('\n');
  //matrix.setTextColor(matrix.Color333(4,4,4));
  //matrix.println("Industries");
  matrix.setTextColor(matrix.color444(15,15,15));
  matrix.printf("%s", "LED MATRIX!\n");

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.color444(15,0,0));
  matrix.writeChar('3');
  matrix.setTextColor(matrix.color444(15,4,0));
  matrix.writeChar('2');
  matrix.setTextColor(matrix.color444(15,15,0));
  matrix.writeChar('x');
  matrix.setTextColor(matrix.color444(8,15,0));
  matrix.writeChar('6');
  matrix.setTextColor(matrix.color444(0,15,0));
  matrix.writeChar('4');
  matrix.setTextColor(34, 24);
  matrix.setTextColor(matrix.color444(0,15,15));
  matrix.writeChar('*');
  matrix.setTextColor(matrix.color444(0,8,15));
  matrix.writeChar('R');
  matrix.setTextColor(matrix.color444(0,0,15));
  matrix.writeChar('G');
  matrix.setTextColor(matrix.color444(8,0,15));
  matrix.writeChar('B');
  matrix.setTextColor(matrix.color444(15,0,8));
  matrix.writeChar('*');
  matrix.writeChar('\n');

  // whew!
}

void loop() {
  // do nothing
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if(WheelPos < 8) {
   return matrix.color444(15 - WheelPos*2, WheelPos*2, 0);
  } else if(WheelPos < 16) {
   WheelPos -= 8;
   return matrix.color444(0, 15-WheelPos*2, WheelPos*2);
  } else {
   WheelPos -= 16;
   return matrix.color444(0, WheelPos*2, 7 - WheelPos*2);
  }
}



