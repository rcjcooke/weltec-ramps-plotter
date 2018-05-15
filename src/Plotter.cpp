#include "Plotter.hpp"
#include "Kinematics.hpp"

#define PEN_LOWER_POSITION 10000

/*******************************
 * Constructors
 *******************************/
Plotter::Plotter() {
  // Set up axes
  mXAxis = new StepperAxis("X", X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN, 500000, false);
  mYAxis = new StepperAxis("Y", Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN, 500000, true);
  mZAxis = new StepperAxis("Z", Z_STEP_PIN, Z_DIR_PIN, Z_ENABLE_PIN, Z_MIN_PIN, Z_MAX_PIN, 500000, true);
  // Home everything
  home();
  // Lower the bed away from the pen
  lowerBed();
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

void Plotter::drawRect(Point* origin, float length, float width) {
  Point* p2 = new Point(origin->x() + length, origin->y());
  Point* p3 = new Point(origin->x() + length, origin->y() + width);
  Point* p4 = new Point(origin->x(), origin->y()  + width);
  // Move to origin
  moveTo(origin);
  // Raise Bed to pen
  raiseBed();
  // Move to top right corner (length)
  moveTo(p2);
  // Move to bottom right corner (width)
  moveTo(p3);
  // Move to bottom left corner (-length)
  moveTo(p4);
  // Move to top left corner (-width)
  moveTo(origin);
  // Lower bed away from pen
  lowerBed();
}

void Plotter::drawTriangle(Point* p1, Point* p2, Point* p3) {
  moveTo(p1);
  raiseBed();
  moveTo(p2);
  moveTo(p3);
  moveTo(p1);
  lowerBed();
}

void Plotter::drawTriangle() {
  mXAxis->moveTo(6000);
  mYAxis->moveTo(6000);
  
  raiseBed();

  mXAxis->enable();
  mYAxis->enable();
  for (int i=0; i<2000; i++) {
    mXAxis->singleStep(Direction::AwayFromHome);
    mYAxis->singleStep(Direction::AwayFromHome);
  }
  for (int i=0; i<2000; i++) {
    mXAxis->singleStep(Direction::TowardsHome);
    mYAxis->singleStep(Direction::AwayFromHome);
  }
  for (int i=0; i<4000; i++) {
    mYAxis->singleStep(Direction::TowardsHome);
  }
  mXAxis->disable();
  mYAxis->disable();

  lowerBed();
}

void Plotter::drawCircle(Point* centre, float radius) {

}

void Plotter::drawCircle() {

}

void Plotter::raiseBed() {
  if (VERBOSE) Serial.println("Raising Bed");
  mZAxis->enable();
  mZAxis->home();
  mZAxis->disable();
}

void Plotter::lowerBed() {
  if (VERBOSE) Serial.println("Lowering Bed");
  mZAxis->moveTo(PEN_LOWER_POSITION);
}

void Plotter::moveTo(Point* toPoint) {
  if (VERBOSE) Serial.println("Move to " + toPoint->toString());

  // Current location
  Point* stepsHere = new Point(mXAxis->getCurrentPosition(), mYAxis->getCurrentPosition());
  Point* stepsThere = Kinematics::mm2Steps(toPoint);

  long deltaX = stepsThere->x() - stepsHere->x();
  long deltaY = stepsThere->y() - stepsHere->y();

  if (VERBOSE) {
    Serial.println("MoveTo: Axes: " + mXAxis->toString() + "," + mYAxis->toString());
    Serial.println("MoveTo: Current: " + String(stepsHere->x()) + "," + String(stepsHere->y()));
    Serial.println("MoveTo: Target: " + String(stepsThere->x()) + "," + String(stepsThere->y()));
    Serial.println("MoveTo: DeltaX: dx=" + String(deltaX) + ", dy=" + String(deltaY));
  }

  if (deltaX == 0 && deltaY == 0) {
    // We're already where we want to be
    return;
  } else if (deltaX == 0) {
    // It's a straight line along the Y Axis
    mYAxis->moveTo(stepsThere->y());
  } else if (deltaY == 0) {
    // It's a straight line along the X Axis
    mXAxis->moveTo(stepsThere->x());
  } else {
    // It's a diagonal line so we need to break it down
    // y = mx+b
    float m = (float) deltaY / (float) deltaX;
    float b = stepsHere->y() - m * stepsHere->x();

    // Work out the increment we need in X to get a single step increment in Y
    // And make sure it's going the right way!
    float xinc = abs(1/m) * (deltaX >=0 ? 1 : -1);
    float x = stepsHere->x();

    if (VERBOSE) Serial.println("MoveTo: DL: m=" + String(m) + " b=" + String(b) + " xinc=" + String(xinc));

    // Turn the motors on
    mXAxis->enable();
    mYAxis->enable();

    bool done = false;
    // Loop through sensible steps on the path (xinc)
    while(!done) {
      x = x + xinc;
      float y = m*x + b;
      long stepX = x;
      long stepY = y;
      mXAxis->moveTo(stepX, false);
      mYAxis->moveTo(stepY, false);
      if (stepX == (long) stepsThere->x()) done = true;
    }

    // Turn the motors off
    mXAxis->disable();
    mYAxis->disable();
  }
  if (VERBOSE) Serial.println("MoveTo: Final Axes: " + mXAxis->toString() + "," + mYAxis->toString());  
}

void Plotter::calibrate(Axis axis) {
  StepperAxis* stepperAxis;
  switch (axis) {
    case Axis::X:
      stepperAxis = mXAxis;
      // Move on to the paper
      mYAxis->moveTo(2000);
      break;
    case Axis::Y:
      stepperAxis = mYAxis;
      // Move on to the paper
      mXAxis->moveTo(2000);
      break;
    case Axis::Z:
      stepperAxis = mZAxis;
      break;
    default:
      stepperAxis = mXAxis;
      break;
  }
  
  stepperAxis->moveTo(2000);
  delay(5000);
  stepperAxis->moveTo(22000);
}

void Plotter::home() {
  if (VERBOSE) Serial.println("Home Everything");
  mXAxis->enable();
  mYAxis->enable();
  mZAxis->enable();
  while (!(mXAxis->isHome() && mYAxis->isHome() && mZAxis->isHome())) {
    mXAxis->singleStep(Direction::TowardsHome);
    mYAxis->singleStep(Direction::TowardsHome);
    mZAxis->singleStep(Direction::TowardsHome);
  }
  mXAxis->disable();
  mYAxis->disable();
  mZAxis->disable();
}