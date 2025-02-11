#include "Kinematics.hpp"

// X Axis 30000 steps = 222mm
// Y Axis 20000 steps = 150 mm

// X Axis number of steps per millimeter
const float Kinematics::X_RATIO = 30000/222;
// Y Axis number of steps per millimeter
const float Kinematics::Y_RATIO = 20000/150;

Point* Kinematics::mm2Steps(Point* mmPoint) {
  return new Point(mmPoint->x() * Kinematics::X_RATIO, mmPoint->y() * Kinematics::Y_RATIO);
}