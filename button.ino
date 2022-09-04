// ========================= ОБРАБОТКА НАЖАТИЙ КНОПКИ =====================
void buttonTick() {
  touch.tick();                                                         // одинарным нажатием в режиме 6 (изменение опорных цветов) изменяем HSV цвета 1
   if (touch.isSingle()) {                                              //
    if (Mode == 6) color1 += 25;
   }
  
   if (touch.isDouble()) {                                              // двойным нажатием в режиме 6 изменяем HSV цвета 2
     if (Mode == 6) color2 += 25;                                       //
     else {
      Mode += 1;
      strip.clear();
     }
   }

   if (touch.isTriple()) {                                              // тройным нажатием кнопки вызываем режим 6 - настройка цвета для эффектов огня
   static byte last_mode;                                               // и градиента
   static boolean selector = 1;
     if (selector) {
       if (Mode != last_mode) last_mode = Mode;
          else Mode = 1;      
       Mode = 6;
     }
     else {
       Mode = last_mode;
     }
     selector = !selector;
   }

   if ((touch.hasClicks()) && (touch.getClicks() == 5)) {               // если было пятикратное нажатие на кнопку, то производим сохранение параметров
      EEPROM.write(0, 100);                                             // хз почему 100. Флаг изменения настроек (для применения их при запуске) 
      if (EEPROM.read(1) != Mode) EEPROM.write(1, Mode);                // запоминаем текущий эффект
      if (EEPROM.read(2) != DELAY) EEPROM.write(2, DELAY);              // запоминаем скорость анимации  
      if (EEPROM.read(3) != BRIGHTNESS) EEPROM.write(3, BRIGHTNESS);    // запоминаем текущий яркость
      if (EEPROM.read(4) != color1) EEPROM.write(4, color1);            // запоминаем текущий цвет1                                                                   
      if (EEPROM.read(5) != color2) EEPROM.write(5, color2);            // запоминаем текущий цвет2                                                                   
      strip.clear();                                                    // индикация сохранения
      for (byte i = 0; i < NUMLEDS; i++) { 
        strip.setColor(i, GREEN);
        delay(500 / NUMLEDS);
        strip.show();
      }
      strip.clear();
   }
   
   if (touch.isStep(1)) {                                                 // изменение скорости анимации при двойном нажатии и удержании кнопки
     DELAY += 10;                                                         // увеличение задержки - медленнее анимация
     strip.clear();
     value = map(DELAY, 0, 255, 0, NUMLEDS);
     for (byte i = 0; i < value; i++) {
       strip.setColor(i, RED);
     }
     strip.show();
     strip.clear();
     delay(200);
   }

   if (touch.isStep(2)) {                                                 // изменение яркости при тройном нажатии кнопки и удержании кнопки
     BRIGHTNESS += 25;
     strip.clear();
     value = map(BRIGHTNESS, 0, 255, 0, NUMLEDS);
     for (byte i = 0; i < value; i++) {
       strip.setColor(i, BLUE);
     }
     strip.setBrightness(BRIGHTNESS);
     strip.show();
     delay(300);
     strip.clear();
   }

   if (touch.isStep(3)) {                                                 // Сервисный выход на радужный режим
     Mode = 2;
     strip.show();
   }
}
