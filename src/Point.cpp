#include "Point.hpp"

Point::Point(float x, float y) {
  mX = x;
  mY = y;
}

float Point::x() const {
  return mX;
}
float Point::y() const {
  return mY;
}

Point* Point::translate(float x, float y) {
  return new Point(mX + x, mY + y);
}