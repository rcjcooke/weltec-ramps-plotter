#include "StepperAxis.hpp"

/*******************************
 * Constructors
 *******************************/  
StepperAxis::StepperAxis(int stepPin, int dirPin, int enablePin, int minPin, int maxPin) {
  mStepPin = stepPin;
  mDirPin = dirPin;
  mEnablePin = enablePin;
  mMinPin = minPin;
  mMaxPin = maxPin; 
}

/*******************************
 * Actions
 *******************************/
void StepperAxis::singleStep(int direction) {
  digitalWrite(mDirPin, direction);
  digitalWrite(mStepPin, HIGH);
  digitalWrite(mStepPin, LOW);
}

void StepperAxis::home() {
  
}
