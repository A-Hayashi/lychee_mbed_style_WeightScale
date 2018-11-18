#include "P3RGB64x32MatrixPanel.h"
#include "mbed.h"
#include "iodefine.h"

Ticker P3RGB64x32MatrixPanel::timer;
P3RGB64x32MatrixPanel *P3RGB64x32MatrixPanel::singleton;


static EventQueue queue(1000 * EVENTS_EVENT_SIZE);
static Thread eventThread(osPriorityISR, 100*1024);

void P3RGB64x32MatrixPanel::test()
{
	pinR1 = LOW;
	pinG1 = LOW;
	pinB1 = LOW;
	pinR2 = LOW;
	pinG2 = LOW;
	pinB2 = LOW;
	pinCLK = LOW;
	pinOE = LOW;
	pinLAT = LOW;
	pinA = LOW;
	pinB = LOW;
	pinC = LOW;
	pinD = LOW;

	wait_us(10000);
	pinR1 = HIGH;	//10 o
	wait_us(10000);
	pinG1 = HIGH;	//20 o
	wait_us(10000);
	pinB1 = HIGH;	//30 o
	wait_us(10000);
	pinR2 = HIGH;	//40 o
	wait_us(10000);
	pinG2 = HIGH;	//50 o
	wait_us(10000);
	pinB2 = HIGH;	//60 o
	wait_us(10000);
	pinCLK = HIGH;	//70 o
	wait_us(10000);
	pinOE = HIGH;	//80 o
	wait_us(10000);
	pinLAT = HIGH;	//90 o
	wait_us(10000);
	pinA = HIGH;	//100 o
	wait_us(10000);
	pinB = HIGH;	//110 o
	wait_us(10000);
	pinC = HIGH;	//120 o
	wait_us(10000);
	pinD = HIGH;	//130 o
	wait_us(10000);
}

void P3RGB64x32MatrixPanel::onTimer() {
//	singleton->test();
	singleton->draw();
}

void P3RGB64x32MatrixPanel::begin() {
	singleton = this;
	pinLAT = LOW;
	pinCLK = LOW;
	pinOE = HIGH;

	eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
	timer.attach_us(queue.event(onTimer), 100);
//	timer.attach_us(onTimer, 80);
}

void P3RGB64x32MatrixPanel::stop() {
	timer.detach();
}

uint16_t P3RGB64x32MatrixPanel::colorHSV(long hue, uint8_t sat, uint8_t val) {
	uint8_t r, g, b, lo;
	uint16_t s1, v1;

	// Hue ( 0 - 1535 )
	hue %= 1536;
	if (hue < 0)
		hue += 1536;
	lo = hue & 255;          // Low byte  = primary/secondary color mix
	switch (hue >> 8) {      // High byte = sextant of colorwheel
	case 0:
		r = 255;
		g = lo;
		b = 0;
		break; // R to Y
	case 1:
		r = 255 - lo;
		g = 255;
		b = 0;
		break; // Y to G
	case 2:
		r = 0;
		g = 255;
		b = lo;
		break; // G to C
	case 3:
		r = 0;
		g = 255 - lo;
		b = 255;
		break; // C to B
	case 4:
		r = lo;
		g = 0;
		b = 255;
		break; // B to M
	default:
		r = 255;
		g = 0;
		b = 255 - lo;
		break; // M to R
	}

	s1 = sat + 1;
	r = 255 - (((255 - r) * s1) >> 8);
	g = 255 - (((255 - g) * s1) >> 8);
	b = 255 - (((255 - b) * s1) >> 8);

	v1 = val + 1;
	r = (r * v1) >> 11;
	g = (g * v1) >> 11;
	b = (b * v1) >> 11;

	return color555(r, g, b);
}

void P3RGB64x32MatrixPanel::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if (x < 0 || x >= 64 || y < 0 || y >= 32)
		return;
	int16_t idx = x + y * 64;
	drawBuffer()[idx] = color;
}

void P3RGB64x32MatrixPanel::draw() {
	static byte cnt = 30;
	static byte y = 15;
	y = (y + 1) % 16;

	if (y == 0)
		cnt = (cnt + 1) % 31; // 31 must be skipped

	byte cmp = (cnt >> 4) | ((cnt >> 2) & 0x2) | (cnt & 0x4)
			| ((cnt << 2) & 0x8) | ((cnt << 4) & 0x10);

	for (int x = 0; x < 64; x++) {
		bool r1, b1, g1, r2, g2, b2;
		uint16_t c = matrixbuff[x + y * 64];
		r1 = (c & 0x1f) > cmp;
		g1 = ((c >> 5) & 0x1f) > cmp;
		b1 = ((c >> 10) & 0x1f) > cmp;
		c = matrixbuff[x + (y + 16) * 64];
		r2 = (c & 0x1f) > cmp;
		g2 = ((c >> 5) & 0x1f) > cmp;
		b2 = ((c >> 10) & 0x1f) > cmp;

		//P5_14 D0	R1
		//P5_8 	D3	G1
		//P5_15 D1	B1
		//P5_9 	D2	R2
		//P5_11 D4	G2
		//P5_10 D5 	B2

		uint16_t out;
		out = GPIO.P5 & ~((1<<14) | (1<<8) | (1<<15) | (1<<9) | (1<<11) | (1<<10));
		out |= ((r1<<14) | (g1<<8) | (b1<<15) | (r2<<9) | (g2<<11) | (b2<<10));
		GPIO.P5 = out;

//		pinR1 = r1;
//		pinG1 = g1;
//		pinB1 = b1;
//		pinR2 = r2;
//		pinG2 = g2;
//		pinB2 = b2;

		pinCLK = HIGH;
		pinCLK = LOW;
	}

	pinOE = HIGH;
	pinLAT = HIGH;
	pinLAT = LOW;

	pinA = (y & 0x01) ? HIGH : LOW;
	pinB = (y & 0x02) ? HIGH : LOW;
	pinC = (y & 0x04) ? HIGH : LOW;
	pinD = (y & 0x08) ? HIGH : LOW;

	pinOE = LOW;
//	wait_us(1); // to wait latch and row switch
}

