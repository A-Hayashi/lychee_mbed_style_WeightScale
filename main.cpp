#include "mbed.h"
#include <string>
#include "PS_PAD.h"
#include "Weight.h"

using namespace std;

//Serial pc(USBTX, USBRX);

//int main() {
//	PS_PAD pad(P6_14, P6_15, P6_12, P3_9);
//	pad.init();
//	while (1) {
//		pad.poll();
//		pc.printf("%4d\t%4d\t%4d\t%4d\t%04x\n", pad.read(PS_PAD::ANALOG_RX),pad.read(PS_PAD::ANALOG_RY),pad.read(PS_PAD::ANALOG_LX),pad.read(PS_PAD::ANALOG_LY),pad.read(PS_PAD::BUTTONS));
//	}
//}

int main() {
	weight_init();
}

