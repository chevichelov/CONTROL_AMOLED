#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TFT_eSPI.h>
#include <LilyGo_AMOLED.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>
#include <VoiceRecognitionV3.h>  
#include <EEPROM.h>
#include "WEBSERVER.h"      
#include "TOUCH.h"
#include "SLIDER.h"
#include "BUTTON.h"
#include "TO.h"
#include "DATA.h"
#include "SAVE.h"
#include "ICONS.h"
#include "FONT.h"
#include "FONT_TEXT.h"

#define BUZZER_PIN 44
#define LED_PIN 43
#define PLUS_PIN 39

#define MAX_VOLTAGE 4200
#define MIN_VOLTAGE 2700

#define COUNT_VALUES 493

uint32_t  VALUES[COUNT_VALUES];

AsyncWebServer SERVER(80);
LilyGo_Class amoled;
VR MICROPHONE;
TOUCH TOUCH(5, 100);                                  //Количество дисплеев, Длина в пикселях для свайпа
SLIDER SLIDER_PALETTE(150, 405, 30, 30);
SLIDER SLIDER_BRIGHTNESS(150, 405, 110, 30);
SLIDER SLIDER_FLASHLIGHT(40, 485, 180, 30);

SLIDER SLIDER_DISPLAY(150, 405, 110, 30);
SLIDER SLIDER_SOUND(150, 405, 30, 30);

SLIDER SLIDER_GENERATE(150, 405, 180, 30);
DATA DATA;
TO TO;
SAVE SAVE;

BUTTON GRAPH_BUTTON(50, 50, 436, 140);
BUTTON WIFI_BUTTON(80, 150, 380, 240);
BUTTON YOU_BUTTON(80, 60, 376, 120);

HardwareSerial SERIAL_3(2);
DFRobotDFPlayerMini PLAYER; 

#define WIDTH  536 //amoled.width()
#define HEIGHT 240 //amoled.height()

#define WIDTH_PADDING 43
#define HEIGHT_PADDING 40

#define MAX_DIVIDER 9     //uint16_t MAX_DIVIDER = HEIGHT / 25
#define HEIGHT_BOTTOM 235 //uint16_t HEIGHT_BOTTOM = HEIGHT - 5

#define EEPROM_LIMIT 300

TFT_eSPI TFT              = TFT_eSPI();
TFT_eSprite MAIN          = TFT_eSprite(&TFT);
Adafruit_NeoPixel RGB_LED = Adafruit_NeoPixel(3, LED_PIN, NEO_GRB + NEO_KHZ800);

IPAddress IP(192, 168, 0, 1);
IPAddress GATEWAY(192, 168, 0, 0);
IPAddress SUBNET(255, 255, 255, 0);

/***************************************************************/
//Прерывание
/***************************************************************/
void IRAM_ATTR ISR()
{
   DATA.HZ = (1000000.0 / (micros() - DATA.TIME_TIK)); //Измеряем частоту
   DATA.TIME_TIK = micros();
}


/***************************************************************/
//Получаем напряжение батареи в процентах
/***************************************************************/
void BATTERY(bool FIRST)
{
  if (millis() - DATA.TIME_BATTERY < 60000 && !FIRST)
    return;
  DATA.BATTERY_VALUE  = map(amoled.getBattVoltage(), MAX_VOLTAGE, MIN_VOLTAGE, 0, 26);
  DATA.TIME_BATTERY   = millis();
  DATA.DISPLAY_ONE    = false;
}

//Получаем данные из EEPROM
void EEPROM_GET()                                                                       
{
  EEPROM.begin(EEPROM_LIMIT);
  EEPROM.get(11, SAVE);
  EEPROM.end();
}

//Сохраняем данные в EEPROM
void EEPROM_SAVE()                                                                      
{
  DATA.REQUEST = false;
  EEPROM.begin(EEPROM_LIMIT);
  EEPROM.put(11, SAVE);
  EEPROM.commit();
  EEPROM.end();
}




void setup(void)
{
    Serial.begin(115200);
    attachInterrupt(12, ISR, FALLING);
    attachInterrupt(11, ISR, FALLING);

    pinMode(42, OUTPUT);
    digitalWrite(42, 0);
    analogWrite(PLUS_PIN, 0);

    amoled.beginAMOLED_191();
    MAIN.createSprite(WIDTH,HEIGHT);
    MAIN.loadFont(FONT_TEXT);
    MAIN.drawString("youtube.com/chevichelov", WIDTH / 2 - 150, HEIGHT / 2 - 10);
    MAIN.unloadFont();
    amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
    
    RGB_LED.begin();                      //Инициализируем ленту.
    RGB_LED.clear();
    
    MICROPHONE.begin(9600);

    SERIAL_3.begin(9600, SERIAL_8N1, 41, 40);
    PLAYER.begin(SERIAL_3);
    PLAYER.volume(30); 
    
    if(MICROPHONE.clear() == 0)
      Serial.println("Recognizer cleared.");
    else{
      Serial.println("Not find VoiceRecognitionModule.");
      Serial.println("Please check connection and restart Arduino.");
     // while(1);
    }

    if(MICROPHONE.load((uint8_t)0) >= 0)
      Serial.println("0 loaded");
    if(MICROPHONE.load((uint8_t)1) >= 0)
      Serial.println("1 loaded");
    if(MICROPHONE.load((uint8_t)2) >= 0)
      Serial.println("2 loaded");
    if(MICROPHONE.load((uint8_t)3) >= 0)
      Serial.println("3 loaded");
    if(MICROPHONE.load((uint8_t)4) >= 0)
      Serial.println("4 loaded");
    if(MICROPHONE.load((uint8_t)5) >= 0)
      Serial.println("5 loaded");
    
    amoled.setHomeButtonCallback([](void *ptr) {
        static uint32_t TIME_BUTTON = 0;
        if (millis() > TIME_BUTTON) {
          amoled.setRotation(amoled.getRotation() == 2 ? 0 : 2);
        }
        TIME_BUTTON = millis() + 100;
    }, NULL); 

    SLIDER_FLASHLIGHT.CIRCLE_X  = 485;
    
    EEPROM_GET();                                                       //При первой прошивке закомментировать
    DATA.DELAY                  = SAVE.DELAY;
    SLIDER_PALETTE.CIRCLE_X     = SAVE.SLIDER_PALETTE;
    SLIDER_BRIGHTNESS.CIRCLE_X  = SAVE.SLIDER_BRIGHTNESS;
    SLIDER_SOUND.CIRCLE_X       = SAVE.SLIDER_SOUND;
    SLIDER_DISPLAY.CIRCLE_X     = SAVE.SLIDER_DISPLAY;
    amoled.setBrightness(255 - (SLIDER_DISPLAY.CIRCLE_X - SLIDER_DISPLAY.LINE_X1));

    DATA.WIFI_PRESS             = SAVE.WIFI;
    

    if (DATA.WIFI_PRESS)
    {
      WiFi.softAP("youtube_com_chevichelov", "");
      WiFi.softAPConfig(IP, GATEWAY, SUBNET);
      
      SERVER.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", INDEX_HTML);
      });
      SERVER.on("/tester", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"TESTER\", \"main\": \""+DATA.RESULT+"\"}");
        TOUCH.NUMBER = 0;
      });
      SERVER.on("/measurement", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"MEASUREMENT\", \"main\": \""+DATA.RESULT+"\"}");
        TOUCH.NUMBER = 1;
      });
      SERVER.on("/oscilloscope", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"oscilloscope\", \"main\": [" + FLOAT_ARRAY_TO_STRING() + "]}");
        TOUCH.NUMBER = 2;
      });
      SERVER.on("/voltmetr", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"VOLTMETR\", \"main\": \""+DATA.RESULT+"\"}");
        TOUCH.NUMBER = 3;
      });
      SERVER.on("/ohmmeter", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"OHMMETER\", \"main\": \""+DATA.RESULT+"\"}");
        TOUCH.NUMBER = 4;
      });
      SERVER.on("/generator", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "{\"head\": \"generator\",\"main\": "+DATA.RESULT+"}");
        TOUCH.NUMBER = 5;
      });
      SERVER.on("/mode", HTTP_GET, [](AsyncWebServerRequest *request){
        String LINK = "tester";
        if (TOUCH.NUMBER == 0)
          LINK = "tester";
        else if (TOUCH.NUMBER == 1)
          LINK = "measurement";
        else if (TOUCH.NUMBER == 2)
          LINK = "oscilloscope";
        else if (TOUCH.NUMBER == 3)
          LINK = "voltmetr";
        else if (TOUCH.NUMBER == 4)
          LINK = "ohmmeter";
        else if (TOUCH.NUMBER == 5)
          LINK = "generator"; 
        request->send(200, "text/html", LINK);
      });
      SERVER.onNotFound([](AsyncWebServerRequest *request){
        AsyncWebServerResponse *response = request->beginResponse(302, "text/html", "");
          response->addHeader("Location", "http://192.168.0.1/");
          response->addHeader("Content-Type", "text/html; charset=UTF-8");
          response->addHeader("Content-Length", "0");
          request->send(response);
      });
      SERVER.begin();
    } 
}


