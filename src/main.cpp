#include <Arduino.h>

#include "Plotter.hpp"
#include "menus/MainMenu.hpp"

Plotter* mPlotter;
MainMenu* mMainMenu;

void setup() {
  // Creates Plotter controller and homes it
  mPlotter = new Plotter();
  mMainMenu = new MainMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, true, 500), mPlotter);
  // Point* p = new Point(0,0);
  // mPlotter->drawTriangle(p, p, p);
}

void loop() {
  SerialDisplayMenu::userInputLoop(mMainMenu);
}