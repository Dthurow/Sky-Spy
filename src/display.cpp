

#include "display.h"
#include <esp_timer.h>
#include "drones.h"

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

DisplayHandler::DisplayHandler(){};

void DisplayHandler::init()
{
    power_save_en = false;
    pinMode(TFT_BACKLITE, OUTPUT);
    pinMode(TFT_I2C_POWER, OUTPUT);

    // turn on backlite
    digitalWrite(TFT_BACKLITE, HIGH);

    // turn on the TFT / I2C power supply
    digitalWrite(TFT_I2C_POWER, HIGH);
    delay(10);


    // initialize TFT
    tft.init(135, 240); // Init ST7789 240x135
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(0,0);

    tft.println("Initializing");


}

void DisplayHandler::scrolling_text(const char * text)
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(0,0);
    const char * line = text;
    const char * top_of_screen = text;
    //max width/height calculated based on text size
    // and screen size
    int maxchars_width = tft.width() / (18);
    int maxchars_height = tft.height() / 24;

    int curlines = 0;
    int loopcnt = 0;
    //max print out 100 lines
    while (loopcnt < 100){
        
        if (curlines >= maxchars_height){
        //need to scroll
        delay(2000); //pause to let user view screen
        top_of_screen += maxchars_width; //update so the top of the screen is one line more
        line = top_of_screen; //the next line to print will be from the top of the screen again
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(0,0);
        curlines = 0;
        
        }


        int printedsize = tft.printf("%.*s", maxchars_width, line);
        if (printedsize < maxchars_width){
        break; //finished the text
        }
        line += maxchars_width;
        curlines++;
        tft.setCursor(0, curlines * 24);
        
        loopcnt++;
    }
    last_updated = millis();
}

void DisplayHandler::power_saver(bool enable){
    if (!power_save_en && enable){
         // turn off backlite
        digitalWrite(TFT_BACKLITE, LOW);

        // turn off the TFT / I2C power supply
        digitalWrite(TFT_I2C_POWER, LOW);
        delay(10);
    }
    else if (power_save_en && !enable){
         // turn on backlite
        digitalWrite(TFT_BACKLITE, HIGH);

        // turn on the TFT / I2C power supply
        digitalWrite(TFT_I2C_POWER, HIGH);
        delay(10);
        
    }
    power_save_en = enable;
}

void DisplayHandler::info(const char * text)
{
    unsigned long curtime = millis();
    if (curtime - last_updated < min_display){
        return;
    }
    tft.setTextWrap(true);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.print(text);
    last_updated = curtime;
}

void DisplayHandler::idle_update(int cur_detections, int total_detections)
{
    unsigned long curtime = millis();

    
    tft.setTextWrap(true);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.printf("In Range: %d\nTotal: %d\nScanning...", cur_detections, total_detections);
    last_updated = curtime;
    last_active_detection_cnt = cur_detections;
    last_total_cnt = total_detections;


    
}

void DisplayHandler::detection(const id_data *UAV)
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.setCursor(0, 0);

    char mac_str[18];
    snprintf(mac_str, sizeof(mac_str), "%02x:%02x:%02x:%02x:%02x:%02x",
           UAV->mac[0], UAV->mac[1], UAV->mac[2],
           UAV->mac[3], UAV->mac[4], UAV->mac[5]);


    char msg[256];
    snprintf(msg, sizeof(msg),
        "mac:\n  %s\nrssi:%d\nGPS:\n  %.6f,%.6f\naltitude:%dm",
        mac_str, UAV->rssi, UAV->lat_d, UAV->long_d, UAV->altitude_msl
        );

    tft.print(msg);
    last_updated = millis();

}