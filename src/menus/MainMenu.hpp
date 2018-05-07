#ifndef __MAINMENU_H_INCLUDED__
#define __MAINMENU_H_INCLUDED__

#include "PlotterSDM.hpp"

class MainMenu : public PlotterSDM {

public:
  /*******************************
   * Constructors
   *******************************/
  MainMenu(SerialDisplayMenuConfiguration* configuration, Plotter* plotter);

  /*******************************
   * Actions
   *******************************/
  // Processes user input
  SerialDisplayMenu* processUserInput(long userInput);

protected:
  /*******************************
   * Actions
   *******************************/
  
  // Prints the menu out to the serial interface
  void printMenu();

};

#endif // __MAINMENU_H_INCLUDED__