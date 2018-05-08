#include "StepperAxis.hpp"

// Microseconds
#define MIN_HALF_STEP_DELAY 100

/*******************************
 * Constructors
 *******************************/  
StepperAxis::StepperAxis(String id, uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t minPin, uint8_t maxPin, long maxSteps, bool invertDirection) {
  mId = id;
  mStepPin = stepPin;
  mDirPin = dirPin;
  mEnablePin = enablePin;
  mMinPin = minPin;
  mMaxPin = maxPin;
  mMaxSteps = maxSteps;
  mInvertDirection = invertDirection;

  mEarliestNextHalfStepMicros = micros();
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
String directionToString(Direction direction) {
  switch (direction) {
    case Direction::AwayFromHome: return "AwayFromHome";
    case Direction::TowardsHome: return "TowardsHome";
    default: return "IllegalDirection";
  }
}

String StepperAxis::toString() {
  return mId + "@" + String(mCurrentStepLocation) + (mHome ? "@H" : "") + (mAtMax ? "@M" : "");
}

void StepperAxis::singleStep(Direction direction) {
  if (DEBUG) Serial.println(this->toString() + ": Single Step " + directionToString(direction));
  // Wait until the earliest time we can next step
  while (micros() < mEarliestNextHalfStepMicros) {}

  // Make sure we don't overshoot the end of the axis
  bool okToMove = false;
  if (direction == Direction::TowardsHome && !isHome()) {
    okToMove = true;
  } else if (direction == Direction::AwayFromHome && !isAtMax()) {
    okToMove = true;
  } else {
    if (DEBUG) Serial.println(this->toString() + ": Single Step NOT OK TO MOVE " + directionToString(direction));    
  }

  if (okToMove) {
    // Make sure we've got the right direction (some axes are inverted)
    Direction directionToMove = direction;
    if (mInvertDirection) {
      if (direction == Direction::AwayFromHome) directionToMove = Direction::TowardsHome;
      else directionToMove = Direction::AwayFromHome;
    }
    // You gotta move it, move it
    digitalWrite(mDirPin, static_cast<uint8_t>(directionToMove));
    digitalWrite(mStepPin, HIGH);
    mEarliestNextHalfStepMicros = micros() + MIN_HALF_STEP_DELAY;
    while (micros() < mEarliestNextHalfStepMicros) {}
    digitalWrite(mStepPin, LOW);
    // Make sure we don't move too quickly next time
    mEarliestNextHalfStepMicros = micros() + MIN_HALF_STEP_DELAY;
    
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
      // Only reset this value if we're moving in this direction, otherwise we just haven't left the switch yet
      if (direction == Direction::TowardsHome) {
        if (VERBOSE) Serial.println(this->toString() + ": Reached Home moving TowardsHome");
        mCurrentStepLocation = 0;
        mHome = true;
      } else {
        // We've just stepped away from home - it's just that the switch happens to be engaged still
        mHome = false;
      }
      mAtMax = false;
    } else if (mCurrentStepLocation == mMaxSteps) {
      if (VERBOSE) Serial.println(this->toString() + ": Reached Max moving " + directionToString(direction));
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

  if (VERBOSE) Serial.println(this->toString() + ": Move to: " + String(position) + " " + directionToString(d));

  while (mCurrentStepLocation != position) {
    singleStep(d);
  }
  if (VERBOSE) Serial.println(this->toString() + ": Move to: Reached required position");

  disable();
}