#ifndef __DRAWRECTANGLEMENU_H_INCLUDED__
#define __DRAWRECTANGLEMENU_H_INCLUDED__

#include "PlotterSDM.hpp"

class DrawRectangleMenu : public PlotterSDM {

public:
  /*******************************
   * Constructors
   *******************************/
  DrawRectangleMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter);

  /*******************************
   * Actions
   *******************************/
  // Processes user input
  SerialDisplayMenu* processUserInput(String userInput);

protected:
  /*******************************
   * Actions
   *******************************/
  
  // Prints the menu out to the serial interface
  void printMenu();
  
  // The current stage of the menu
  int mCurrentStage;
  // The measurements for the rectangle
  Point* mOriginPoint;
  float mLength;
  float mWidth;
};

#endif // __DRAWRECTANGLEMENU_H_INCLUDED__