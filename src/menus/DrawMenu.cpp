#include "DrawMenu.hpp"

/*******************************
 * Constructors
 *******************************/

DrawMenu::DrawMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter) : PlotterSDM(configuration, plotter, origin, (int8_t) 11, (int8_t) 12) {
}

/*******************************
 * Actions
 *******************************/

void DrawMenu::printMenu() {
  Serial << "  Please choose a menu item by number." << endl << endl;
  Serial << "\t[1] Draw Rectangle" << endl;
  Serial << "\t[2] Draw Triangle" << endl;
  Serial << "\t[3] Draw Circle" << endl;
  Serial << "\t[4] Freehand" << endl;
  Serial << "\t[5] Return to Main Menu" << endl << endl;
  Serial << "  Choice (number followed by enter): ";
}

SerialDisplayMenu* DrawMenu::processUserInput(long userInput) {
  
  SerialDisplayMenu* returnMenu = this;
  if (userInput == 1) {
    mPlotter->drawRect();
    returnMenu = this;
  } else if (userInput == 2) {
    mPlotter->drawTriangle();
    returnMenu = this;
  } else if (userInput == 3) {
    returnMenu = this;
  } else if (userInput == 4) {
    returnMenu = this;
  } else if (userInput == 5) {
    returnMenu = mOrigin;
  } else {
    displayError("Please pick either 1, 2, 3, 4 or 5. You entered " + String(userInput));
  }
  return returnMenu;
}