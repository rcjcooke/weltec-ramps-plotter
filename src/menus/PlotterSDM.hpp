#ifndef __PLOTTERSDM_H_INCLUDED__
#define __PLOTTERSDM_H_INCLUDED__

#include "SerialDisplayMenu.hpp"
#include "Plotter.hpp"

class PlotterSDM : public SerialDisplayMenu {

public:
  /*******************************
   * Constructors
   *******************************/
  PlotterSDM(SerialDisplayMenuConfiguration* configuration, Plotter* plotter, SerialDisplayMenu* origin, int8_t statusLineNumber, int8_t errorLineNumber);

protected:
  /*******************************
   * Actions
   *******************************/
  
  // This method is called on every loop while the menu is waiting for user input. It is here in case 
  // the system needs to keep something up to date while waiting.
  void controllerUpdate();
  // Puts together the one line status update string to show users
  String constructStatusLine();

  /*******************************
   * Member variables
   *******************************/
  // Pointer to the controller for passing to other menus
  Plotter* mPlotter;

private:
  
};

#endif // __PLOTTERSDM_H_INCLUDED__