#ifndef __STEPPERAXIS_H_INCLUDED__
#define __STEPPERAXIS_H_INCLUDED__

#include <Arduino.h>
//#include <Eigen>
#include "Point.hpp"
#include "RAMPSController.hpp"

enum Direction : uint8_t {
  TowardsHome=HIGH,
  AwayFromHome=LOW
};

/**
 * Stepper Motor encapsulation.
 */
class StepperAxis {
public:
  /*******************************
   * Constructors
   *******************************/  
  StepperAxis(int stepPin, int dirPin, int enablePin, int minPin, int maxPin, long maxSteps, bool invertDirection);

  /*******************************
   * Accessors
   *******************************/
  // Return true if the axis is in the home position
  bool isHome() const;
  // True true if the axis is at it's maximum value
  bool isAtMax() const;

  /*******************************
   * Actions
   *******************************/
  // Single step
  void singleStep(int direction);
  // Move the stepper back to the home position
  void home();
  // Turn the power off
  void disable();
  // Turn the power on
  void enable();

protected:
private:
  /*******************************
   * Actions
   *******************************/

  /*******************************
   * Member variables (fields)
   *******************************/
  // Arduino Step Pin for Motor
  uint8_t mStepPin;
  uint8_t mDirPin;
  uint8_t mEnablePin;
  uint8_t mMinPin;
  uint8_t mMaxPin;
  long mMaxSteps;
  bool mInvertDirection;

  bool mAtMax;
  bool mHome;
  unsigned long mEarliestNextStepMicros;

  long mCurrentStepLocation;
};

#endif // __STEPPERAXIS_H_INCLUDED__