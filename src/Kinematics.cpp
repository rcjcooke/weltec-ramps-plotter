
#include "Kinematics.hpp"

Point* Kinematics::mm2Steps(Point* mmPoint) {
  return new Point(mmPoint->x * X_RATIO, mmPoint->y * Y_RATIO);
}