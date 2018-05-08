#include <Arduino.h>

#include "Plotter.hpp"
//#include "menus/MainMenu.hpp"

Plotter* mPlotter;
//MainMenu* mMainMenu;

void setup() {
  // Serial interface setup
  Serial.begin(115200);

  // Creates Plotter controller and homes it
  Serial.println("Creating Plotter");
  mPlotter = new Plotter();
  delay(10000);
  Serial.println("Calibrate X");
  mPlotter->calibrate(Axis::X);
  // delay(10000);
  // Serial.println("Calibrate Y");
  // mPlotter->calibrate(Axis::Y);
  // delay(10000);
  // Serial.println("Calibrate Z");
  // mPlotter->calibrate(Axis::Z);
  
  // mMainMenu = new MainMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, false, 1000), mPlotter);
}

void loop() {
  //SerialDisplayMenu::userInputLoop(mMainMenu);
}