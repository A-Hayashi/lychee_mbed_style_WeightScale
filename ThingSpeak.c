//#include "mbed.h"
//#include "http_request.h"
//
//#include "ESP32Interface.h"
//#include "PS_PAD.h"
//
//ESP32Interface wifi(P5_3, P3_14, P7_1, P0_1);
//Serial pc(USBTX, USBRX);
//
//const char* ssid = "W04_78625678F45E";//書き換えてください
//const char* password = "6dqbfjgfyb6gi22";//書き換えてください
//
//void ChannelUpdate(int field1, int field2);
//Timer t;
//
//int main() {
//	PS_PAD pad(P6_14, P6_15, P6_12, P3_9);
//
//    pc.baud(9600);
//
//    pc.printf("\nConnecting...\n");
//    int ret = wifi.connect(ssid, password, NSAPI_SECURITY_WPA_WPA2);
//    if (ret != 0) {
//    	pc.printf("\nConnection error\n");
//        return -1;
//    }
//    pc.printf("Success\n\n");
//    pc.printf("MAC: %s\n", wifi.get_mac_address());
//    pc.printf("IP: %s\n", wifi.get_ip_address());
//    pc.printf("Netmask: %s\n", wifi.get_netmask());
//    pc.printf("Gateway: %s\n", wifi.get_gateway());
//    pc.printf("RSSI: %d\n\n", wifi.get_rssi());
//
//	pad.init();
//	t.start();
//
//	while (1) {
//		pad.poll();
//		int field1 = pad.read(PS_PAD::ANALOG_RX)+128;
//		int field2 = pad.read(PS_PAD::ANALOG_LX)+128;
//
//		if(t.read() > 5){
//			pc.printf("field1: %d, field2: %d\n", field1, field2);
//			if(pad.read(PS_PAD::PAD_R1)){
//				t.reset();
//				t.start();
//				ChannelUpdate(pad.read(PS_PAD::ANALOG_RX)+128, pad.read(PS_PAD::ANALOG_LX)+128);
//			}
//		}
//	}
//}
//
//
//
//void ChannelUpdate(int field1, int field2)
//{
//	char* thingSpeakUrl = "http://api.thingspeak.com/update";
//	char* thingSpeakKey = "DAUNON43Q966D9XS";
//
//	char urlBuffer[256];
//
//	urlBuffer[0] = 0;
//
//	sprintf(urlBuffer, "%s?key=%s&field1=%d&field2=%d", thingSpeakUrl, thingSpeakKey, field1, field2);
//
//	pc.printf("Request to %s\r\n", urlBuffer);
//	pc.printf("\n----- HTTP GET request -----\n");
//
//    HttpRequest* get_req = new HttpRequest(&wifi, HTTP_GET, urlBuffer);
//
//    HttpResponse* get_res = get_req->send();
//    if (!get_res) {
//    	pc.printf("HttpRequest failed (error code %d)\n", get_req->get_error());
//    	return;
//    }
//    pc.printf("\n----- HTTP GET response -----\n");
//
//    pc.printf("%s\n", get_res->get_body_as_string().c_str());
//    delete get_req;
//}
