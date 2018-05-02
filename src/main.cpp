#include <Arduino.h>

#include "Plotter.hpp"

void loop() {
  int i;
  Plotter* p;
  p = new Plotter();
  Point* origin = new Point(5,6);
  p->drawRect(origin, 4, 5);
  
}