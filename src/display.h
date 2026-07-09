#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

class DisplayHandler {

    public:
        DisplayHandler();

        void init();

        void info(const char * text);

        void new_detection();

        void service();


};




#endif