#ifndef __PLOTTER_H_INCLUDED__
#define __PLOTTER_H_INCLUDED__

#include <Arduino.h>
//#include <Eigen>
#include "Point.hpp"
#include "RAMPSController.hpp"

/**
 * Stepper Motor encapsulation.
 */
class StepperAxis {
public:
  /*******************************
   * Constructors
   *******************************/  
  StepperAxis(int stepPin, int dirPin, int enablePin, int minPin, int maxPin);

  /*******************************
   * Actions
   *******************************/
  void singleStep();

protected:
private:
  /*******************************
   * Actions
   *******************************/
  // Raise the pen up so it's away from the paper
  void raise();
  // Lower the pen onto the paper
  void lower();
  // Move the pen from it's current location to the specified point
  void move(Point toPoint);
  // Move the pen to the home position
  void home();

  /*******************************
   * Member variables (fields)
   *******************************/
  // Arduino Step Pin for Motor
  int mStepPin;
  int mDirPin;
  int mEnablePin;
  int mMinPin;
  int mMaxPin;

};

#endif // __PLOTTER_H_INCLUDED__