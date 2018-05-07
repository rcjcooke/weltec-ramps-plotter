#include <Arduino.h>

#include "Plotter.hpp"

Plotter* mPlotter;

void setup() {
  // Creates Plotter controller and homes it
  mPlotter = new Plotter();
  Point* p = new Point(0,0);
  mPlotter->drawTriangle(p, p, p);
}

void loop() {

}