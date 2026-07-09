#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "drones.h"

class DisplayHandler {

    public:
        DisplayHandler();

        void init();

        void info(const char * text);

        void new_detection(const id_data *UAV);

        void idle_update(int cur_detections, int total_detections);

        void service();

    private:
        unsigned long int last_updated;
        const int min_display = 1000;
        


};




#endif