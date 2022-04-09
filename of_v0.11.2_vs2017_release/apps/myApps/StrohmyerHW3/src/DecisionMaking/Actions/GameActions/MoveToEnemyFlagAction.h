#pragma once

#include <iostream>
#include "..\Action.h"

class TestAction : public AI::DecisionMaking::Action {
 public:
  std::string test_string_;
  
  TestAction();
  TestAction(std::string string);

  bool CanInterupt();
  bool CanDoBoth(Action other);
  bool IsComplete();
  int Execute();
 private:
  bool hasPrinted = false;
};
