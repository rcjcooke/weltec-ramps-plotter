#include "StepperAxis.hpp"

#define MIN_STEP_DELAY 5

/*******************************
 * Constructors
 *******************************/  
StepperAxis::StepperAxis(int stepPin, int dirPin, int enablePin, int minPin, int maxPin, long maxSteps) {
  mStepPin = stepPin;
  mDirPin = dirPin;
  mEnablePin = enablePin;
  mMinPin = minPin;
  mMaxPin = maxPin;
  mEarliestNextStepMillis = millis();
  mMaxSteps = maxSteps;

  mCurrentStepLocation = 0;

  // Set up the modes
  pinMode(mStepPin, OUTPUT);
  pinMode(mDirPin, OUTPUT);
  pinMode(mEnablePin, OUTPUT);

  // Switch activates HIGH
  pinMode(mMinPin, INPUT_PULLUP);
  pinMode(mMaxPin, INPUT_PULLUP);

  // Power it up
  digitalWrite(mEnablePin, LOW);
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

/*******************************
 * Actions
 *******************************/
void StepperAxis::singleStep(int direction) {
  // Wait until the earliest time we can next step
  while (millis() < mEarliestNextStepMillis) {}

  // Make sure we don't overshoot the end of the axis
  bool okToMove = false;
  if (direction == Direction::TowardsHome && !isHome()) {
    okToMove = true;
  } else if (direction == Direction::AwayFromHome && !isAtMax()) {
    okToMove = true;
  }

  if (okToMove) {
    digitalWrite(mDirPin, direction);
    digitalWrite(mStepPin, HIGH);
    digitalWrite(mStepPin, LOW);
    mEarliestNextStepMillis = mEarliestNextStepMillis + MIN_STEP_DELAY;
  }

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

void StepperAxis::home() {
    while (!isHome()) {
      singleStep(Direction::TowardsHome);
  }
}