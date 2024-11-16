#pragma once
#include <Arduino.h>

//Класс для работы с кнопками
class BUTTON {
  private:
    uint32_t TIME   = 0;
  public: 
    int16_t X       = 0;
    int16_t Y       = 0;
    int16_t WIDTH   = 0;
    int16_t HEIGHT  = 0;
     
    bool IS_PRESSED  = false;

    //Инициализируем кнопку
    BUTTON(int16_t X, int16_t Y, int16_t WIDTH, int16_t HEIGHT)
    {
      this->X             = X;
      this->Y             = Y;
      this->HEIGHT        = HEIGHT;
      this->WIDTH         = WIDTH;
    }

    //Проверяем нажата ли кнопка
    bool IS_PRESS(int16_t &x, int16_t &y) 
    {
        bool _IS_PRESSED = false;
        if (millis() - TIME >= 400 && x >= X && x <= X + WIDTH && y >= Y && y <= Y + HEIGHT)
        {
          TIME = millis();
          if(IS_PRESSED)
            IS_PRESSED = false;
          else
            IS_PRESSED = true;
          _IS_PRESSED = true;
        }
        return _IS_PRESSED;
    }
};
