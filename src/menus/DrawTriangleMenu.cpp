#include "DrawTriangleMenu.hpp"

/*******************************
 * Constructors
 *******************************/

DrawTriangleMenu::DrawTriangleMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter) : PlotterSDM(configuration, plotter, origin, (int8_t) 2, (int8_t) 3) {
  mCurrentStage = 0;
}

/*******************************
 * Actions
 *******************************/

void DrawTriangleMenu::printMenu() {
  switch (mCurrentStage) {
    case 0:
      Serial << "  Type in point 1 in the form x,y in mm measured from home [20,20]: ";
      break;
    case 1:
      Serial << "  Type in point 2 in the form x,y in mm measured from home [40,50]: ";
      break;
    case 2:
      Serial << "  Type in point 3 in the form x,y in mm measured from home [30,35]: ";
      break;
  }
}

SerialDisplayMenu* DrawTriangleMenu::processUserInput(String userInput) {
  
  SerialDisplayMenu* returnMenu = this;

  Point* p;
  if (userInput.equals("")) {
    // Handle the defaults
    switch (mCurrentStage) {
      case 0: p = new Point(20,20); break;
      case 1: p = new Point(40,50); break;
      case 2: p = new Point(30,35); break;
    }
  } else {
    // Convert what the user has written in to a Point
    int commaIdx = userInput.indexOf(',');
    if (commaIdx == -1) {
      displayError("The value must be blank to accept the default, or x,y. You entered: " + userInput);
      return returnMenu;
    }
    String xStr = userInput.substring(0, commaIdx-1);
    String yStr = userInput.substring(commaIdx+1, userInput.length()-1);
    p = new Point(xStr.toFloat(), yStr.toFloat());
  }

  // Remember the point
  switch (mCurrentStage) {
    case 0: mP1 = p; break;
    case 1: mP2 = p; break;
    case 2: 
      mP3 = p; 
      mPlotter->drawTriangle(mP1, mP2, mP3);
      returnMenu = mOrigin;
      break;
  }

  mCurrentStage++;

  return returnMenu;
}