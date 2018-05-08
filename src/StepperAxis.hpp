#ifndef __STEPPERAXIS_H_INCLUDED__
#define __STEPPERAXIS_H_INCLUDED__

#include <Arduino.h>
//#include <Eigen>
#include "Point.hpp"
#include "RAMPSController.hpp"
#include "Logging.hpp"


enum class Direction : uint8_t {
  AwayFromHome=0x0,
  TowardsHome=0x1
};

/**
 * Stepper Motor encapsulation.
 */
class StepperAxis {
public:
  /*******************************
   * Constructors
   *******************************/  
  StepperAxis(String id, uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t minPin, uint8_t maxPin, long maxSteps, bool invertDirection);

  /*******************************
   * Accessors
   *******************************/
  // Return true if the axis is in the home position
  bool isHome() const;
  // True true if the axis is at it's maximum value
  bool isAtMax() const;
  // Get the current position of this axis as measured in Steps from Home
  long getCurrentPosition() const;
  // Returns a string representation identifying this Stepper Axis
  String toString();

  /*******************************
   * Actions
   *******************************/
  // Single step
  void singleStep(Direction direction);
  // Move the stepper back to the home position
  void home();
  // Move to a specific position / measured in steps
  void moveTo(long position);
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
  // A Unique identifier for this axis to refer to it in logging
  String mId;

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
  unsigned long mEarliestNextHalfStepMicros;

  long mCurrentStepLocation;
};

#endif // __STEPPERAXIS_H_INCLUDED__