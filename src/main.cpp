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
  Point* p1 = new Point(30,30);
  Point* p2 = new Point(50,70);
  Point* p3 = new Point(46,90);
  mPlotter->drawTriangle(p1, p2, p3);
  //mPlotter->moveTo(new Point(20,20));
  
  // mMainMenu = new MainMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, false, 1000), mPlotter);
}

void loop() {
  // SerialDisplayMenu::userInputLoop(mMainMenu);
}