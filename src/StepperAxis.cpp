#include "StepperAxis.hpp"

// Microseconds
#define MIN_STEP_DELAY 750

/*******************************
 * Constructors
 *******************************/  
StepperAxis::StepperAxis(int stepPin, int dirPin, int enablePin, int minPin, int maxPin, long maxSteps, bool invertDirection) {
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
void StepperAxis::singleStep(int direction) {
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
    digitalWrite(mDirPin, mInvertDirection ? !direction : direction);
    digitalWrite(mStepPin, HIGH);
    digitalWrite(mStepPin, LOW);
    mEarliestNextStepMicros = mEarliestNextStepMicros + MIN_STEP_DELAY;
    
    switch(direction) {
      case Direction::TowardsHome:
        mCurrentStepLocation--;
        if (digitalRead(mMinPin) == HIGH) {
          mHome = true;
          mCurrentStepLocation = 0;
        }
        break;
      case Direction::AwayFromHome:
        mCurrentStepLocation++;
        if (mCurrentStepLocation == mMaxSteps) {
          mAtMax = true;
        }
        break;
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