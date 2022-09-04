/*
  Скетч динамической подсветки для компьютера с управлением одной сенсорной или механической кнопки
  для адресной светодиодной ленты с контроллером WS2812 
  Версия 1.0
  Длина ленты фронтальной панели 22 диода (60led/m)
  Режимы работы ленты (эффекты): Конфетти, Огонь, Радуга, Градиент, Помехи
*/

// ================== НАСТРОЙКИ =================

// ------------------ ЛЕНТА ---------------------
#define BRIGHTNESS_START 5                                // стандартная маскимальная яркость (0-255)
#define NUMLEDS 22                                        // длина ленты
#define ORDER_GRB                                         // порядок цветов на ленте.
#define DELAY_START 100                                   // стартовая скорость анимации

// ------------ НАСТРОЙКИ ПЛАМЕНИ ---------------
#define HUE_GAP 15                                        // заброс по hue
#define FIRE_STEP 15                                      // шаг огня
#define MIN_BRIGHT 20                                     // мин. яркость огня
#define MAX_BRIGHT 255                                    // макс. яркость огня
#define MIN_SAT 245                                       // мин. насыщенность
#define MAX_SAT 255                                       // макс. насыщенность

// ============= ДЛЯ РАЗРАБОТЧИКОВ =============
#define LED_PIN 10                                        // пин ленты
#define BTN_PIN 2                                         // пин подключения кнопки
#define COLOR_DEBTH 3                                     // битность цвета (от 1 до 3)

// ---------------- БИБЛИОТЕКИ -----------------
#include <EEPROM.h>
#include "microLED.h"
#include <FastLED.h>
#include <GyverButton.h>

// ------------------- ТИПЫ --------------------
LEDdata leds[NUMLEDS];                                    // буфер ленты типа LEDdata (размер зависит от COLOR_DEBTH)
microLED strip(leds, NUMLEDS, LED_PIN);                   // объявление ленты
//GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);            // сенсорная кнопка
GButton touch(BTN_PIN, HIGH_PULL, NORM_OPEN);             // механическая кнопка

// ----------------- ПЕРЕМЕННЫЕ ------------------
uint32_t timer;
byte DELAY, BRIGHTNESS, Mode, value, color1, color2;
int16_t V, counter;

// ----------------- ФУНКЦИИ -----------------------
void setup() {
  touch.setStepTimeout(200);
  touch.setClickTimeout(500);
  Mode = 0;
  //Serial.begin(9600);
  if (EEPROM.read(0) == 100) {                            // если было сохранение настроек, то восстанавливаем их 
    Mode = EEPROM.read(1);
    DELAY = EEPROM.read(2);
    BRIGHTNESS = EEPROM.read(3);
    color1 = EEPROM.read(4);
    color2 = EEPROM.read(5);
  }
  else {                                                  // если сохранённых настроек нет, то выставляется default
    color1 = 0;
    color2 = 100;
    DELAY = DELAY_START;
    BRIGHTNESS = BRIGHTNESS_START;
  }
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  buttonTick();
  if (millis() - timer > DELAY / 4) {
    switch (Mode) {
      case 0: sparkles();
        break;
      case 1: fireRoutine();
        break;
      case 2: rainbow();
        break;
      case 3: gradient();
        break;
      case 4: noises();
        break;
      case 5: Mode = 0;
        break;
      case 6: clr_select();
        break;
    } 
    timer = millis();
    //Serial.println (Mode);
  }
}
