#pragma once
#include <Arduino.h>

class SLIDER {
  private:                   
    bool IS_CLICK     = false;
    bool IS_TOUCH     = true;
  public:
    SLIDER(uint16_t LINE_X1, uint16_t LINE_X2, uint16_t CIRCLE_Y, uint16_t CIRCLE_R)
    {
      this->LINE_X1     = LINE_X1;
      this->LINE_X2     = LINE_X2;
      this->CIRCLE_X    = LINE_X1;
      this->CIRCLE_Y    = CIRCLE_Y;
      this->CIRCLE_R    = CIRCLE_R;
    }

    uint16_t X, Y, LINE_X1, LINE_X2, CIRCLE_X, CIRCLE_Y, CIRCLE_R, SELECT;
 

  //Определяем адрес
  void MOVEMENT(bool TOUCHED)
  {
    if (TOUCHED && CIRCLE_X - CIRCLE_R <= X && X <= CIRCLE_X + CIRCLE_R && CIRCLE_Y - CIRCLE_R <= Y && Y <= CIRCLE_Y + CIRCLE_R)
      IS_CLICK = true;
      
    if (!TOUCHED)
      IS_CLICK  = false;
      
    if (TOUCHED && IS_CLICK && X > 0)
      if (X < LINE_X1)
        CIRCLE_X = LINE_X1;
      else if (X > LINE_X2)  
        CIRCLE_X = LINE_X2;
      else
        CIRCLE_X = X;
  }

  void MOVEMENT_CHECKED(bool TOUCHED, uint16_t X1, uint16_t X2, uint16_t X3, uint16_t X4)
  {
    if (TOUCHED && CIRCLE_X - CIRCLE_R <= X && X <= CIRCLE_X + CIRCLE_R && CIRCLE_Y - CIRCLE_R <= Y && Y <= CIRCLE_Y + CIRCLE_R)
      IS_CLICK = true;
      
    if (!TOUCHED)
      IS_CLICK  = false;
    
    if (TOUCHED && IS_CLICK && X > 0)
      if (X < X1 + (X2 - X1) / 2)
      {
        CIRCLE_X = X1;
        SELECT = 3;
      }
      else if (X1 + (X2 - X1) / 2 <= X && X < X2 + (X3 - X2) / 2)
      {
        CIRCLE_X = X2;
        SELECT = 2;
      }
      else if (X2 + (X3 - X2) / 2 <= X && X < X3 + (X4 - X3) / 2)
      {
        CIRCLE_X = X3;
        SELECT = 1;
      }
      else
      {
        CIRCLE_X = X4;
        SELECT = 0;
      }
  }
};
