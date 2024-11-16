#pragma once
#include <Arduino.h>

//Класс для сохранения данных в EEPROM
class SAVE {
  public:
    uint8_t DELAY              = 255;    //Скважность для генератора

    uint16_t SLIDER_PALETTE    = 150;    //
    
    uint16_t SLIDER_BRIGHTNESS = 150;    //

    uint16_t SLIDER_SOUND      = 150;    //
    
    uint16_t SLIDER_DISPLAY    = 150;    //

    bool WIFI                 = false;   //
};