String FLOAT_ARRAY_TO_STRING()
{
  String RESULT = "";
  for(int i = 0; i < COUNT_VALUES; ++i)
  {
    RESULT += String(VALUES[i]) + ",";  
  } 
  return RESULT.substring(0, RESULT.length() - 1);
}


/***************************************************************/
//Измеряем напряжение на пине
/***************************************************************/
float GET_VOLT(uint8_t PIN)
{
  int32_t VOLTS = 0;
  for(uint8_t i = 0; i <= 4; ++i)
    VOLTS += analogReadMilliVolts(PIN);
  return VOLTS / 5000.0f;
}

/***************************************************************/
//sigtrain 0 ZERO
//sigtrain 1 DATA
//sigtrain 2 HZ
//sigtrain 3 VOLT
//sigtrain 4 OM
//sigtrain 5 YOU //ТЫ ГДЕ
//sigtrain 6 
//sigtrain 7
//sigtrain 8 
/***************************************************************/
void SPEAK(float VALUE, String NAME)
{ 
  DATA.SPEEK_DATA = false;
  if (NAME == "nan")
  {
    PLAYER.playMp3Folder(910);
    delay(2500);
    return;
  }
  if (VALUE < 0)
  {
    VALUE = VALUE * -1;
    PLAYER.playMp3Folder(909);
    delay(1700);
  }
  VALUE = round(VALUE * 100) / 100;
  if (VALUE >= 100)
  { 
    PLAYER.playMp3Folder(((int)(VALUE / 100)) * 100);
    delay(2500); 
    if ((((int)VALUE) % 100) != 0 )
    {
      PLAYER.playMp3Folder(((int)VALUE) % 100);
      delay(2500); 
    }
  } 
  else
  {
    PLAYER.playMp3Folder((int)VALUE);
    delay(2500);
  }
  if ((VALUE - floor(VALUE)) * 100 > 0 && NAME != "om" && NAME != "hz")
  {
    PLAYER.playMp3Folder(901);
    delay(1700);
    if ((int)((VALUE - (int)VALUE) * 100) < 10)
    {
      PLAYER.playMp3Folder(0);
      delay(2500);
    }
    PLAYER.playMp3Folder((int)((VALUE - (int)VALUE) * 100));
    delay(2500);
  }
  if (NAME == "om")
  {
    PLAYER.playMp3Folder(902);
    delay(2500);
  } 
  else if (NAME == "kom")
  {
    PLAYER.playMp3Folder(903);
    delay(2500);
  }
  else if (NAME == "mom")
  {
    PLAYER.playMp3Folder(904);
    delay(2500);
  }
  else if (NAME == "hz")
  {
    PLAYER.playMp3Folder(905);
    delay(2500);
  }
  else if (NAME == "khz")
  {
    PLAYER.playMp3Folder(906);
    delay(2500);
  }
  else if (NAME == "mhz")
  {
    PLAYER.playMp3Folder(907);
    delay(2500);
  }
  else if (NAME == "v")
  {
    PLAYER.playMp3Folder(908);
    delay(2500);
  }
}

void YOU(bool TOUCHED, int16_t X, int16_t Y)
{
  if (TOUCHED && YOU_BUTTON.IS_PRESS(X, Y))
  {
    DATA.YOU_PRESS  = false;
    TOUCH.TOP       = 0;
    RGB_LED.clear();
  }
  if (DATA.YOU_PRESS)
  {
    digitalWrite(42, 0);
    analogWrite(BUZZER_PIN, 255);
    RGB_LED.setPixelColor(1, RGB_LED.Color(255, 255, 255));
    RGB_LED.show();
    RGB_LED.setPixelColor(2, RGB_LED.Color(255, 255, 255));
    RGB_LED.show();
  }
  MAIN.fillSprite(TFT_BLACK);  
  MAIN.loadFont(FONT);
  MAIN.fillRect(80, 60, 376, 120, TO.RGB_TO_RGB16(152, 251, 152));
  MAIN.drawString("I'M HERE", WIDTH / 2 - 160, 70);
  MAIN.unloadFont();
  amoled.pushColors(0, 0, WIDTH, HEIGHT,(uint16_t *)MAIN.getPointer());
}

