#include "TimeInstruction.hpp"

TimeInstruction::TimeInstruction(long timeMillis, StepInstruction* instructions[]) {
  mTimeMillis = timeMillis;
  mStepInstructions = instructions;
}

// Returns the set of instructions to execute at this time
StepInstruction* TimeInstruction::getInstructions() {
  return mStepInstructions;
}