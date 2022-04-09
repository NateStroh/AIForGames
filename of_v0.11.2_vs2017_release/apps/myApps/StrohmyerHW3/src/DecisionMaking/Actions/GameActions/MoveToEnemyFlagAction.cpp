#include "MoveToEnemyFlagAction.h"

#include "ofUtils.h"

TestAction::TestAction() {
  priority_ = 1;
  queued_time_ = ofGetCurrentTime().getAsMilliseconds();
  expiry_time_ = 10000;
  test_string_ = "default value";
}

TestAction::TestAction(std::string string) {
  priority_ = 1;
  queued_time_ = ofGetCurrentTime().getAsMilliseconds();
  expiry_time_ = 10000;
  test_string_ = string;
}

bool TestAction::CanInterupt() {
  return false;
}

bool TestAction::CanDoBoth(Action other) {
  return false;
}

bool TestAction::IsComplete() {
  return hasPrinted;
}

int TestAction::Execute() {
  printf("%s\n", test_string_.c_str());
  hasPrinted = true;
  return 0;
}
