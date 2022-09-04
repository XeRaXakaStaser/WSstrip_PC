// =============================== ЭФФЕКТЫ ====================================

// ------------------------------- конфетти ------------------------------------
void sparkles() {
  for (byte i = 0; i < NUMLEDS; i++) {
    if (strip.getColorHEX(i) == 0) {
      strip.setHSV(i, random(0, 255), 255, random(150, 255));
    }
    else strip.fade(i, 1);
  }
  strip.show();
}

// -------------------------------- огонь --------------------------------------
void fireRoutine() {
  static uint32_t prevTime;
    for (byte i = 0; i < NUMLEDS; i++ ) {
      strip.setLED(i, getFireColor((inoise8(i * FIRE_STEP, counter))));
    }
    counter += 20;
    strip.show();
  }

                                                                                  
LEDdata getFireColor(int val) {                                                   // возвращает цвет огня для одного пикселя
                                                                                  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return mHSV(
           color1 + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}


// ------------------------------- радуга --------------------------------------
void rainbow() {
  static byte cnt = 0;
  for (byte i = 0; i < NUMLEDS; i++) {
    strip.setHSV(i, cnt + i * (255 / NUMLEDS), 255, 255);
  }
  cnt ++;
  strip.show();
}

// ------------------------- цветовой градиент ---------------------------------
void gradient() {
  static byte color;
  static boolean direct, clr;
  for (byte i = 0; i < NUMLEDS; i++) {
    if (clr) {
    color = color1;            
    }
    else {
    color = color2;
    }
    strip.setHSV(i, color, 255, V);
      if (direct) {
        V += (500 / NUMLEDS);                                                     // получаем плавное нарастание
        V = constrain (V, 0, 250);
        if (V == 250) {
          direct = !direct;
        }
      }
      else {
        V -= (500 / NUMLEDS);                                                     // получаем плавное угасание
        V = constrain (V, 0, 250);
        if (V == 0) {
          direct = !direct;
          clr = !clr;
        }
      }
  }
  strip.show();
  clr = !clr;
}

// ------------------------------- помехи --------------------------------------
void noises() { Mode++;/*
  if (!glitchFlag && secs > 7 && secs < 55) {
    if (glitchTimer.isReady()) {
      glitchFlag = true;
      indiState = 0;
      glitchCounter = 0;
      glitchMax = random(2, 6);
      glitchIndic = random(0, 4);
      glitchTimer.setInterval(random(1, 6) * 20);
    }
  } else if (glitchFlag && glitchTimer.isReady()) {
    indiDimm[glitchIndic] = indiState * indiMaxBright;
    indiState = !indiState;
    glitchTimer.setInterval(random(1, 6) * 20);
    glitchCounter++;
    if (glitchCounter > glitchMax) {
      glitchTimer.setInterval(random(GLITCH_MIN * 1000L, GLITCH_MAX * 1000L));
      glitchFlag = false;
      indiDimm[glitchIndic] = indiMaxBright;
    }
  }*/
}  

// ================ РЕЖИМ НАСТРОЙКИ ЦВЕТА color1 И color2 =====================
void clr_select() {
  for (byte i = 0; i < NUMLEDS; i++) {
    if (i < NUMLEDS / 2) {
      strip.setHSV(i, color1, 255, 255);
    }
    else {
      strip.setHSV(i, color2, 255, 255);
    }
  //if 
  strip.show();
  }
}
