#ifndef __POINT_H_INCLUDED__
#define __POINT_H_INCLUDED__

#include <Arduino.h>

/**
 * Encapsulation of an immuteable 2D Point
 */
class Point {

public:
  Point(float x, float y);

  float x() const;
  float y() const;

  Point* translate(float x, float y);

  String toString();

private:
  float mX;
  float mY;
};

#endif // __POINT_H_INCLUDED__