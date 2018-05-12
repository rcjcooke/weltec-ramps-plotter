#include <Arduino.h>

#include "Plotter.hpp"
#include "menus/MainMenu.hpp"

Plotter* mPlotter;
MainMenu* mMainMenu;

/*******************************
 * Physical Test Methods
 *******************************/
void testCalibration() {
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

void triangleTest() {
  Point* p1 = new Point(30,30);
  Point* p2 = new Point(50,70);
  Point* p3 = new Point(46,90);
  mPlotter->drawTriangle(p1, p2, p3);
}

/*******************************
 * Setup Methods
 *******************************/

void setup() {
  // Serial interface setup
  Serial.begin(115200);

  // Create Plotter controller and home it
  mPlotter = new Plotter();
  // Create the initial Serial Menu
  mMainMenu = new MainMenu(new SerialDisplayMenuConfiguration(SerialDisplayType::ansi_vt100, false, 1000), mPlotter);
}

/*******************************
 * Main Loop
 *******************************/

void loop() {
  // The menu runs the show - this will never exit
  SerialDisplayMenu::userInputLoop(mMainMenu);
}