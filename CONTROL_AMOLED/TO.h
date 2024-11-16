#pragma once
#include <Arduino.h>

class TO {
  private:
    uint32_t TIME_DELAY = 0;
    uint16_t SPEAK_NUMBER = 0;
  public:
    //аналогичен делай только не занисает процессорное время контролерра
    bool DELAY(uint32_t TIME, uint16_t NUMBER, bool ZERO = false)
    {
      if (millis() - TIME_DELAY >= TIME && SPEAK_NUMBER == NUMBER)
      {
          TIME_DELAY = millis();
          ++SPEAK_NUMBER;
          if (ZERO)
            SPEAK_NUMBER = 0;
          return true;
      } 
      return false;
    }

    //Считаем количество символов в числе
    uint8_t SIZE_NUMBER(int32_t NUMBER)
    {
      NUMBER = abs(NUMBER);
      if (NUMBER >= 1000000000)
        return 9;
      if (NUMBER >= 100000000)
        return 8;  
      if (NUMBER >= 10000000)
        return 7;
      if (NUMBER >= 1000000)
        return 6;
      if (NUMBER >= 100000)
        return 5;
      if (NUMBER >= 10000)
        return 4;
      if (NUMBER >= 1000)
        return 3;
      if (NUMBER >= 100)
        return 2;
      if (NUMBER >= 10)
        return 1;
      return 0; 
    }

    //Рассчитываем отступ
    String PADDING_SPACE(int32_t NUMBER)
    {
      uint8_t PADDING_NUMBER = 6 - (this->SIZE_NUMBER(NUMBER) + (NUMBER < 0 ? 2 : 1));
      if (PADDING_NUMBER == 5)
        return "  ";
      if (PADDING_NUMBER == 4)
        return "  ";
      if (PADDING_NUMBER == 3)
        return "  ";
      if (PADDING_NUMBER == 2)
        return " ";
      if (PADDING_NUMBER == 1)
        return " ";
      return "";
    }
  
    //Функция конвертирует цвет из RGB в RGB16
    uint16_t RGB_TO_RGB16(uint8_t R, uint8_t G, uint8_t B)                
    {
      return ((R & 0xF8)<<8) | ((G & 0xFC)<<3) | ((B & 0xF8)>>3);
    }
  
    //Функция расчёта палитры
    uint16_t PALETTE(uint16_t NUMBER) {
      if (NUMBER <= 255)
        return ((255 & 0xF8)<<8) | ((NUMBER & 0xFC)<<3) | ((0 & 0xF8)>>3);
      else if (NUMBER > 255 && NUMBER <= 510) 
        return ((510 - NUMBER & 0xF8)<<8) | ((255 & 0xFC)<<3) | ((0 & 0xF8)>>3);
      else if (NUMBER > 510 && NUMBER <= 765)
        return ((0 & 0xF8)<<8) | ((255 & 0xFC)<<3) | ((NUMBER - 510 & 0xF8)>>3);
      else if (NUMBER > 765 && NUMBER <= 1020)
        return ((0 & 0xF8)<<8) | ((1020 - NUMBER & 0xFC)<<3) | ((255 & 0xF8)>>3);
      else if (NUMBER > 1020 && NUMBER <= 1275)
        return ((NUMBER - 1020 & 0xF8)<<8) | ((0 & 0xFC)<<3) | ((255 & 0xF8)>>3);
      else if (NUMBER > 1275 && NUMBER <= 1530)
        return ((255 & 0xF8)<<8) | ((0 & 0xFC)<<3) | ((1530 - NUMBER & 0xF8)>>3);  
      return 0;
    }

    //Функция расчёта палитры для RGB светодиода
    static uint32_t RGB_LED(uint16_t NUMBER) {
      if (NUMBER <= 255)
        return ((uint32_t)255 << 16) | ((uint32_t)NUMBER << 8) | 0;
      else if (NUMBER > 255 && NUMBER <= 510) 
        return ((uint32_t)(510 - NUMBER) << 16) | ((uint32_t)255 << 8) | 0;
      else if (NUMBER > 510 && NUMBER <= 765)
        return ((uint32_t)0 << 16) | ((uint32_t)255 << 8) | NUMBER - 510;
      else if (NUMBER > 765 && NUMBER <= 1020)
        return ((uint32_t)0 << 16) | ((uint32_t)(1020 - NUMBER) << 8) | 255;
      else if (NUMBER > 1020 && NUMBER <= 1275)
        return ((uint32_t)(NUMBER - 1020) << 16) | ((uint32_t)0 << 8) | 255;
      else if (NUMBER > 1275 && NUMBER <= 1530)
        return ((uint32_t)255 << 16) | ((uint32_t)0 << 8) | (1530 - NUMBER); 
      return 0;
    }
  
  
    //Функция затирает предыдущие показания пробелами 
    char* DISPLAY_TEXT(float DATA, uint8_t COUNT, uint8_t FLOAT)          
    {
      static char DATA_RESULT[20];                                        //Объявляем переменную
      char DATA_DISPLAY[20];                                              //Объявляем переменную
      dtostrf(DATA, COUNT, FLOAT, DATA_DISPLAY);                          //Конвертируем показания в привычные глазу данные для дальнейшего вывода на экран
      uint8_t LEN = COUNT - (strlen(DATA_DISPLAY) - 1);                   //Узнаём длину полученных данных
      for(uint8_t i = 0; i < LEN; ++i)                                    //Вычисляем сколько пробелов не хватает
        strcpy(DATA_RESULT, " ");                                         //Создаём строку из недостающих пробелов
      strcat(DATA_RESULT, DATA_DISPLAY);                                  //Добавляем недостающие пробелы
      return DATA_RESULT;                                                 //Отдаём результат
    }

 
};
