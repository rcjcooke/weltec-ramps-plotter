#ifndef __KINEMATICS_H_INCLUDED__
#define __KINEMATICS_H_INCLUDED__

#include "Point.hpp"

class Kinematics {  

public:

  // Convert a point in millimeters from origin to a point in steps from origin
  static Point* mm2Steps(Point* mmPoint);

private: 

  // X Axis number of steps per millimeter
  static const float X_RATIO;
  // Y Axis number of steps per millimeter
  static const float Y_RATIO;
  
};

#endif // __KINEMATICS_H_INCLUDED__