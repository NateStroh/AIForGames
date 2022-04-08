// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_MOVEMENTALGORITHMS_MOVEMENTALGORITHMS_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_MOVEMENTALGORITHMS_MOVEMENTALGORITHMS_H_

#include <vector>

#include "../GameObjects/Physics/Rigidbody.h"
#include "../GameObjects/Physics/SteeringOutput.h"

namespace AI {

namespace MovementAlgorithms {
SteeringOutput Seek(Rigidbody i_characterRigidbody, Rigidbody i_targetRigidbody,
                    float i_maxAcceleration);

SteeringOutput Flee(Rigidbody i_characterRigidbody, Rigidbody i_targetRigidbody,
                    float i_maxAcceleration);

SteeringOutput KinematicAlign(ofVec2f i_velocityToAlignTo);

SteeringOutput DynamicAlign(Rigidbody i_characterRigidbody,
                            Rigidbody i_targetRigidbody,
                            float i_maxAngularAcceleration, float i_maxRotation,
                            float targetRadius, float slowRadius,
                            float i_timeToTarget);

SteeringOutput PositionMatchingArrive(Rigidbody i_characterRigidbody,
                                      Rigidbody i_targetRigidbody,
                                      float i_maxAcceleration, float i_maxSpeed,
                                      float i_slowRadius, float i_targetRadius,
                                      float i_timeToTarget);

SteeringOutput DynamicWander(Rigidbody i_characterRigidbody, float i_maxRange,
                             float i_maxSpeed, ofVec2f i_offset);

SteeringOutput DynamicWanderFaceTarget(
    Rigidbody i_characterRigidbody, float i_maxRange, float i_maxSpeed,
    ofVec2f i_offset, float i_maxAngularAcceleration, float i_maxRotation,
    float i_targetRadius, float i_slowRadius, float i_timeToTarget);

SteeringOutput VelocityMatch(Rigidbody i_characterRigidbody,
                             Rigidbody i_targetRigidbody,
                             float i_maxAcceleration, float i_timeToTarget);

SteeringOutput DynamicPursue(Rigidbody i_characterRigidbody,
                             Rigidbody i_targetRigidbody, float i_maxSpeed,
                             float i_maxPredictionTime);

SteeringOutput DynamicEvade(Rigidbody i_characterRigidbody,
                            Rigidbody i_targetRigidbody,
                            float i_maxLinearAcceleration, float i_fleeRadius,
                            float i_decay);

SteeringOutput DynamicSeperate(Rigidbody i_characterRigidbody,
                               std::vector<Rigidbody> i_targetRigidbodys,
                               float i_maxAcceleration, float i_fleeRadius,
                               float i_decay);

SteeringOutput Face(Rigidbody i_characterRigidbody, Rigidbody i_targetRigidbody,
                    float i_maxAngularAcceleration, float i_maxRotation,
                    float i_targetRadius, float i_slowRadius,
                    float i_timeToTarget);

SteeringOutput LookWhereYouAreGoing(Rigidbody i_characterRigidbody,
                                    float i_maxAngularAcceleration,
                                    float i_maxRotation, float i_targetRadius,
                                    float i_slowRadius, float i_timeToTarget);

SteeringOutput Flock(Rigidbody i_characterRigidbody,
                     std::vector<Rigidbody> i_targetRigidbodys,
                     float i_maxAcceleration, float i_maxSpeed,
                     float i_slowRadius, float i_targetRadius,
                     float i_timeToTarget, float i_fleeRadius, float i_decay);

SteeringOutput FlockNoLeader(Rigidbody i_characterRigidbody,
                             std::vector<Rigidbody> i_targetRigidbodys,
                             float i_maxAcceleration, float i_maxSpeed,
                             float i_slowRadius, float i_targetRadius,
                             float i_timeToTarget, float i_fleeRadius,
                             float i_decay);

SteeringOutput FollowPath(Rigidbody* i_characterRigidbody,
                          std::vector<int> path,
                          int columns,
                          float tile_size,
                          float smoothing_radius,
                          float max_acceleration,
                          float max_speed,
                          float slow_radius,
                          float target_radius,
                          float time_to_target);

}  // namespace MovementAlgorithms

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_MOVEMENTALGORITHMS_MOVEMENTALGORITHMS_H_
