/*Libreria para gestianar el estado de un boton, tanto flanco de pulso, como pulso largo.
  Autor: Javier Vargas García
*/

#include "Arduino.h"

class ButtonControl {
 public:
  ButtonControl(int Pin, int TimeBounce, int TimeLongPush); //Constructor
  ButtonControl(int Pin); //Constructor
  void begin(bool mode); //PinMode
  void begin(void); //PinMode
  bool Read(); //Muestreo, lectura del estado del botón, devuelve 1 ante un flanco o durante estado de pulso largo
  bool Flag(); //Devuelve 1 en deteccion de flanco
  bool LongFlag(); //Devuelve 1 en deteccion de flanco de pulso largo
  bool Estate(); //Estado del boton
  bool LongEstate(); //Estado de pulso largo
private:
  int Pin;
  bool Mode;
  int TimeBounce; //Tiempo antirrebotes
  int TimeLongPush; //Tiempo de pulso largo
  bool ButtonFlag; //Flanco de lectura
  bool ButtonLongFlag; //Flanco en pulso largo del boton
  bool ButtonEstate; //Estado de lectura
  bool ButtonLongEstate; //Estado del pulso largo del boton
  unsigned long m = 0; //Valor de tiempo en el que es pulsado
  bool longpushed = 0; //Modo pulso largo
};
