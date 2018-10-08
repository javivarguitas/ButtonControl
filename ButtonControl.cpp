#include "ButtonControl.h"


ButtonControl::ButtonControl(int Pin_ = 3, int TimeBounce_ = 100, int TimeLongPush_ = 2000){
  Pin = Pin_;
  TimeBounce = TimeBounce_;
  TimeLongPush = TimeLongPush_;
}

ButtonControl::ButtonControl(int Pin_ = 3){
  Pin = Pin_;
  TimeBounce = 100;
  TimeLongPush = 2000;
}

void ButtonControl::begin(bool Mode_ = HIGH){
    if (Mode_ == HIGH) pinMode(Pin, INPUT_PULLUP);
    else pinMode(Pin, INPUT);
    Mode = Mode_;
}

void ButtonControl::begin() {
    pinMode(Pin, INPUT_PULLUP);
    Mode = HIGH;
}

bool ButtonControl::Read() {

  //Flancos a 0
  if (ButtonFlag) ButtonFlag = 0;
  if (ButtonLongFlag) ButtonLongFlag = 0;

  //Boton disponible, tiempo antirrebotes superado
  if (millis() > m + TimeBounce || millis() < m) {

    //Lectura digital
    bool p = digitalRead(Pin);
    if (Mode == HIGH) p = !p; //Boton pulsado a nivel bajo
    ButtonFlag = !ButtonEstate && p;
    ButtonEstate = p;

    //Si algun boton es pulsado, reiniciamos tiempo antirrebotes
    if (ButtonFlag) {
      m = millis();
      return 1;
    }

    //Boton pulsado durante un tiempo
    if (p) {

      //No esta activado el pulso largo
      if (!ButtonLongEstate) {
        //Tiempo de pulso largo superado
        if (millis() > m + TimeLongPush) {
          if (p) ButtonLongFlag = 1;
          //Estado de pulso largo activo
          longpushed = 1;
          ButtonLongEstate = 1;
        }
      }

      //Mantiene pulsado
      if (longpushed) return 1;
    }
    //Final de estado de pulso largo
    else if (longpushed) {
      longpushed = 0;
      ButtonLongEstate = 0;
    }

    return 0;
  }

  //Boton no disponible, recien pulsado.
  else {
    return 0;
  }
}

bool ButtonControl::Flag() {
  return ButtonFlag;
}

bool ButtonControl::LongFlag() {
  return ButtonLongFlag;
}

bool ButtonControl::Estate() {
  return ButtonEstate;
}

bool ButtonControl::LongEstate() {
  return ButtonLongEstate;
}
