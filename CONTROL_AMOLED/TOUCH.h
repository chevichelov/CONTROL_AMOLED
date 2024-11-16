#pragma once
#include <Arduino.h>

class TOUCH {
  private:
    uint16_t LENGTH   = 0;                //Длина в пикселях для свайпа
    uint8_t COUNT     = 0;                //Количество дисплеев
    bool IS_CLICK     = true;
    bool IS_TOUCH     = true;
    int16_t X1, Y1;
  public:
    TOUCH(uint8_t COUNT, uint16_t LENGTH) 
    {
      this->COUNT   = COUNT;
      this->LENGTH  = LENGTH;
    }

 int16_t X, Y, NUMBER, TOP;
 

  //Определяем адрес
  void SCREEN(bool TOUCHED)
  {
    if (TOUCHED && !IS_CLICK && IS_TOUCH)
    {
      if (TOP == 0 && X1 - X > LENGTH && (486 <= X1 && X1 <= 536))
      {
        ++NUMBER;
        if (NUMBER > COUNT)
          NUMBER = 0;
        IS_CLICK = true;
        IS_TOUCH = false;
      }
      if (TOP == 0 && X - X1 > LENGTH && (0 <= X1 && X1 <= 50))
      {
          --NUMBER;
          if (NUMBER < 0)
            NUMBER = COUNT;
          IS_CLICK = true;
          IS_TOUCH = false;
      }

      
      if (Y - Y1 > LENGTH && (0 <= Y1 && Y1 <= 50))
      {
          if (TOP == 0)
            TOP = 1;
          if (TOP == 2)
            TOP = 0;
          IS_CLICK = true;
          IS_TOUCH = false;
      }
      if (Y1 - Y > LENGTH && (190 <= Y1 && Y1 <= 240))
      {
          if (TOP == 0)
            TOP = 2;
          if (TOP == 1)
            TOP = 0;
          IS_CLICK = true;
          IS_TOUCH = false;
      }
      
    }
    if (!TOUCHED)
    {
      Y1        = Y;
      X1        = X;
      IS_CLICK  = true;
      IS_TOUCH  = true;
    }
    if (TOUCHED && IS_CLICK)
    {
      X1        = X;
      Y1        = Y;
      IS_CLICK  = false;
    }
  }
};
