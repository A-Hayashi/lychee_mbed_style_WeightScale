/*
 * PlayStation Controller library
 * Copyright (c) 2013 Hiroshi Suga
 */

#include "mbed.h"

class PS_PAD {
public:
    enum TYPE {
        PAD_LEFT,
        PAD_BOTTOM,
        PAD_RIGHT,
        PAD_TOP,
        PAD_START,
        ANALOG_LEFT,
        ANALOG_RIGHT,
        PAD_SELECT,
        PAD_SQUARE,
        PAD_X,
        PAD_CIRCLE,
        PAD_TRIANGLE,
        PAD_R1,
        PAD_L1,
        PAD_R2,
        PAD_L2,
        BUTTONS,
        ANALOG_RX,
        ANALOG_RY,
        ANALOG_LX,
        ANALOG_LY,
    };

    PS_PAD (PinName mosi, PinName miso, PinName sck, PinName cs);
    PS_PAD (SPI &spi, PinName cs);

    int init ();
    int poll ();
    int read (TYPE t);
    int vibration (int v1, int v2);

private:
    SPI &_spi;
    DigitalOut _cs;
    uint8_t _pad[6];
    int _vib1, _vib2;
    bool _connected;

    int send (const char *cmd, int len, char *dat);
    int __rbit(int v);
};
