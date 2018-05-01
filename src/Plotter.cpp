#include "Plotter.hpp"

/*******************************
 * Constructors
 *******************************/
Plotter::Plotter() {

}

/*******************************
 * Actions
 *******************************/
void Plotter::calibrateBedLevel() {

}

void Plotter::drawRect(Point origin, float length, float width) {
  // TODO: Add range error checking
  // Raise pen
  // Move to origin
  // Lower pen
  // Move to top right corner (length)
  // Move to bottom right corner (width)
  // Move to bottom left corner (-length)
  // Move to top left corner (-width)
  // Raise pen
}

void Plotter::drawTriangle(Point p1, Point p2, Point p3) {

}

void Plotter::drawCircle(Point centre, float radius) {

}

void Plotter::raise() {
  digitalWrite(Z_STEP_PIN, HIGH);
}

void Plotter::lower() {
  
  digitalWrite(Z_STEP_PIN, HIGH);

}

void Plotter::move(Point toPoint) {

}

void Plotter::home() {

}