#ifndef __DRAWMENU_H_INCLUDED__
#define __DRAWMENU_H_INCLUDED__

#include "PlotterSDM.hpp"

class DrawMenu : public PlotterSDM {

public:
  /*******************************
   * Constructors
   *******************************/
  DrawMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter);

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
  
};

#endif // __DRAWMENU_H_INCLUDED__