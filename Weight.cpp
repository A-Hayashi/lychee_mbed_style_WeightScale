#include "Weight.h"
#include "mbed.h"

static Serial pc(USBTX, USBRX);

#define TIMEOUT_US 30000

static InterruptIn p(P5_9);
static Timer t;
static Timeout t2;
static Timeout t3;

static uint32_t bh = 0;
static uint32_t bl = 0;
static uint32_t cnt = 0;

static EventQueue queue(320 * EVENTS_EVENT_SIZE);

static void fall();
static void rise();
static void restart();

static void itob(char *s, int n, unsigned long long v) {
	if (n > 0) {
		unsigned long long f = 1ULL << (n - 1);
		do
			*s++ = f & v ? '1' : '0';
		while (f >>= 1, --n);
	} else if (n != 0) {
		char *b = s;
		do
			*s++ = '0' + v % 2;
		while ((v >>= 1) && ++n);
		for (char c, *e = s - 1; b < e; b++, e--)
			c = *b, *b = *e, *e = c;
	}
	*s = '\0';
}

static void eee(uint32_t bh, uint32_t bl) {
	uint8_t stable = (bh >> 18) & 0x03;
	if(stable == 0x03){
		p.rise(NULL);
		p.fall(NULL);
		t3.attach(queue.event(restart), 5);
	}

	char s[64];
	itob(s, 2, (unsigned long long int) stable);
	pc.printf(s);
	pc.printf(" ");

	itob(s, 32, bh);
	pc.printf(s);
	pc.printf(" ");

	itob(s, 32, bl);
	pc.printf(s);
	pc.printf("\n");

	if (stable == 0x00) {
	} else if (stable == 0x01) {
	} else if (stable == 0x03) {
		float weight = (bh & 0xffff) / (float) 10;
		pc.printf("%5.2f\t\n", weight);
	} else {
	}
}

static void restart()
{
	p.rise(queue.event(rise));
}

static void timeout() {
	p.rise(NULL);
	p.fall(NULL);
	uint32_t bh_disp = bh;
	uint32_t bl_disp = bl;
	uint32_t cnt_disp = cnt;
	bh = 0;
	bl = 0;
	cnt = 0;
	p.rise(queue.event(rise));

	if (cnt_disp == 39) {
		eee(bh_disp, bl_disp);
	}
}



static void rise() {
	p.rise(NULL);
	t.reset();
	t.start();
	p.fall(queue.event(fall));
}

static void fall() {
	p.fall(NULL);
	t2.attach_us(queue.event(timeout), TIMEOUT_US);
	t.stop();
	uint32_t pulse = t.read_us();
	uint8_t bit = pulse < 750 ? 1 : 0;
	if (cnt < 32) {
		bh |= bit << (31 - cnt);
	} else if (cnt < 64) {
		bl |= bit << (63 - cnt);
	}
	cnt++;
	p.rise(queue.event(rise));
}

Thread eventThread;
void weight_init() {
	eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
	pc.printf("start\n");
	p.mode(PullNone);
	p.rise(queue.event(rise));

}

