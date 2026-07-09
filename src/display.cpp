

#include "display.h"

#include "drones.h"

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

DisplayHandler::DisplayHandler(){};

void DisplayHandler::init()
{

    // turn on backlite
    pinMode(TFT_BACKLITE, OUTPUT);
    digitalWrite(TFT_BACKLITE, HIGH);

    // turn on the TFT / I2C power supply
    pinMode(TFT_I2C_POWER, OUTPUT);
    digitalWrite(TFT_I2C_POWER, HIGH);
    delay(10);


    // initialize TFT
    tft.init(135, 240); // Init ST7789 240x135
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(0,0);

    const char * text = "Initialized, will scan for remoteID drones within roughly 500 feet";
    const char * line = text;
    const char * top_of_screen = text;
    int maxchars_width = tft.width() / (18);
    int maxchars_height = tft.height() / 24;

    int curlines = 0;
    int loopcnt = 0;
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

}


void DisplayHandler::info(const char * text)
{
    tft.setTextWrap(true);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.print(text);
}