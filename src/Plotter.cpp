#include "Plotter.hpp"

/*******************************
 * Constructors
 *******************************/
Plotter::Plotter() {
  // Set up axes
  mXAxis = new StepperAxis(X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN, 500000, false);
  mYAxis = new StepperAxis(Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN, 500000, true);
  mZAxis = new StepperAxis(Z_STEP_PIN, Z_DIR_PIN, Z_ENABLE_PIN, Z_MIN_PIN, Z_MAX_PIN, 500000, true);
  // Home everything
  home();

  // Turn the stepper motor power offto avoid thermal overload
  mXAxis->disable();
  mYAxis->disable();
  mZAxis->disable();
}

Plotter::~Plotter() {
  delete mXAxis;
  delete mYAxis;
  delete mZAxis;
}

/*******************************
 * Actions
 *******************************/
void Plotter::calibrateBedLevel() {

}

// Adding some comments
void Plotter::drawRect(Point* origin, float length, float width) {
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

void Plotter::drawTriangle(Point* p1, Point* p2, Point* p3) {

}

void Plotter::drawCircle(Point* centre, float radius) {

}

void Plotter::raise() {
  digitalWrite(Z_STEP_PIN, HIGH);
}

void Plotter::lower() {
  
  digitalWrite(Z_STEP_PIN, HIGH);

}

void Plotter::move(Point* toPoint) {

}

void Plotter::home() {
  while (!(mXAxis->isHome() && mYAxis->isHome() && mZAxis->isHome())) {
    mXAxis->singleStep(Direction::TowardsHome);
    mYAxis->singleStep(Direction::TowardsHome);
    mZAxis->singleStep(Direction::TowardsHome);
  }
}