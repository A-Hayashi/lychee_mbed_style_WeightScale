#include "mbed.h"
#include <string>
#include "PS_PAD.h"
#include "Weight.h"
#include "P3RGB64x32MatrixPanel.h"

typedef struct {
	uint8_t stable;
	float weight;
} weight_mail_t;

Mail<weight_mail_t, 16> weight_mail_box;

//P5_14 D0	R1
//P5_8 	D3	G1
//P5_15 D1	B1
//P5_9 	D2	R2
//P5_11 D4	G2
//P5_10 D5 	B2
//P3_10 D8	CLK
//P2_1 	D6	D
//P4_0  	OE
//P1_7 	D14	A
//P2_0	D7	B
//P4_2		C
//P4_1		LAT
void draw_main();
Serial pc(USBTX, USBRX);
Thread T1(osPriorityNormal, 1500 * 1024);

//int main() {
//	PS_PAD pad(P6_14, P6_15, P6_12, P3_9);
//	pad.init();
//	while (1) {
//		pad.poll();
//		pc.printf("%4d\t%4d\t%4d\t%4d\t%04x\n", pad.read(PS_PAD::ANALOG_RX),pad.read(PS_PAD::ANALOG_RY),pad.read(PS_PAD::ANALOG_LX),pad.read(PS_PAD::ANALOG_LY),pad.read(PS_PAD::BUTTONS));
//	}
//}

int main() {
	T1.start(&draw_main);
	return 0;
}

void draw_main() {
	pc.printf("start\n");
//	P3RGB64x32MatrixPanel matrix(D0, D3, D1, D2, D4, D5, D8, D6, P4_0, D14, D7, P4_2, P4_1);
//	matrix.begin();
	weight_init();

	while (true) {
		osEvent evt = weight_mail_box.get();
		if (evt.status == osEventMail) {
			weight_mail_t *mail = (weight_mail_t *) evt.value.p;
			pc.printf("stable:%d\t weight:%f\n", mail->stable, mail->weight);

			// fill the screen with 'black'
//			matrix.fillScreen(matrix.color444(0, 0, 0));
//			matrix.setTextCursor(0, 0);
//			matrix.setTextColor(matrix.color444(15, 0, 0));
//			matrix.printf("%1d %f3.1 kg\n",  mail->stable, mail->weight);

			weight_mail_box.free(mail);
		}

	}
}

void weight_result(uint8_t stable, float weight) {
	weight_mail_t *mail = weight_mail_box.alloc();
	mail->stable = stable;
	mail->weight = weight;
	weight_mail_box.put(mail);
}
