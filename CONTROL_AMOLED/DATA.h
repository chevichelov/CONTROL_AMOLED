#pragma once
#include <Arduino.h>

class DATA {
  public:
    byte SIGNAl = 0;                //Сигнал для зумера

    uint8_t BUF[255];               //Буфер модуля распознованияч речи

    bool STOP_TIME = false;         //Остановка осцилографа
    
    uint32_t HZ = 0;                //Частота измерения
    
    uint32_t HZ_STOP = 0;           //Сохраняем частоту
    
    uint32_t TIME_TIK = 0;          //Сохраняем время последнего прерывания в микросекундах

    uint32_t  TIME = 0;             //Задержка для плавного изменения цифр

    uint32_t  TIME_SPEEK = 0;       //Время говорить

    uint8_t BATTERY_VALUE = 0;      //Заряд батареи    
    
    uint32_t TIME_BATTERY = 0;      //Время проверки батареи
    
    uint8_t SELECT_DISPLAY = 0;     //Выбор режима
     
    bool DISPLAY_ONE = true;        //Выполнить один раз
    
    bool PRESS = false;             //Проверяем удерживается ли дисплей 
    
    int16_t NUMBER_LAST = 0;        //Последний выбранный режим

    bool BOOZER = true;             //Включение/выключение виброматора/пищалки

    uint32_t SET_DIVIDER = 0;       //Рассчитываем шкалу для графика
    
    uint32_t MAX_GRAPH = 0;         //Максимальная величина графика
    
    uint32_t MIN_GRAPH = 0;         //Минимальная величина графика
    
    bool STOP_PRESS = false;        //Нажат стоп

    bool WIFI_PRESS = false;        //Нажат WI-FI

    bool QUEUE = false;             //Очередь расчётов

    bool SPEEK_DATA = false;        //Воспроизводим голосом показания

    float VALUE = 0;                //Значение для спикера 
    
    String NAME = "";               //Тип для спикера

    String RESULT = "";             //Данные для WEB-интерфейса

    bool REQUEST  = false;          //Запрос делаем

    uint32_t REQUEST_TIME = 0;      //Время запроса

    uint8_t DELAY = 255;            //Скважность для генератора

    bool YOU_PRESS = false;        //Нажата кнопка поиска
    
};
