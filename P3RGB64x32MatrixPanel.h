#ifndef _ESP32_P3_RGB_64_32_MATRIX_PANEL
#define _ESP32_P3_RGB_64_32_MATRIX_PANEL

#include <vector>
#include <array>
#include "./Adafruit_GFX/Adafruit_GFX.h"
#include "mbed.h"

typedef uint8_t byte;
#define LOW 0
#define HIGH 1

class P3RGB64x32MatrixPanel : public Adafruit_GFX {
  public:
    P3RGB64x32MatrixPanel(PinName _pinR1, PinName _pinG1, PinName _pinB1, PinName _pinR2, PinName _pinG2, PinName _pinB2, PinName _pinCLK, PinName _pinLAT, PinName _pinOE, PinName _pinA, PinName _pinB, PinName _pinC, PinName _pinD, bool _doubleBuffer = false)
      : Adafruit_GFX(64, 32), pinR1(_pinR1), pinG1(_pinG1), pinB1(_pinB1), pinR2(_pinR2), pinG2(_pinG2), pinB2(_pinB2), pinCLK(_pinCLK), pinLAT(_pinLAT), pinOE(_pinOE), pinA(_pinA), pinB(_pinB), pinC(_pinC), pinD(_pinD), doubleBuffer(_doubleBuffer) {
      initMatrixBuff();
    }
    void begin(void);
    void stop(void);
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color);

    uint16_t color444(uint8_t r, uint8_t g, uint8_t b) { return ((r & 0xf) << 1) | ((uint16_t)(g & 0xf) << 6) | ((uint16_t)(b & 0xf) << 11); }
    uint16_t color555(uint8_t r, uint8_t g, uint8_t b) { return (r&0x1f) | ((uint16_t)(g & 0x1f) << 5) | ((uint16_t)(b & 0x1f) << 10); }
    uint16_t colorHSV(long hue, uint8_t sat, uint8_t val);

    void swapBuffer() {
      matrixbuff = drawBuffer();
    }
    uint16_t* matrixbuff;
    std::vector<std::array<uint16_t, 64*32>> _matrixbuff;

    void copyBuffer() {
      if (!doubleBuffer) return;
      if (matrixbuff == _matrixbuff[0].data())
        _matrixbuff[0] = _matrixbuff[1];
      else
        _matrixbuff[1] = _matrixbuff[0];
    }

  private:
    void initMatrixBuff() {
      _matrixbuff.resize(doubleBuffer ? 2 : 1);
      matrixbuff = _matrixbuff[0].data();
    }
    static void onTimer(void);
    void draw();

    uint16_t* drawBuffer() {
      if (!doubleBuffer) return _matrixbuff[0].data();
      if (matrixbuff == _matrixbuff[0].data())
        return _matrixbuff[1].data();
      else
        return _matrixbuff[0].data();
    }
    static Ticker timer;

    DigitalOut pinR1;
    DigitalOut pinG1;
    DigitalOut pinB1;
    DigitalOut pinR2;
    DigitalOut pinG2;
    DigitalOut pinB2;

    DigitalOut pinCLK;
    DigitalOut pinLAT;
    DigitalOut pinOE;

    DigitalOut pinA;
    DigitalOut pinB;
    DigitalOut pinC;
    DigitalOut pinD;

    bool doubleBuffer;
    static Semaphore timerSemaphore;
    static P3RGB64x32MatrixPanel *singleton;
};

#endif
