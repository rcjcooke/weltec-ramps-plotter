#include "MainMenu.hpp"
#include "DrawMenu.hpp"

/*******************************
 * Constructors
 *******************************/

MainMenu::MainMenu(SerialDisplayMenuConfiguration* configuration, Plotter* plotter) : PlotterSDM(configuration, plotter, NULL, (int8_t) 8, (int8_t) 9) {}

/*******************************
 * Actions
 *******************************/

void MainMenu::printMenu() {
  Serial << "  Please choose a menu item by number." << endl << endl;
  Serial << "\t[1] Level Bed" << endl;
  Serial << "\t[2] Calibrate Axes" << endl;
  Serial << "\t[3] Draw" << endl << endl;
  Serial << "  Choice (number followed by enter): ";
}

SerialDisplayMenu* MainMenu::processUserInput(String userInput) {
  
  SerialDisplayMenu* returnMenu = this;
  if (userInput.equals("1")) {
    displayError("Not implemented yet");
  } else if (userInput.equals("2")) {
    displayError("Not implemented yet");
  } else if (userInput.equals("3")) {
    returnMenu = new DrawMenu(getSerialDisplayMenuConfiguration(), this, mPlotter);
  } else {
    displayError("Please pick either 1, 2 or 3. You entered " + String(userInput));
  }
  return returnMenu;
}