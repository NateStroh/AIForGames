// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_Action
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_Action

namespace AI {

namespace DecisionMaking {

class Action {
 public:
  int priority_;
  float queued_time_;
  float expiry_time_;

  virtual bool CanInterupt();
  virtual bool CanDoBoth(Action other);
  virtual bool IsComplete();
  // 0 = success
  // 1 = fail
  // 2 = running
  // 3 = error
  virtual int Execute();
  bool operator<(const Action& other) const;

 private:
};

} // namespace DecisionMaking

} // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_Action