/***************************************************************/
//Выводим значение напряжения на экран
/***************************************************************/
float VOLT(TFT_eSprite *MAIN, char PARAMETER)
{
  float VOLT = 0;
  
  if (PARAMETER == 'L')
  {
    pinMode(45, INPUT);           //Пин на вход
    pinMode(46, OUTPUT);          //Пин на выход
    digitalWrite(46, 0);          
    VOLT = GET_VOLT(10) * 20.31;  //(5.06 + 5.06) / 0.510
  } 
  else if (PARAMETER == 'R')
  {
    pinMode(46, INPUT);           //Пин на вход
    pinMode(45, OUTPUT);          //Пин на выход
    digitalWrite(45, 0);          
    VOLT = GET_VOLT(1) * 19.84;    //(5.06 + 5.06) / 0.510
  }
  if (VOLT > 0.1)
  {
    if (!DATA.BOOZER)
    {
      analogWrite(BUZZER_PIN, 255 - (SLIDER_SOUND.CIRCLE_X - SLIDER_SOUND.LINE_X1));
      DATA.BOOZER = true;
    }
    else
    {
      analogWrite(BUZZER_PIN, 0);
      DATA.BOOZER = false;
    }
    if (PARAMETER == 'L')
    {
      MAIN->drawString(String(VOLT) + "V", WIDTH / 2 - 100, HEIGHT / 2 - 50);
      DATA.RESULT = String(VOLT) + "V";
      DATA.VALUE = VOLT;
      DATA.NAME = "v";
    }
    else if (PARAMETER == 'R')
    {
      MAIN->drawString("-" + String(VOLT) + "V", WIDTH / 2 - 150, HEIGHT / 2 - 50);
      DATA.RESULT = "-" + String(VOLT) + "V";
      DATA.VALUE = VOLT * -1;
      DATA.NAME = "v";
    }
    if (VOLT > 11)
      RGB_LED.setPixelColor(0, RGB_LED.Color(255, 0, 0));
    else
      RGB_LED.setPixelColor(0, RGB_LED.Color(255, 128, 0));
    RGB_LED.show();
    DATA.SELECT_DISPLAY = 1;
  }
  else
  {
    DATA.SELECT_DISPLAY = 0;
    DATA.RESULT = "0.00V";
  }
  return VOLT;
}


/***************************************************************/
//Выводим значение сопротивления на экран
/***************************************************************/
void OHMMETER(TFT_eSprite *MAIN)
{
  pinMode(46, OUTPUT);              //Пин выход
  pinMode(45, OUTPUT);              //Пин выход
  digitalWrite(46, 1);
  digitalWrite(45, 0);
  
  float R1 =  GET_VOLT(10);         //Измеряем напряжение на верхнем конце делителя

  float R2 =  GET_VOLT(14);         //Измеряем напряжение на верхнем щупе
  
  float R3 =  GET_VOLT(13);         //Измеряем напряжение на нижнем щупе
  
  R1 = R1 - R3;                     //Полное напряжение на делителе
  R2 = R2 - R3;                     //Напряжение на измеряемом резисторе

  float R = (R2 * 5060)/(R1 - R2);  //Сопротивление измеряемого резистора
  if (R >= 15000 && R < 25000)
    R = R * 1.1;
  else if (R >= 25000 && R < 35000)
    R = R * 1.2;
  else if (R >= 35000 && R < 45000)
    R = R * 1.3;
  else if (R >= 45000 && R < 55000)
    R = R * 1.5;
  else if (R >= 55000 && R < 65000)
    R = R * 1.55;
  else if (R > 65000)
    R = R * 1.6;
    
  if (R < 0)
    R = 0;
  if (R <= 120000)
  { 
    analogWrite(BUZZER_PIN, 255 - (SLIDER_SOUND.CIRCLE_X - SLIDER_SOUND.LINE_X1));
    if (R > 1000)
    { 
      float R_kOm = R / 1000.00f;
      MAIN->drawString(String(R_kOm) + " kOm", WIDTH / 2 - (R_kOm > 100 ? 200 : R_kOm > 10 ? 150 : 100), HEIGHT / 2 - 50);
      DATA.RESULT = String(R_kOm) + " kOm";
      DATA.VALUE = R_kOm;
      DATA.NAME = "kom";
    }
    else
    {
      MAIN->drawString(String((int32_t)R) + " Om", WIDTH / 2 - 100, HEIGHT / 2 - 50);
      DATA.RESULT = String((int32_t)R) + " Om";
      DATA.VALUE = R;
      DATA.NAME = "om";
    }
    RGB_LED.setPixelColor(0, RGB_LED.Color(0, 255, 0));
    RGB_LED.show();
    DATA.SELECT_DISPLAY = 3;
  }
  else
  {
    analogWrite(BUZZER_PIN, 0);
    DATA.VALUE = 0;
    DATA.NAME = "nan";
    DATA.RESULT = "????";
    MAIN->drawString("????", WIDTH / 2 - 100, HEIGHT / 2 - 50);
    RGB_LED.setPixelColor(0, RGB_LED.Color(0, 0, 0));
    RGB_LED.show();
    DATA.SELECT_DISPLAY = 0;
  }
}


/***************************************************************/
//Выводим значение частоты на экран
/***************************************************************/
void HERTZ(TFT_eSprite *MAIN, char PARAMETER)
{
  if (PARAMETER == 'L')
  {
    pinMode(45, INPUT);         //Пин вход
    pinMode(46, OUTPUT);        //Пин выход
    digitalWrite(46,0);
    digitalWrite(45,0);
  } 
  else if (PARAMETER == 'R')
  {
    pinMode(46, INPUT);         //Пин вход
    pinMode(45, OUTPUT);        //Пин выход
    digitalWrite(46,0);
    digitalWrite(45,0);         
  }
  if (DATA.HZ > 0)
  {
    if (DATA.HZ >= 1000000)
    {
      MAIN->drawString(String(DATA.HZ / 1000000.00f) + " MHz", WIDTH / 2 - 200, HEIGHT / 2 - 50);
      DATA.RESULT = String(DATA.HZ / 1000000.00f) + " MHz";
      DATA.VALUE = DATA.HZ / 1000000.00f;
      DATA.NAME = "mhz";
    }
    else if (DATA.HZ >= 1000)
    {
      MAIN->drawString(String(DATA.HZ / 1000.00f) + " kHz", WIDTH / 2 - 200, HEIGHT / 2 - 50);
      DATA.RESULT = String(DATA.HZ / 1000.00f) + " kHz";
      DATA.VALUE = DATA.HZ / 1000.00f;
      DATA.NAME = "khz";
    }
    else
    {
      MAIN->drawString(String(DATA.HZ) + " Hz", WIDTH / 2 - 100, HEIGHT / 2 - 50);
      DATA.RESULT = String(DATA.HZ) + " Hz";
      DATA.VALUE = DATA.HZ;
      DATA.NAME = "hz";
    }
    RGB_LED.setPixelColor(0, RGB_LED.Color(0, 0, 255));
    RGB_LED.show();

    if (DATA.SIGNAl % 2 == 0 && DATA.SIGNAl != 4)
    {
      analogWrite(BUZZER_PIN, 255 - (SLIDER_SOUND.CIRCLE_X - SLIDER_SOUND.LINE_X1));
    }
    else
    {
      analogWrite(BUZZER_PIN, 0);
    }
    ++DATA.SIGNAl;
    if (DATA.SIGNAl == 6)
      DATA.SIGNAl = 0;
    DATA.SELECT_DISPLAY = 1;
  }
  else
    DATA.SELECT_DISPLAY = 0;
}


