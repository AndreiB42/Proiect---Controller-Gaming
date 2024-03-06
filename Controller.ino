#include <Joystick.h>  

const uint8_t buttonCount = 7; //numar butoane
Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, buttonCount, //declare tip butoane si bool stocare
                     0, true, true, false,
                     false, false, false,
                     false, false, false,       
                     false, false);
 
int const BTN_1_PIN = 7;
int const BTN_2_PIN = 9;
int const BTN_3_PIN = 10;
int const BTN_4_PIN = 8;
int const BTN_5_PIN = 6;
int const BTN_6_PIN = 12; //pini conectare
int const BTN_7_PIN = 11;
int const AXIS_X_PIN = A1;
int const AXIS_Y_PIN = A0;
 
int const buttonPins[buttonCount] = {
  BTN_1_PIN,
  BTN_2_PIN,
  BTN_3_PIN,  //tip butoane simulate
  BTN_4_PIN,
  BTN_5_PIN,
  BTN_6_PIN,
  BTN_7_PIN
};
int lastButtonValue[buttonCount];
int lastXAxisValue = -1;
int lastYAxisValue = -1;   //valoare axe joystick
 
void setup()
{
  controller.setYAxisRange(0, 1023);
  controller.setYAxisRange(0, 1023);  //range operare joystick
  controller.begin(false);
 
  for (int i = 0; i < buttonCount; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonValue[i] = -1;
  }
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
 
void loop()
{
  bool sendUpdate = false;
  for (int i = 0; i < buttonCount; i++)
  {
    const int buttonValue = digitalRead(buttonPins[i]);  //citire digitala butoane
 
    if (buttonValue != lastButtonValue[i])
    {
      controller.setButton(i, !buttonValue);  //daca valoarea butonului este diferita de cea anterioara
      lastButtonValue[i] = buttonValue;
      sendUpdate = true;     //facem update
    }
  }
 
  const int currentXAxisValue = analogRead(AXIS_X_PIN);
  if (currentXAxisValue != lastXAxisValue)
  {
    controller.setXAxis(currentXAxisValue); //daca valoarea joystick axa x este diferita de cea anterioara
    lastXAxisValue = currentXAxisValue;
    sendUpdate = true;   //facem update
  }
 
  const int currentYAxisValue = analogRead(AXIS_Y_PIN);
  if (currentYAxisValue != lastYAxisValue)    //daca valoarea joystick axa Y este diferita de cea anterioara
  {
    controller.setYAxis(currentYAxisValue);
    lastYAxisValue = currentYAxisValue;
    sendUpdate = true; //facem update
  }
 
  if (sendUpdate)
  {
    controller.sendState();   //logica  trimitere status
  }
  delay(50); //delay 50
}
