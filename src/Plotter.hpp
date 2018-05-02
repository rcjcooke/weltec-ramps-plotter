#ifndef __PLOTTER_H_INCLUDED__
#define __PLOTTER_H_INCLUDED__

#include <Arduino.h>
//#include <Eigen>
#include "Point.hpp"
#include "RAMPSController.hpp"
#include "StepperAxis.hpp"

/**
 * Plotter encapsulation. All arguments in millimeters unless otherwise specified.
 */
class Plotter {
public:
  /*******************************
   * Constructors
   *******************************/
  Plotter();

  /*******************************
   * Actions
   *******************************/
  // Calculates the transform that would be required to level the bed
  void calibrateBedLevel();
  // Draws a rectangle
  void drawRect(Point* origin, float length, float width);
  // Draws a triangle
  void drawTriangle(Point* p1, Point* p2, Point* p3);
  // Draws a circle
  void drawCircle(Point* centre, float radius);

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
  void move(Point* toPoint);
  // Move the pen to the home position
  void home();

  /*******************************
   * Member variables (fields)
   *******************************/
  // X Axis Stepper Motor RAMPSController
  StepperAxis* mXAxis;
  // Y Axis Stepper Motor RAMPSController
  StepperAxis* mYAxis;
  // Z Axis Stepper Motor RAMPSController
  StepperAxis* mZAxis;  
  
  // The current location of the pen
  Point* mCurrentLocation;
  // True when the pen is in the "lowered" state
  bool mLowered;
  // The bed levelling transform matrix
//  MatrixXd mBedLevellingTransform;

};

#endif // __PLOTTER_H_INCLUDED__