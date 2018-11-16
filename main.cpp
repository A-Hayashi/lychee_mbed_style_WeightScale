/* Derived from Adafruit RGB_matrix_Panel library */

#include "P3RGB64x32MatrixPanel.h"
#include "mbed.h"

//D0 R1
//D3 G1
//D1 B1
//D2 R2
//D4 G2
//D10	B2
//D8	CLK
//D6	D
//P4_0  OE
//D14	A
//D5 	B
//D15	C
//D7	LAT

//P3RGB64x32MatrixPanel(PinName _pinR1, PinName _pinG1, PinName _pinB1, PinName _pinR2, PinName _pinG2, PinName _pinB2, PinName _pinCLK, PinName _pinLAT, PinName _pinOE, PinName _pinA, PinName _pinB, PinName _pinC, PinName _pinD, bool _doubleBuffer = false)
//  : Adafruit_GFX(64, 32), pinR1(_pinR1), pinG1(_pinG1), pinB1(_pinB1), pinR2(_pinR2), pinG2(_pinG2), pinB2(_pinB2), pinCLK(_pinCLK), pinLAT(_pinLAT), pinOE(_pinOE), pinA(_pinA), pinB(_pinB), pinC(_pinC), pinD(_pinD), doubleBuffer(_doubleBuffer) {
//  initMatrixBuff();
//}

void draw_main();
void setup(P3RGB64x32MatrixPanel &matrix);
void loop();
uint16_t Wheel(P3RGB64x32MatrixPanel &matrix, byte WheelPos);

Thread T1(osPriorityNormal, 1500 * 1024);

int main() {
	T1.start(&draw_main);

	while (true) {

	}
	return 0;
}

void draw_main() {
	P3RGB64x32MatrixPanel matrix(D0, D3, D1, D2, D4, D10, D8, D6, P4_0, D14, D5, D15, D7);
	Serial pc(USBTX, USBRX);

	pc.printf("draw_main\n");
	setup(matrix);
	pc.printf("setup\n");
	while (true) {
//		pc.printf("loop\n");
		loop();
	}
}

void setup(P3RGB64x32MatrixPanel &matrix) {

	matrix.begin();

//	// draw a pixel in solid white
//	matrix.drawPixel(0, 0, matrix.color444(15, 15, 15));
//	wait_ms(500);
//
//	// fix the screen with green
//	matrix.fillRect(0, 0, matrix.width(), matrix.height(),
//			matrix.color444(0, 15, 0));
//	wait_ms(500);

//	// draw a box in yellow
//	matrix.drawRect(0, 0, matrix.width(), matrix.height(),
//			matrix.color444(15, 15, 0));
//	wait_ms(500);

//	// draw an 'X' in red
//	matrix.drawLine(0, 0, matrix.width() - 1, matrix.height() - 1,
//			matrix.color444(15, 0, 0));
//	matrix.drawLine(matrix.width() - 1, 0, 0, matrix.height() - 1,
//			matrix.color444(15, 0, 0));
//	wait_ms(500);
//
//	// draw a blue circle
//	matrix.drawCircle(10, 10, 10, matrix.color444(0, 0, 15));
//	wait_ms(500);
//
//	// fill a violet circle
//	matrix.fillCircle(40, 21, 10, matrix.color444(15, 0, 15));
//	wait_ms(500);
//
//	// fill the screen with 'black'
//	matrix.fillScreen(matrix.color444(0, 0, 0));
//
	// draw some text!
	matrix.setTextSize(1);     // size 1 == 8 pixels high
	matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

	matrix.setTextCursor(8, 0);    // start at top left, with 8 pixel of spacing
	uint8_t w = 0;
	char *str = "P3indoorSMDDisplay";
	for (w = 0; w < 8; w++) {
		matrix.setTextColor(Wheel(matrix, w));
		matrix.writeChar(str[w]);
	}
	matrix.setTextCursor(2, 8);    // next line
	for (w = 8; w < 18; w++) {
		matrix.setTextColor(Wheel(matrix, w));
		matrix.writeChar(str[w]);
	}
//	matrix.writeChar('\n');
//
//	matrix.setTextColor(matrix.color444(15, 15, 15));
//	matrix.printf("%s", "LED MATRIX!\n");
//
//	// print each letter with a rainbow color
//	matrix.setTextColor(matrix.color444(15, 0, 0));
//	matrix.writeChar('3');
//	matrix.setTextColor(matrix.color444(15, 4, 0));
//	matrix.writeChar('2');
//	matrix.setTextColor(matrix.color444(15, 15, 0));
//	matrix.writeChar('x');
//	matrix.setTextColor(matrix.color444(8, 15, 0));
//	matrix.writeChar('6');
//	matrix.setTextColor(matrix.color444(0, 15, 0));
//	matrix.writeChar('4');
//	matrix.setTextColor(34, 24);
//	matrix.setTextColor(matrix.color444(0, 15, 15));
//	matrix.writeChar('*');
//	matrix.setTextColor(matrix.color444(0, 8, 15));
//	matrix.writeChar('R');
//	matrix.setTextColor(matrix.color444(0, 0, 15));
//	matrix.writeChar('G');
//	matrix.setTextColor(matrix.color444(8, 0, 15));
//	matrix.writeChar('B');
//	matrix.setTextColor(matrix.color444(15, 0, 8));
//	matrix.writeChar('*');
//	matrix.writeChar('\n');

}

void loop() {
	// do nothing
}

// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(P3RGB64x32MatrixPanel &matrix, byte WheelPos) {
	if (WheelPos < 8) {
		return matrix.color444(15 - WheelPos * 2, WheelPos * 2, 0);
	} else if (WheelPos < 16) {
		WheelPos -= 8;
		return matrix.color444(0, 15 - WheelPos * 2, WheelPos * 2);
	} else {
		WheelPos -= 16;
		return matrix.color444(0, WheelPos * 2, 7 - WheelPos * 2);
	}
}

