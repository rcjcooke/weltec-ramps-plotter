#include "StepInstruction.hpp"

class TimeInstruction {

public:
  TimeInstruction(long timeMillis, StepInstruction* instructions[]);

  // Returns the set of instructions to execute at this time
  StepInstruction* getInstructions();

private:

  long mTimeMillis;
  StepInstruction* mStepInstructions[];

};