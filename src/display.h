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

        void detection(const id_data *UAV);

        void idle_update(int cur_detections, int total_detections);

        void service();

    protected:
        void power_saver(bool enable);
        void scrolling_text(const char * text);

    private:
        unsigned long int last_updated;
        const int min_display = 1000;
        //intialized to high numbers so initial display will work
        int last_active_detection_cnt = 500;
        int last_total_cnt = 500;
        bool power_save_en;
        


};




#endif