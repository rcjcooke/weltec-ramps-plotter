#include <Arduino.h>

#include "Plotter.hpp"
#include "menus/MainMenu.hpp"

Plotter* mPlotter;
MainMenu* mMainMenu;

void testCode() {
  delay(10000);
  Serial.println("Calibrate X");
  mPlotter->calibrate(Axis::X);
  delay(10000);
  Serial.println("Calibrate Y");
  mPlotter->calibrate(Axis::Y);
  delay(10000);
  Serial.println("Calibrate Z");
  mPlotter->calibrate(Axis::Z);
}

void setup() {
  // Serial interface setup
  Serial.begin(115200);

  // Creates Plotter controller and homes it
  mPlotter = new Plotter();
  mMainMenu = new MainMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, false, 1000), mPlotter);
}

void loop() {
  SerialDisplayMenu::userInputLoop(mMainMenu);
}