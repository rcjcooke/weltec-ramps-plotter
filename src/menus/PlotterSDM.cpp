#include "PlotterSDM.hpp"

/*******************************
 * Constructors
 *******************************/

PlotterSDM::PlotterSDM(SerialDisplayMenuConfiguration* configuration, Plotter* plotter, SerialDisplayMenu* origin, int8_t statusLineNumber, int8_t errorLineNumber) : SerialDisplayMenu(configuration, origin, (int8_t) 8, (int8_t) 9) {
  mPlotter = plotter;
}

/*******************************
 * Actions
 *******************************/
void PlotterSDM::controllerUpdate() {
  // Don't need to do anything but we need to implement it to satisfy menu interface
}

String PlotterSDM::constructStatusLine() {
  // TODO: Sort this out
  String statusLine = "";
  return statusLine;
}