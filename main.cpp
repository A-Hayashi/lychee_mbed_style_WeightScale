#include "mbed.h"
#include <string>

using namespace std;
uint8_t *hex_decode(const char *in, size_t len, uint8_t *out);

Serial pc(USBTX, USBRX); // tx, rx

char msg[20] = "Hello World!\n";

int main() {
	pc.format(8, SerialBase::Even, 1);
	pc.printf(msg);
	char data[1100];
	int data_index = 0;



	while (1) {
		if (!pc.readable())
			continue;

		char c = pc.getc();
		data[data_index++] = c;
		if (c == '\n') {
			data[data_index] = '\0';
			data_index = 0;

			//			int i = 0;
			//			for(;;){
			//				pc.putc(data[i]);
			//				i++;
			//				if(data[i]=='\0') break;
			//			}
			//			pc.putc('\n');

			uint8_t a[20];
			hex_decode(data, strlen(data), a);
//			pc.printf("%x %x %x %x %x %x %x %x\n", a[0], a[1], a[2], a[3], a[4],
//					a[5], a[6], a[7]);
			if (a[0] == 0xF4) {
				unsigned char size = a[1];
				unsigned long addr = a[4] * 0x1000000 + a[5] * 0x10000
						+ a[6] * 0x100 + a[7];

//				pc.printf("size:%d, addr:%x\n", size, addr);

				uint8_t data[20];
				for (int i = 0; i < size; i++) {
					data[i] = *((uint8_t *) (addr + i));
				}

				pc.printf("data:");
				for (int i = 0; i < size; i++) {
					pc.printf("%2x ", data[i]);
				}
				pc.printf("\n");

			}
		}
	}
}

uint8_t *hex_decode(const char *in, size_t len, uint8_t *out) {
	unsigned int i, t, hn, ln;

	for (t = 0, i = 0; i < len; i += 2, ++t) {

		hn = in[i] > '9' ? in[i] - 'A' + 10 : in[i] - '0';
		ln = in[i + 1] > '9' ? in[i + 1] - 'A' + 10 : in[i + 1] - '0';

		out[t] = (hn << 4) | ln;
	}

	return out;
}
