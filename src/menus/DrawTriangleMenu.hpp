#ifndef __DRAWTRIANGLEMENU_H_INCLUDED__
#define __DRAWTRIANGLEMENU_H_INCLUDED__

#include "PlotterSDM.hpp"

class DrawTriangleMenu : public PlotterSDM {

public:
  /*******************************
   * Constructors
   *******************************/
  DrawTriangleMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter);

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
  // The points of the triangle
  Point* mP1;
  Point* mP2;
  Point* mP3;
};

#endif // __DRAWTRIANGLEMENU_H_INCLUDED__