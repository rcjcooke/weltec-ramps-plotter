#include "StepperAxis.hpp"

// Microseconds
#define MIN_STEP_DELAY 750

/*******************************
 * Constructors
 *******************************/  
StepperAxis::StepperAxis(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t minPin, uint8_t maxPin, long maxSteps, bool invertDirection) {
  mStepPin = stepPin;
  mDirPin = dirPin;
  mEnablePin = enablePin;
  mMinPin = minPin;
  mMaxPin = maxPin;
  mMaxSteps = maxSteps;
  mInvertDirection = invertDirection;

  mEarliestNextStepMicros = micros();
  mCurrentStepLocation = 0;
  mHome = false;
  mAtMax = false;

  // Set up the modes
  pinMode(mStepPin, OUTPUT);
  pinMode(mDirPin, OUTPUT);
  pinMode(mEnablePin, OUTPUT);

  // Switch activates HIGH
  pinMode(mMinPin, INPUT_PULLUP);
  pinMode(mMaxPin, INPUT_PULLUP);

  // Disable power to safeguard from thermal overload
  disable();
}

/*******************************
 * Accessors
 *******************************/
bool StepperAxis::isHome() const {
  return mHome;
}

bool StepperAxis::isAtMax() const {
  return mAtMax;
}

long StepperAxis::getCurrentPosition() const {
  return mCurrentStepLocation;  
}

/*******************************
 * Actions
 *******************************/
void StepperAxis::singleStep(Direction direction) {
  // Wait until the earliest time we can next step
  while (micros() < mEarliestNextStepMicros) {}

  // Make sure we don't overshoot the end of the axis
  bool okToMove = false;
  if (direction == Direction::TowardsHome && !isHome()) {
    okToMove = true;
  } else if (direction == Direction::AwayFromHome && !isAtMax()) {
    okToMove = true;
  }

  if (okToMove) {
    // Make sure we've got the right direction (some axes are inverted)
    uint8_t directionToMove = direction;
    if (mInvertDirection) {
      if (direction == HIGH) directionToMove = LOW;
      else directionToMove = HIGH;
    }
    // You gotta move it, move it
    digitalWrite(mDirPin, directionToMove);
    digitalWrite(mStepPin, HIGH);
    digitalWrite(mStepPin, LOW);
    // Make sure we don't move too quickly next time
    mEarliestNextStepMicros = mEarliestNextStepMicros + MIN_STEP_DELAY;
    
    // Update location
    switch(direction) {
      case Direction::TowardsHome:
        mCurrentStepLocation--;
        break;
      case Direction::AwayFromHome:
        mCurrentStepLocation++;
        break;
    }

    // Check axis limits
    if (digitalRead(mMinPin) == HIGH) {
      mCurrentStepLocation = 0;
      mHome = true;
      mAtMax = false;
    } else if (mCurrentStepLocation == mMaxSteps) {
      mHome = false;
      mAtMax = true;
    } else {
      mHome = false;
      mAtMax = false;
    }
  }
}

void StepperAxis::home() {
    while (!isHome()) {
      singleStep(Direction::TowardsHome);
  }
}

void StepperAxis::enable() {
  digitalWrite(mEnablePin, LOW);
}

void StepperAxis::disable() {
  digitalWrite(mEnablePin, HIGH);
}

void StepperAxis::moveTo(long position) {
  enable();
  Direction d;
  if (mCurrentStepLocation > position) {
    d = Direction::TowardsHome;
  } else {
    d = Direction::AwayFromHome;
  }

  while (mCurrentStepLocation != position) {
    singleStep(d);
  }
  disable();
}