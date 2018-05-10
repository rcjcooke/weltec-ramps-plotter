#include "Plotter.hpp"
#include "Kinematics.hpp"

// X Axis 30000 steps = 222mm
// Y Axis 20000 steps = 150 mm

#define PEN_LOWER_POSITION 5000



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

// Adding some comments

void Plotter::drawRect() {
  // TODO: Add range error checking
  // Raise pen
  // Move to origin
  // Raise Bed to pen
  raiseBed();
  // Move to top right corner (length)
  // Move to bottom right corner (width)
  // Move to bottom left corner (-length)
  // Move to top left corner (-width)
  // Raise pen
}

void Plotter::drawRect(Point* origin, float length, float width) {
  // TODO: Add range error checking
  // Raise pen
  // Move to origin
  // Raise Bed to pen
  raiseBed();
  // Move to top right corner (length)
  // Move to bottom right corner (width)
  // Move to bottom left corner (-length)
  // Move to top left corner (-width)
  // Raise pen
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
  // Start on the circumference of the circle
  mXAxis->moveTo(5000);
  mYAxis->moveTo(10000);

  // (x – h)^2 + (y – k)^2 = r^2
  
  // Centre at 10000, 10000
  Point* centreOffset = new Point(10000, 10000);
  float radius = 5000;
  // Circle with a radus of 5000 steps
  long x = 0;
  while (true) {
    
  }
}

void Plotter::raiseBed() {
  mZAxis->enable();
  mZAxis->home();
  mZAxis->disable();
}

void Plotter::lowerBed() {
  if (VERBOSE) Serial.println("Lowering Bed");
  mZAxis->moveTo(PEN_LOWER_POSITION);
}

void Plotter::moveTo(Point* toPoint) {
  // Current location
  Point* stepsHere = new Point(mXAxis->getCurrentPosition(), mYAxis->getCurrentPosition());
  Point* stepsThere = Kinematics::mm2Steps(toPoint);

  long deltaX = stepsThere->x - stepsHere->x;
  long deltaY = stepsThere->y - stepsHere->y;

  if (deltaX == 0 && deltaY == 0) {
    // We're already where we want to be
    return;
  } else if (deltaX == 0) {
    // It's a straight line along the Y Axis
    mYAxis->moveTo(stepsThere->y);
  } else if (deltaY == 0) {
    // It's a straight line along the X Axis
    mXAxis->moveTo(stepsThere->x);
  } else {
    // It's a diagonal line so we need to break it down
    // y = mx+b
    float m = (deltaY) / (deltaX);
    float b = stepsHere->y - m * stepsHere->x;

    long xinc = 1/m;
    for (long x = stepsHere->x; x <= stepsThere->x; x = x + xinc) {
      mXAxis->moveTo(x);
      long y2 = m*(x+1) + b;
      mYAxis->moveTo(y2);
    }
  }
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