#include "DrawRectangleMenu.hpp"

/*******************************
 * Constructors
 *******************************/

DrawRectangleMenu::DrawRectangleMenu(SerialDisplayMenuConfiguration* configuration, SerialDisplayMenu* origin, Plotter* plotter) : PlotterSDM(configuration, plotter, origin, (int8_t) 2, (int8_t) 3) {
  mCurrentStage = 0;
}

/*******************************
 * Actions
 *******************************/

void DrawRectangleMenu::printMenu() {
  switch (mCurrentStage) {
    case 0:
      Serial << "  Type in the origin point in the form x,y in mm measured from home [30,30]: ";
      break;
    case 1:
      Serial << "  Type in length (along X) measured in mm [50]: ";
      break;
    case 2:
      Serial << "  Type in the width (along Y) measured in mm [40]: ";
      break;
  }
}

SerialDisplayMenu* DrawRectangleMenu::processUserInput(String userInput) {
  
  SerialDisplayMenu* returnMenu = this;

  Point* p;
  if (userInput.equals("")) {
    // Handle the defaults
    switch (mCurrentStage) {
      case 0: mOriginPoint = new Point(30,30); break;
      case 1: mLength = 50; break;
      case 2: mWidth = 40; break;
    }
  } else {
    switch (mCurrentStage) {
      case 0: 
        // Convert what the user has written in to a Point
        int commaIdx = userInput.indexOf(',');
        if (commaIdx == -1) {
          displayError("The value must be blank to accept the default, or x,y. You entered: " + userInput);
          return returnMenu;
        }
        mOriginPoint = new Point(userInput.substring(0, commaIdx-1).toFloat(), userInput.substring(commaIdx+1, userInput.length()-1).toFloat());
        break;
      case 1: 
        mLength = userInput.toFloat();
        break;
      case 2:
        mWidth = userInput.toFloat();
        break;
    }
  }

  if (mCurrentStage == 2) {
    mPlotter->drawRect(mOriginPoint, mLength, mWidth);
    returnMenu = mOrigin;
  }

  mCurrentStage++;

  return returnMenu;
}