/***************************************************************/
//Режим тестера
/***************************************************************/
void TESTER()
{ 
  if (millis() - DATA.TIME <= 200)  //Добавляем задержку в 200 миллисекунд
    return;
  DATA.TIME = millis(); 

  MAIN.fillSprite(TFT_BLACK);

  BATTERY(DATA.DISPLAY_ONE);  
  MAIN.drawRect(501, 0, 30, 15, TFT_WHITE);
  MAIN.fillRect(496, 5, 5, 5, TFT_WHITE);
  MAIN.fillRect(502 + DATA.BATTERY_VALUE, 1, 28 - DATA.BATTERY_VALUE, 13, TO.RGB_TO_RGB16(152, 251, 152));

  MAIN.loadFont(FONT_TEXT);
  MAIN.drawString("TESTER", WIDTH / 2 - 50, 10);
  MAIN.unloadFont();
  
  MAIN.fillCircle(20, HEIGHT - 20, 15, TFT_WHITE);   
  MAIN.drawCircle(60, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(100, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(140, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(180, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(220, HEIGHT - 20, 15, TFT_WHITE);
  
  MAIN.loadFont(FONT);
  pinMode(46, INPUT);     //Пин вход
  pinMode(45, INPUT);     //Пин вход

    VOLT(&MAIN, 'L');
  if (DATA.SELECT_DISPLAY == 0)
    VOLT(&MAIN, 'R');
  if (DATA.SELECT_DISPLAY == 0)
    OHMMETER(&MAIN);
  
  MAIN.unloadFont(); 
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
}


/***************************************************************/
//Режим частомера
/***************************************************************/
void MEASUREMENT()
{
  MAIN.fillSprite(TFT_BLACK);

  BATTERY(DATA.DISPLAY_ONE);
  MAIN.drawRect(501, 0, 30, 15, TFT_WHITE);
  MAIN.fillRect(496, 5, 5, 5, TFT_WHITE);
  MAIN.fillRect(502 + DATA.BATTERY_VALUE, 1, 28 - DATA.BATTERY_VALUE, 13, TO.RGB_TO_RGB16(152, 251, 152));
   
  
  MAIN.loadFont(FONT_TEXT);
  MAIN.drawString("FREQUENCY METER", WIDTH / 2 - 100, 10);
  MAIN.unloadFont();
  
  MAIN.drawCircle(20, HEIGHT - 20, 15, TFT_WHITE);   
  MAIN.fillCircle(60, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(100, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(140, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(180, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(220, HEIGHT - 20, 15, TFT_WHITE);
  
  MAIN.loadFont(FONT);
    HERTZ(&MAIN, 'L');
  if (DATA.SELECT_DISPLAY == 0)  
    HERTZ(&MAIN, 'R');

  if (DATA.HZ == 0)
  {
    MAIN.drawString("0 Hz", WIDTH / 2 - 100, HEIGHT / 2 - 50);
    DATA.RESULT = "0 Hz";
    DATA.VALUE = 0;
    DATA.NAME = "hz";
  }
  MAIN.unloadFont(); 
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
  if (micros() - DATA.TIME_TIK >= 500000)
  {
    DATA.HZ = 0;
    analogWrite(BUZZER_PIN, 0);
    RGB_LED.setPixelColor(0, RGB_LED.Color(0, 0, 0));
    RGB_LED.show();
  }
}


/***************************************************************/
//Получаем график измерение для графика
/***************************************************************/
void SIZE_SIGNAL(uint8_t PIN, bool STOP_TIME = false)
{
  if (STOP_TIME)
    return;
  uint32_t MAX = 0, MIN = 10000;  
  for (uint16_t i = 0; i < COUNT_VALUES; i++)             //Делаем несколько измерений напряжения
  {
    VALUES[i] = analogReadMilliVolts(PIN) * 1.984;         //Получаем значения (5.06 + 5.06) / 5.10
    MAX       = max(MAX,  VALUES[i]);                     //Находим максимальное значение
    MIN       = min(MIN,  VALUES[i]);                     //Находим минимальное значение
  }
   DATA.MAX_GRAPH = MAX;
   DATA.MIN_GRAPH = MIN;
}


/***************************************************************/
//Режим осцилографа
/***************************************************************/
void OSCILLOSCOPE(bool TOUCHED, bool PRESS, int16_t X, int16_t Y)
{
  if (DATA.DISPLAY_ONE)
  {
    MAIN.fillSprite(TFT_BLACK);
    MAIN.setTextSize(2);
    MAIN.drawString("F:", 10, 10, 1);
    MAIN.drawString("V :", 160, 10, 1);
    MAIN.drawString("V :", 310, 10, 1);
    MAIN.setTextSize(1);
    MAIN.drawString("max", 170, 17, 1);
    MAIN.drawString("min", 320, 17, 1);
    DATA.HZ = 0;
    DATA.DISPLAY_ONE = false;
    if (!DATA.STOP_PRESS)
      DATA.STOP_TIME = false;
  }
  if (TOUCHED && !PRESS && GRAPH_BUTTON.IS_PRESS(X, Y))
  {
    DATA.STOP_TIME = !DATA.STOP_TIME;
    DATA.STOP_PRESS = !DATA.STOP_PRESS;
  }
  
  bool FIRST_LEFT_TEXT = true, SIGN = false;; 
  uint16_t  DIVIDER = 0, DIVIDER_TIME = 0;
  
  MAIN.fillRect(0, 35, WIDTH, 205, TFT_BLACK);
  MAIN.setTextColor(TFT_WHITE);
  if (!DATA.QUEUE)
  {
    pinMode(45, INPUT);         //Пин вход
    pinMode(46, OUTPUT);        //Пин выход
    digitalWrite(46,0);
    if (analogReadMilliVolts(10) > 100)
    {
      SIZE_SIGNAL(10, DATA.STOP_TIME);
      DATA.QUEUE = false;
    }
    else
    {
      pinMode(46, INPUT);         //Пин вход
      pinMode(45, OUTPUT);        //Пин выход
      digitalWrite(45,0);
      if (analogReadMilliVolts(1) > 100)
      {
        SIZE_SIGNAL(1, DATA.STOP_TIME);
        DATA.QUEUE = true;
        SIGN = true;
      }
      else
        DATA.QUEUE = false;
    }   
  }
  else
  {
      pinMode(46, INPUT);         //Пин вход
      pinMode(45, OUTPUT);        //Пин выход
      digitalWrite(45,0);
      if (analogReadMilliVolts(1) > 100)
      {
        SIZE_SIGNAL(1, DATA.STOP_TIME);
        DATA.QUEUE = true;
      }
      else
        DATA.QUEUE = false;
      SIGN = true;
  }
  
  DATA.MAX_GRAPH =  ceil(DATA.MAX_GRAPH / pow(4, TO.SIZE_NUMBER(DATA.MAX_GRAPH))) * pow(4, TO.SIZE_NUMBER(DATA.MAX_GRAPH));
  DATA.SET_DIVIDER = (DATA.MAX_GRAPH - DATA.MIN_GRAPH) / MAX_DIVIDER;
  MAIN.setTextSize(2);
  MAIN.fillRect(35, 10, 125, 35, TFT_BLACK);
  if (DATA.STOP_TIME)
     DATA.HZ = DATA.HZ_STOP;
  if (DATA.HZ >= 1000000)
    MAIN.drawString( "MHz", MAIN.drawFloat(DATA.HZ / 1000000.00f, 2, 35, 10) + 40, 10);  
  else if (DATA.HZ >= 1000) 
    MAIN.drawString("kHz", MAIN.drawFloat(DATA.HZ / 1000.00f, 2, 35, 10) + 40, 10); 
  else
    MAIN.drawString("Hz", MAIN.drawNumber(DATA.HZ, 35, 10) + 40, 10);
  if (!DATA.STOP_TIME)
    DATA.HZ_STOP = DATA.HZ;
  MAIN.fillRect(195, 10, 85, 35, TFT_BLACK); 
  if (SIGN)
    MAIN.drawString("-", 195, 10, 1);
  MAIN.drawFloat(DATA.MAX_GRAPH / 100.00f, 2, SIGN ? 210 : 200, 10, 1);
  MAIN.fillRect(335, 10, 75, 35, TFT_BLACK);
  if (SIGN)
    MAIN.drawString("-", 345, 10, 1);
  MAIN.drawFloat(DATA.MIN_GRAPH / 100.00f, 2, SIGN ? 360 : 350, 10, 1);
  if (DATA.STOP_TIME)
    MAIN.drawString("PAUSE", 470, 10, 1);
  else
    MAIN.fillRect(470, 10, 66, 35, TFT_BLACK);
  MAIN.setTextSize(1);
  
  
  MAIN.drawFastVLine(WIDTH_PADDING, HEIGHT_PADDING, HEIGHT_BOTTOM - HEIGHT_PADDING, TO.RGB_TO_RGB16(0, 199, 223));
  MAIN.drawFastHLine(WIDTH_PADDING, HEIGHT_BOTTOM, WIDTH, TO.RGB_TO_RGB16(0, 199, 223));
  
  for (uint16_t x = WIDTH_PADDING; x <= WIDTH; x += 5) {                  //Строим сетку графика
    for (uint16_t y = HEIGHT_PADDING + 20; y < HEIGHT_BOTTOM; y += 20) {
      MAIN.drawFastHLine(x + 1, y, 2, TO.RGB_TO_RGB16(142, 200, 171));
    }

    if ((x - WIDTH_PADDING) % 25 == 0) {
      for (uint16_t y = HEIGHT_PADDING; y < HEIGHT_BOTTOM; y += 5) {
        if (x != WIDTH_PADDING)
          MAIN.drawFastVLine(x, y, 2, TO.RGB_TO_RGB16(142, 200, 171));
        if (FIRST_LEFT_TEXT && y % 20 == 0)
        {
          MAIN.drawFastHLine(WIDTH_PADDING - 3, y, 3, TO.RGB_TO_RGB16(0, 199, 223));
          int32_t VALUE_DIVIDER = DATA.MAX_GRAPH - (DATA.SET_DIVIDER * DIVIDER); 
          MAIN.drawFloat(VALUE_DIVIDER / 100.00f, 2, VALUE_DIVIDER > 1000 ? 5 : 10, y - 2, 1);
          ++DIVIDER;  
        }
      }
      FIRST_LEFT_TEXT = false;
      MAIN.drawFastHLine(x - WIDTH_PADDING == 0 ? x + 1 : x == WIDTH - 12 ? x - 2 : x - 1, HEIGHT_PADDING, x - WIDTH_PADDING == 0  ? 2 : 3, TO.RGB_TO_RGB16(142, 200, 171));
      if (x > WIDTH_PADDING)                                                                                                   
      {
        MAIN.drawFastVLine(x, HEIGHT_BOTTOM, 3, TO.RGB_TO_RGB16(0, 199, 223));
        ++DIVIDER_TIME;
      }
    }
  }
  MAIN.drawFloat(DATA.MIN_GRAPH / 100.00f, 2, 10, HEIGHT_BOTTOM - 2, 1);

  for(uint16_t i = 0; i < COUNT_VALUES; ++i)
      MAIN.drawLine(i + WIDTH_PADDING + 1, map(VALUES[i], DATA.MIN_GRAPH, DATA.MAX_GRAPH, HEIGHT_BOTTOM, HEIGHT_PADDING), i + WIDTH_PADDING + 1, map(VALUES[i == 0 ? i : i - 1], DATA.MIN_GRAPH, DATA.MAX_GRAPH, HEIGHT_BOTTOM, HEIGHT_PADDING), TFT_RED);
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
}

/***************************************************************/
//Режим измерения только напряжения
/***************************************************************/
void VOLTMETR()
{
  if (millis() - DATA.TIME <= 200)    //Добавляем задержку в 200 миллисекунд
    return;
  DATA.TIME = millis(); 

  MAIN.fillSprite(TFT_BLACK);

  BATTERY(DATA.DISPLAY_ONE);
  MAIN.drawRect(501, 0, 30, 15, TFT_WHITE);
  MAIN.fillRect(496, 5, 5, 5, TFT_WHITE);
  MAIN.fillRect(502 + DATA.BATTERY_VALUE, 1, 28 - DATA.BATTERY_VALUE, 13, TO.RGB_TO_RGB16(152, 251, 152));
  
  MAIN.loadFont(FONT_TEXT);
  MAIN.drawString("VOLTMETR", WIDTH / 2 - 50, 10);
  MAIN.unloadFont();
  
  MAIN.drawCircle(20, HEIGHT - 20, 15, TFT_WHITE);   
  MAIN.drawCircle(60, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(100, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.fillCircle(140, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(180, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(220, HEIGHT - 20, 15, TFT_WHITE);
  
  MAIN.loadFont(FONT);
  pinMode(46, INPUT);
  pinMode(45, INPUT);
  
    VOLT(&MAIN, 'L');
  if (DATA.SELECT_DISPLAY == 0)
    VOLT(&MAIN, 'R');
  if (DATA.SELECT_DISPLAY == 0)
  {
    analogWrite(BUZZER_PIN, 0);
    RGB_LED.setPixelColor(0, RGB_LED.Color(0, 0, 0));
    RGB_LED.show();
    MAIN.drawString("0.00V", WIDTH / 2 - 100, HEIGHT / 2 - 50);
    DATA.VALUE = 0;
    DATA.NAME = "v";
  }
  MAIN.unloadFont(); 
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
}


/***************************************************************/
//Режим измерения только сопротивления
/***************************************************************/
void OHMMETER()
{
  if (millis() - DATA.TIME <= 200)                  //Добавляем задержку в 200 миллисекунд
    return;
  DATA.TIME = millis(); 

  MAIN.fillSprite(TFT_BLACK);

  BATTERY(DATA.DISPLAY_ONE);
  MAIN.drawRect(501, 0, 30, 15, TFT_WHITE);
  MAIN.fillRect(496, 5, 5, 5, TFT_WHITE);
  MAIN.fillRect(502 + DATA.BATTERY_VALUE, 1, 28 - DATA.BATTERY_VALUE, 13, TO.RGB_TO_RGB16(152, 251, 152));

  MAIN.loadFont(FONT_TEXT);
  MAIN.drawString("OHMMETER", WIDTH / 2 - 50, 10);
  MAIN.unloadFont();
  
  MAIN.drawCircle(20, HEIGHT - 20, 15, TFT_WHITE);   
  MAIN.drawCircle(60, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(100, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(140, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.fillCircle(180, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(220, HEIGHT - 20, 15, TFT_WHITE);
  
  MAIN.loadFont(FONT);  
  OHMMETER(&MAIN);
  MAIN.unloadFont();
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
}


/***************************************************************/
//Режим генератора
/***************************************************************/
void GENERATOR(bool TOUCHED, int16_t X, int16_t Y)
{
  SLIDER_GENERATE.X = X;
  SLIDER_GENERATE.Y = Y;
        
  if (DATA.DISPLAY_ONE)
  {
    pinMode(46, INPUT);
    pinMode(45, OUTPUT);
    digitalWrite(46,0);
    digitalWrite(45,0);
    DATA.DISPLAY_ONE = false;
  }
  
  analogWrite(PLUS_PIN, SAVE.DELAY);
  
  MAIN.fillSprite(TFT_BLACK);

  MAIN.drawCircle(20, HEIGHT - 20, 15, TFT_WHITE);   
  MAIN.drawCircle(60, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(100, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(140, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.drawCircle(180, HEIGHT - 20, 15, TFT_WHITE);
  MAIN.fillCircle(220, HEIGHT - 20, 15, TFT_WHITE);
  
  MAIN.loadFont(FONT);
  MAIN.drawString(String(SAVE.DELAY * 100 / 255) + "%", WIDTH / 2 - 100, HEIGHT / 2 - 50);
  MAIN.unloadFont(); 
  DATA.RESULT = String(SAVE.DELAY);

  MAIN.loadFont(FONT_TEXT);
  MAIN.drawString("GENERATOR", WIDTH / 2 - 50, 10);
  MAIN.drawString("PWM", SLIDER_GENERATE.LINE_X2 + 30, SLIDER_GENERATE.CIRCLE_Y - 20, 1);
  SLIDER_GENERATE.MOVEMENT(TOUCHED);
  MAIN.fillTriangle(SLIDER_GENERATE.LINE_X1, SLIDER_GENERATE.CIRCLE_Y + 15, SLIDER_GENERATE.LINE_X1, SLIDER_GENERATE.CIRCLE_Y - 20, SLIDER_GENERATE.LINE_X2, SLIDER_GENERATE.CIRCLE_Y + 15, TFT_WHITE);
  MAIN.fillCircle(SLIDER_GENERATE.CIRCLE_X, SLIDER_GENERATE.CIRCLE_Y, SLIDER_GENERATE.CIRCLE_R, TFT_CYAN);
  SAVE.DELAY = 255 - (SLIDER_GENERATE.CIRCLE_X - SLIDER_GENERATE.LINE_X1);
  if (SAVE.DELAY != DATA.DELAY)
  {
    DATA.REQUEST = true;
    DATA.REQUEST_TIME = millis();
  }
  MAIN.drawNumber(SAVE.DELAY, SLIDER_GENERATE.LINE_X1 - 110, SLIDER_GENERATE.CIRCLE_Y - 15, 1);
  MAIN.unloadFont(); 
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)MAIN.getPointer());
}


/***************************************************************/
//Верхняя шторка
/***************************************************************/
void UP(bool TOUCHED, int16_t X, int16_t Y)
{
  SLIDER_PALETTE.X    = X;
  SLIDER_PALETTE.Y    = Y;
  SLIDER_BRIGHTNESS.X = X;
  SLIDER_BRIGHTNESS.Y = Y;
  SLIDER_FLASHLIGHT.X = X;
  SLIDER_FLASHLIGHT.Y = Y;
      
  MAIN.fillSprite(TFT_BLACK);

  MAIN.pushImage(SLIDER_PALETTE.LINE_X2 + 30, SLIDER_PALETTE.CIRCLE_Y - 25, 50, 50, PALETTE_50_50);
  SLIDER_PALETTE.MOVEMENT(TOUCHED);
  for(uint8_t X = 0; X < 255; ++X)
    MAIN.drawLine(SLIDER_PALETTE.LINE_X1 + X, SLIDER_PALETTE.CIRCLE_Y - 15, SLIDER_PALETTE.LINE_X1 + X, SLIDER_PALETTE.CIRCLE_Y + 15, TO.PALETTE(X * 6));
  MAIN.fillCircle(SLIDER_PALETTE.CIRCLE_X, SLIDER_PALETTE.CIRCLE_Y, SLIDER_PALETTE.CIRCLE_R, TO.PALETTE((SLIDER_PALETTE.CIRCLE_X - 150) * 6));
  MAIN.fillRect(SLIDER_PALETTE.LINE_X1 - 110, SLIDER_PALETTE.CIRCLE_Y - 30, 60, 60, TO.PALETTE((SLIDER_PALETTE.CIRCLE_X - 150) * 6));
  if (SAVE.SLIDER_PALETTE != SLIDER_PALETTE.CIRCLE_X)
  {
    DATA.REQUEST = true;
    DATA.REQUEST_TIME = millis();
    SAVE.SLIDER_PALETTE = SLIDER_PALETTE.CIRCLE_X;
  } 

  MAIN.pushImage(SLIDER_BRIGHTNESS.LINE_X2 + 30, SLIDER_BRIGHTNESS.CIRCLE_Y - 20, 50, 50, BRIGHTNESS_50_50);
  SLIDER_BRIGHTNESS.MOVEMENT(TOUCHED);
  MAIN.fillTriangle(SLIDER_BRIGHTNESS.LINE_X1, SLIDER_BRIGHTNESS.CIRCLE_Y + 15, SLIDER_BRIGHTNESS.LINE_X1, SLIDER_BRIGHTNESS.CIRCLE_Y - 20, SLIDER_BRIGHTNESS.LINE_X2, SLIDER_BRIGHTNESS.CIRCLE_Y + 15, TFT_WHITE);
  MAIN.fillCircle(SLIDER_BRIGHTNESS.CIRCLE_X, SLIDER_BRIGHTNESS.CIRCLE_Y, SLIDER_BRIGHTNESS.CIRCLE_R, TFT_CYAN);
  RGB_LED.setBrightness(255 - (SLIDER_BRIGHTNESS.CIRCLE_X - SLIDER_BRIGHTNESS.LINE_X1));
  MAIN.loadFont(FONT_TEXT);
  MAIN.drawNumber(255 - (SLIDER_BRIGHTNESS.CIRCLE_X - SLIDER_BRIGHTNESS.LINE_X1), SLIDER_BRIGHTNESS.LINE_X1 - 110, SLIDER_BRIGHTNESS.CIRCLE_Y - 15, 1);
  if (SAVE.SLIDER_BRIGHTNESS != SLIDER_BRIGHTNESS.CIRCLE_X)
  {
    DATA.REQUEST = true;
    DATA.REQUEST_TIME = millis();
    SAVE.SLIDER_BRIGHTNESS = SLIDER_BRIGHTNESS.CIRCLE_X;
  } 
  
  SLIDER_FLASHLIGHT.MOVEMENT_CHECKED(TOUCHED, SLIDER_FLASHLIGHT.LINE_X1, SLIDER_FLASHLIGHT.LINE_X1 + ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3), SLIDER_FLASHLIGHT.LINE_X2 - ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3),SLIDER_FLASHLIGHT.LINE_X2);
  MAIN.drawLine(SLIDER_FLASHLIGHT.LINE_X1, SLIDER_FLASHLIGHT.CIRCLE_Y, SLIDER_FLASHLIGHT.LINE_X2, SLIDER_FLASHLIGHT.CIRCLE_Y, TFT_WHITE);
  MAIN.drawLine(SLIDER_FLASHLIGHT.LINE_X1, SLIDER_FLASHLIGHT.CIRCLE_Y - 10, SLIDER_FLASHLIGHT.LINE_X1, SLIDER_FLASHLIGHT.CIRCLE_Y + 10, TFT_WHITE);
  MAIN.drawLine(SLIDER_FLASHLIGHT.LINE_X1 + ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3), SLIDER_FLASHLIGHT.CIRCLE_Y - 10,SLIDER_FLASHLIGHT.LINE_X1 + ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3), SLIDER_FLASHLIGHT.CIRCLE_Y + 10, TFT_WHITE);
  MAIN.drawLine(SLIDER_FLASHLIGHT.LINE_X2 - ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3), SLIDER_FLASHLIGHT.CIRCLE_Y - 10,SLIDER_FLASHLIGHT.LINE_X2 - ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3), SLIDER_FLASHLIGHT.CIRCLE_Y + 10, TFT_WHITE);
  MAIN.drawLine(SLIDER_FLASHLIGHT.LINE_X2, SLIDER_FLASHLIGHT.CIRCLE_Y - 10, SLIDER_FLASHLIGHT.LINE_X2, SLIDER_FLASHLIGHT.CIRCLE_Y + 10, TFT_WHITE);
  MAIN.fillCircle(SLIDER_FLASHLIGHT.CIRCLE_X, SLIDER_FLASHLIGHT.CIRCLE_Y, SLIDER_FLASHLIGHT.CIRCLE_R, TFT_WHITE);
  MAIN.fillCircle(SLIDER_FLASHLIGHT.CIRCLE_X, SLIDER_FLASHLIGHT.CIRCLE_Y, SLIDER_FLASHLIGHT.CIRCLE_R - 15, TFT_RED);

  MAIN.drawString("UF", SLIDER_FLASHLIGHT.LINE_X1 - 15, SLIDER_FLASHLIGHT.CIRCLE_Y + 20, 1);
  MAIN.drawString("RGB", SLIDER_FLASHLIGHT.LINE_X1 + ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3) - 26, SLIDER_FLASHLIGHT.CIRCLE_Y + 20, 1);
  MAIN.drawString("ON", SLIDER_FLASHLIGHT.LINE_X2 - ((SLIDER_FLASHLIGHT.LINE_X2 - SLIDER_FLASHLIGHT.LINE_X1) / 3) - 16, SLIDER_FLASHLIGHT.CIRCLE_Y + 20, 1);
  MAIN.drawString("OFF", SLIDER_FLASHLIGHT.LINE_X2 - 25, SLIDER_FLASHLIGHT.CIRCLE_Y + 20, 1);
  MAIN.unloadFont();

  if (SLIDER_FLASHLIGHT.SELECT == 0)
  {
    digitalWrite(42, 0);
    RGB_LED.clear();
  }
  else if (SLIDER_FLASHLIGHT.SELECT == 1)
  {
    digitalWrite(42, 0);
    RGB_LED.setPixelColor(1, RGB_LED.Color(255, 255, 255));
    RGB_LED.show();
    RGB_LED.setPixelColor(2, RGB_LED.Color(255, 255, 255));
    RGB_LED.show();
  }
  else if (SLIDER_FLASHLIGHT.SELECT == 2)
  {
    digitalWrite(42, 0);
    RGB_LED.setPixelColor(1, TO.RGB_LED((SLIDER_PALETTE.CIRCLE_X - SLIDER_PALETTE.LINE_X1) * 6));
    RGB_LED.show();
    RGB_LED.setPixelColor(2, TO.RGB_LED((SLIDER_PALETTE.CIRCLE_X - SLIDER_PALETTE.LINE_X1) * 6));
    RGB_LED.show(); 
  }
  else
  {
    RGB_LED.clear();
    digitalWrite(42, 1);
  }
  
  MAIN.drawLine(201, 235, 335, 235, TFT_WHITE); 
  MAIN.drawLine(201, 237, 335, 237, TFT_WHITE); 
  MAIN.drawLine(201, 239, 335, 239, TFT_WHITE); 
  amoled.pushColors(0,0,WIDTH,HEIGHT,(uint16_t *)MAIN.getPointer());
}


/***************************************************************/
//Нижняя шторка
/***************************************************************/
void BOTTOM(bool TOUCHED, int16_t X, int16_t Y)
{
  SLIDER_DISPLAY.X  = X;
  SLIDER_DISPLAY.Y  = Y;
  SLIDER_SOUND.X    = X;
  SLIDER_SOUND.Y    = Y;
      
  MAIN.fillSprite(TFT_BLACK);
  
  MAIN.drawLine(201, 0, 335, 0, TFT_WHITE); 
  MAIN.drawLine(201, 2, 335, 2, TFT_WHITE); 
  MAIN.drawLine(201, 4, 335, 4, TFT_WHITE); 
  
  MAIN.loadFont(FONT_TEXT);

  MAIN.pushImage(SLIDER_SOUND.LINE_X2 + 30, SLIDER_SOUND.CIRCLE_Y - 20, 50, 50, SOUND_50_50);
  SLIDER_SOUND.MOVEMENT(TOUCHED);
  MAIN.fillTriangle(SLIDER_SOUND.LINE_X1, SLIDER_SOUND.CIRCLE_Y + 15, SLIDER_SOUND.LINE_X1, SLIDER_SOUND.CIRCLE_Y - 20, SLIDER_SOUND.LINE_X2, SLIDER_SOUND.CIRCLE_Y + 15, TFT_WHITE);
  MAIN.fillCircle(SLIDER_SOUND.CIRCLE_X, SLIDER_SOUND.CIRCLE_Y, SLIDER_SOUND.CIRCLE_R, TFT_CYAN);
  MAIN.drawNumber(255 - (SLIDER_SOUND.CIRCLE_X - SLIDER_SOUND.LINE_X1), SLIDER_SOUND.LINE_X1 - 110, SLIDER_SOUND.CIRCLE_Y - 15, 1);
  if (SAVE.SLIDER_SOUND != SLIDER_SOUND.CIRCLE_X)
  {
    DATA.REQUEST = true;
    DATA.REQUEST_TIME = millis();
    SAVE.SLIDER_SOUND = SLIDER_SOUND.CIRCLE_X;
  }
  
  MAIN.pushImage(SLIDER_DISPLAY.LINE_X2 + 30, SLIDER_DISPLAY.CIRCLE_Y - 20, 50, 50, DISPLAY_BRIGHTNESS_50_50);
  SLIDER_DISPLAY.MOVEMENT(TOUCHED);
  MAIN.fillTriangle(SLIDER_DISPLAY.LINE_X1, SLIDER_DISPLAY.CIRCLE_Y + 15, SLIDER_DISPLAY.LINE_X1, SLIDER_DISPLAY.CIRCLE_Y - 20, SLIDER_DISPLAY.LINE_X2, SLIDER_DISPLAY.CIRCLE_Y + 15, TFT_WHITE);
  MAIN.fillCircle(SLIDER_DISPLAY.CIRCLE_X, SLIDER_DISPLAY.CIRCLE_Y, SLIDER_DISPLAY.CIRCLE_R, TFT_CYAN);
  amoled.setBrightness(255 - (SLIDER_DISPLAY.CIRCLE_X - SLIDER_DISPLAY.LINE_X1));
  MAIN.drawNumber(amoled.getBrightness(), SLIDER_DISPLAY.LINE_X1 - 110, SLIDER_DISPLAY.CIRCLE_Y - 15, 1);
  if (SAVE.SLIDER_DISPLAY != SLIDER_DISPLAY.CIRCLE_X)
  {
    DATA.REQUEST = true;
    DATA.REQUEST_TIME = millis();
    SAVE.SLIDER_DISPLAY = SLIDER_DISPLAY.CIRCLE_X;
  }
  
  
  MAIN.unloadFont();
  

  if (TOUCHED && WIFI_BUTTON.IS_PRESS(X, Y))
  {
    DATA.WIFI_PRESS = !DATA.WIFI_PRESS;
    SAVE.WIFI       = DATA.WIFI_PRESS;
    EEPROM_SAVE();
    ESP.restart();
  }
  MAIN.loadFont(FONT);
  MAIN.fillRect(50, 150, 420, 240, DATA.WIFI_PRESS ? TO.RGB_TO_RGB16(152, 251, 152) : TO.RGB_TO_RGB16(176, 63, 53));
  MAIN.drawString(DATA.WIFI_PRESS ? "192.168.0.1" : "WI-FI OFF", DATA.WIFI_PRESS ? WIDTH / 2 - 200 : WIDTH / 2 - 180, 152);
  MAIN.unloadFont();
  amoled.pushColors(0, 0, WIDTH, HEIGHT,(uint16_t *)MAIN.getPointer());
}

void loop()
{
    if (MICROPHONE.recognize(DATA.BUF, 50) > 0 && DATA.BUF[1] > 0)
    {
      if (DATA.BUF[1] != 5)
        DATA.SPEEK_DATA = true;
      if (DATA.BUF[1] == 1)
        TOUCH.NUMBER = 0;
      else if (DATA.BUF[1] == 2)
        TOUCH.NUMBER = 1;
      else if (DATA.BUF[1] == 3)
        TOUCH.NUMBER = 3;
      else if (DATA.BUF[1] == 4)
        TOUCH.NUMBER = 4;
      else if (DATA.BUF[1] == 5)
      {
        TOUCH.TOP       = 3;
        DATA.YOU_PRESS  = true;
      }
      DATA.TIME_SPEEK = millis();
    }
    
    int16_t X, Y;
    bool touched = amoled.getPoint(&X, &Y);
    TOUCH.X = X;
    TOUCH.Y = Y;
    TOUCH.SCREEN(touched);

    if (DATA.NUMBER_LAST != TOUCH.NUMBER || TOUCH.TOP > 0)
    {
      analogWrite(BUZZER_PIN, 0);
      analogWrite(PLUS_PIN, 0);
      RGB_LED.setPixelColor(0, RGB_LED.Color(0, 0, 0));
      RGB_LED.show();
      DATA.DISPLAY_ONE = true;
      DATA.PRESS       = true;
    }
    if (!touched)
      DATA.PRESS       = false;
      
    if (TOUCH.TOP == 1)
      UP(touched, X, Y);
    else if (TOUCH.TOP == 2)
      BOTTOM(touched, X, Y);
    else if(TOUCH.TOP == 3)
      YOU(touched, X, Y);
    else
    {
      if (TOUCH.NUMBER == 0)
        TESTER();
      else if (TOUCH.NUMBER == 1)
        MEASUREMENT();
      else if (TOUCH.NUMBER == 2)
        OSCILLOSCOPE(touched, DATA.PRESS, X, Y);
      else if (TOUCH.NUMBER == 3)
        VOLTMETR(); 
      else if (TOUCH.NUMBER == 4)
        OHMMETER();
      else if (TOUCH.NUMBER == 5)
        GENERATOR(touched, X, Y);
      DATA.NUMBER_LAST = TOUCH.NUMBER;
      
      if (DATA.SPEEK_DATA && millis() - DATA.TIME_SPEEK >= 400) 
        SPEAK(DATA.VALUE, DATA.NAME); 
    }

    if (DATA.REQUEST && millis() - DATA.REQUEST_TIME >= 1000)
      EEPROM_SAVE();
}
