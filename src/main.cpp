#include <Arduino.h>

#include "Plotter.hpp"

Plotter* mPlotter;

void setup() {
  // Creates Plotter controller and homes it
  mPlotter = new Plotter();
}

void loop() {

}