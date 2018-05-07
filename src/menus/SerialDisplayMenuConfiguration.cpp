#include <stdint.h>

#include "SerialDisplayMenuConfiguration.hpp"

SerialDisplayMenuConfiguration::SerialDisplayMenuConfiguration(SerialDisplayType displayType, bool displayStatusLine, int userStatusUpdateFrequencyModulus) {
  mSerialDisplay = displayType;
  mDisplayStatusLine = displayStatusLine;
  mUserStatusUpdateFrequencyModulus = userStatusUpdateFrequencyModulus;
}

SerialDisplayType SerialDisplayMenuConfiguration::getSerialDisplayType() const {
  return mSerialDisplay;
}

bool SerialDisplayMenuConfiguration::getDisplayStatusLine() const {
  return mDisplayStatusLine;
}

int SerialDisplayMenuConfiguration::getUserStatusUpdateFrequencyModulus() const {
  return mUserStatusUpdateFrequencyModulus;
}
