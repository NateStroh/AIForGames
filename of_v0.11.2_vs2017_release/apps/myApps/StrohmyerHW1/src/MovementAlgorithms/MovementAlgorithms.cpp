// copyright 2022 Nate Strohmyer

#include "MovementAlgorithms.h"
#include "math\ofMath.h"

AI::SteeringOutput AI::MovementAlgorithms::Seek(Rigidbody i_characterRigidbody,
                                                Rigidbody i_targetRigidbody,
                                                float i_maxAcceleration) {
  ofVec2f seekVector = i_targetRigidbody.position
    - i_characterRigidbody.position;

  seekVector = seekVector.normalize();

  seekVector *= i_maxAcceleration;

  return SteeringOutput(seekVector, 0.0f);
}

AI::SteeringOutput AI::MovementAlgorithms::Flee(Rigidbody i_characterRigidbody,
                                                Rigidbody i_targetRigidbody,
                                                float i_maxAcceleration) {
  ofVec2f seekVector = i_characterRigidbody.position
    - i_targetRigidbody.position;

  seekVector = seekVector.normalize();

  seekVector *= i_maxAcceleration;

  return SteeringOutput(seekVector, 0.0f);
}

AI::SteeringOutput AI::MovementAlgorithms::KinematicAlign(
  ofVec2f i_velocityToAlignTo) {
  return SteeringOutput(ofVec2f(0, 0), atan2(i_velocityToAlignTo.y,
  i_velocityToAlignTo.x));
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicAlign(
  Rigidbody i_characterRigidbody,
  Rigidbody i_targetRigidbody,
  float i_maxAngularAcceleration,
  float i_maxRotation,
  float i_targetRadius,
  float i_slowRadius,
  float i_timeToTarget) {
  float rotation = i_targetRigidbody.orientation
    - i_characterRigidbody.orientation;

  rotation = ofWrapRadians(rotation);
  float rotationSize = abs(rotation);

  float targetRotation = 0;
  if (rotationSize < ofDegToRad(i_targetRadius))
    return SteeringOutput(ofVec2f(0, 0), 0);
  if (rotationSize > ofDegToRad(i_slowRadius))
    targetRotation = i_maxRotation;
  else
    targetRotation = i_maxRotation * rotationSize / ofDegToRad(i_slowRadius);

  targetRotation *= rotation / rotationSize;

  float angularAcceleration = targetRotation - i_characterRigidbody.rotation;
  angularAcceleration /= i_timeToTarget;

  float angularAcc = abs(angularAcceleration);
  if (angularAcc > i_maxAngularAcceleration) {
    angularAcceleration /= angularAcceleration;
    angularAcceleration *= i_maxAngularAcceleration;
  }

  return SteeringOutput(ofVec2f(0, 0), angularAcceleration);
}

AI::SteeringOutput AI::MovementAlgorithms::PositionMatchingArrive(
    Rigidbody i_characterRigidbody,
    Rigidbody i_targetRigidbody,
    float i_maxAcceleration,
    float i_maxSpeed,
    float i_slowRadius,
    float i_targetRadius,
    float i_timeToTarget) {
  ofVec2f direction = (i_targetRigidbody.position
    - i_characterRigidbody.position);
  float distance = direction.length();
  float targetSpeed = 0;

  if (distance < i_targetRadius)
    return SteeringOutput(ofVec2f(0, 0), 0);
  if (distance > i_slowRadius)
    targetSpeed = i_maxSpeed;
  else
    targetSpeed = i_maxSpeed * distance / i_slowRadius;

  ofVec2f veleocityDiff = direction.getNormalized();
  veleocityDiff *= targetSpeed;
  ofVec2f linearAcceleration = veleocityDiff
    - i_characterRigidbody.velocity;
  linearAcceleration /= i_timeToTarget;

  if (linearAcceleration.length() > i_maxAcceleration) {
    linearAcceleration.normalize();
    linearAcceleration *= i_maxAcceleration;
  }

  return SteeringOutput(linearAcceleration, 0);
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicWander(
    Rigidbody i_characterRigidbody,
    float i_maxRange,
    float i_maxSpeed,
    ofVec2f i_offset) {
  float rotationSize = abs(ofDegToRad(i_maxRange
    - i_characterRigidbody.orientation));

  rotationSize *= ofRandomf();
  rotationSize += i_characterRigidbody.orientation;

  ofVec2f newVector(cos((rotationSize)), sin((rotationSize)));
  newVector *= i_offset;
  newVector += i_characterRigidbody.position;

  return Seek(i_characterRigidbody, Rigidbody(newVector, 0), i_maxSpeed);
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicWanderFaceTarget(
    Rigidbody i_characterRigidbody,
    float i_maxRange,
    float i_maxSpeed,
    ofVec2f i_offset,
    float i_maxAngularAcceleration,
    float i_maxRotation,
    float i_targetRadius,
    float i_slowRadius,
    float i_timeToTarget) {
  float rotationSize = abs(ofDegToRad(i_maxRange
    - i_characterRigidbody.orientation));
  rotationSize *= ofRandomf();
  rotationSize += i_characterRigidbody.orientation;

  ofVec2f newVector(cos((rotationSize)), sin((rotationSize)));
  newVector *= i_offset;
  newVector += i_characterRigidbody.position;

  Rigidbody newPosition(newVector, 0);
  SteeringOutput output = Seek(i_characterRigidbody,
      newPosition,
      i_maxSpeed);
  output.rotationAcceleration += Face(i_characterRigidbody,
      newPosition,
      i_maxAngularAcceleration,
      i_maxRotation,
      i_targetRadius,
      i_slowRadius,
      i_timeToTarget).rotationAcceleration;

  return output;
}

AI::SteeringOutput AI::MovementAlgorithms::VelocityMatch(
    Rigidbody i_characterRigidbody,
    Rigidbody i_targetRigidbody,
    float i_maxAcceleration,
    float i_timeToTarget) {
  ofVec2f linearAcceleration = i_targetRigidbody.velocity
    - i_characterRigidbody.velocity;
  linearAcceleration /= i_timeToTarget;

  if (linearAcceleration.length() > i_maxAcceleration) {
    linearAcceleration.normalize();
    linearAcceleration *= i_maxAcceleration;
  }

  return SteeringOutput(linearAcceleration, 0);
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicPursue(
    Rigidbody i_characterRigidbody,
    Rigidbody i_targetRigidbody,
    float i_maxSpeed,
    float i_maxPredictionTime) {
  ofVec2f direction = i_characterRigidbody.position
    - i_targetRigidbody.position;
  float distance = direction.length();

  float characterSpeed = i_characterRigidbody.velocity.length();

  float predictionTime = 0;
  if (characterSpeed >= distance / i_maxPredictionTime) {
    predictionTime = i_maxPredictionTime;
  } else {
    predictionTime = distance / (characterSpeed + .001);
  }

  Rigidbody seekRigidBody = i_targetRigidbody;
  seekRigidBody.position += (i_targetRigidbody.velocity * predictionTime);
  return Seek(i_characterRigidbody, seekRigidBody, i_maxSpeed);
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicEvade(
    Rigidbody i_characterRigidbody, Rigidbody i_targetRigidbody,
    float i_maxLinearAcceleration, float i_fleeRadius, float i_decay) {
  float runAwaySpeed = 0;
  ofVec2f direction =
      (i_targetRigidbody.position - i_characterRigidbody.position);
  float distance = direction.length();

  if (distance >= i_fleeRadius) {
    runAwaySpeed = 0;
  } else {
    float repulsionFactor = i_decay / (distance * distance);
    if (repulsionFactor > i_maxLinearAcceleration)
      runAwaySpeed = i_maxLinearAcceleration;
    else
      runAwaySpeed = repulsionFactor;
  }

  return Flee(i_characterRigidbody, i_targetRigidbody, runAwaySpeed);
}

AI::SteeringOutput AI::MovementAlgorithms::DynamicSeperate(
    Rigidbody i_characterRigidbody, std::vector<Rigidbody> i_targetRigidbodys,
    float i_maxAcceleration, float i_fleeRadius, float i_decay) {
  SteeringOutput returnSteering;

  float strength = 0;
  for (Rigidbody target : i_targetRigidbodys) {
    returnSteering.linearAcceleration +=
        AI::MovementAlgorithms::DynamicEvade(i_characterRigidbody, target,
                                             i_maxAcceleration, i_fleeRadius,
                                             i_decay)
            .linearAcceleration;

    if (returnSteering.linearAcceleration.x > i_maxAcceleration)
      returnSteering.linearAcceleration.x = i_maxAcceleration;
    if (returnSteering.linearAcceleration.y > i_maxAcceleration)
      returnSteering.linearAcceleration.y = i_maxAcceleration;
  }

  return SteeringOutput(returnSteering);
}

AI::SteeringOutput AI::MovementAlgorithms::Face(
    Rigidbody i_characterRigidbody, Rigidbody i_targetRigidbody,
    float i_maxAngularAcceleration, float i_maxRotation, float i_targetRadius,
    float i_slowRadius, float i_timeToTarget) {
  ofVec2f direction =
      (i_targetRigidbody.position - i_characterRigidbody.position);

  if (direction.length() < .001) return SteeringOutput();

  Rigidbody rigidbody = i_targetRigidbody;
  rigidbody.orientation = atan2(direction.y, direction.x);
  return DynamicAlign(i_characterRigidbody, rigidbody, i_maxAngularAcceleration,
                      i_maxRotation, i_targetRadius, i_slowRadius,
                      i_timeToTarget);
}

AI::SteeringOutput AI::MovementAlgorithms::LookWhereYouAreGoing(
    Rigidbody i_characterRigidbody, float i_maxAngularAcceleration,
    float i_maxRotation, float i_targetRadius, float i_slowRadius,
    float i_timeToTarget) {
  if (i_characterRigidbody.velocity.length() < .001) return SteeringOutput();

  Rigidbody rigidbody(ofVec2f(), atan2(i_characterRigidbody.velocity.y,
                                       i_characterRigidbody.velocity.x));
  return DynamicAlign(i_characterRigidbody, rigidbody, i_maxAngularAcceleration,
                      i_maxRotation, i_targetRadius, i_slowRadius,
                      i_timeToTarget);
}

AI::SteeringOutput AI::MovementAlgorithms::Flock(
    Rigidbody i_characterRigidbody, std::vector<Rigidbody> i_targetRigidbodys,
    float i_maxAcceleration, float i_maxSpeed, float i_slowRadius,
    float i_targetRadius, float i_timeToTarget, float i_fleeRadius,
    float i_decay) {
  SteeringOutput blendedOutput;
  Rigidbody centroid;

  // getting centroid position
  float totalMassOfFlock = 0;
  for (Rigidbody target : i_targetRigidbodys) {
    centroid.position.x += target.mass * target.position.x;
    centroid.position.y += target.mass * target.position.y;
    totalMassOfFlock += target.mass;
  }
  centroid.position /= totalMassOfFlock;

  // getting centroid velocity
  for (Rigidbody target : i_targetRigidbodys) {
    centroid.velocity.x += target.mass * target.velocity.x;
    centroid.velocity.y += target.mass * target.velocity.y;
  }
  centroid.velocity /= totalMassOfFlock;

  // getting all movement algorithms
  SteeringOutput seperationSteering =
      DynamicSeperate(i_characterRigidbody, i_targetRigidbodys,
                      i_maxAcceleration, i_fleeRadius, i_decay);
  SteeringOutput velocityMatchSteering = VelocityMatch(
      i_characterRigidbody, centroid, i_maxAcceleration, i_timeToTarget);
  SteeringOutput arriveSteering = PositionMatchingArrive(
      i_characterRigidbody, centroid, i_maxAcceleration, i_maxSpeed,
      i_slowRadius, i_slowRadius, i_timeToTarget);

  // blending different outputs together
  blendedOutput.linearAcceleration +=
      seperationSteering.linearAcceleration * 2.0f;
  blendedOutput.linearAcceleration +=
      velocityMatchSteering.linearAcceleration * 0.5f;
  blendedOutput.linearAcceleration += arriveSteering.linearAcceleration * 0.6f;

  return blendedOutput;
}

AI::SteeringOutput AI::MovementAlgorithms::FlockNoLeader(
    Rigidbody i_characterRigidbody, std::vector<Rigidbody> i_targetRigidbodys,
    float i_maxAcceleration, float i_maxSpeed, float i_slowRadius,
    float i_targetRadius, float i_timeToTarget, float i_fleeRadius,
    float i_decay) {
  SteeringOutput blendedOutput;
  Rigidbody centroid;

  // getting centroid position
  float totalMassOfFlock = 0;
  for (Rigidbody target : i_targetRigidbodys) {
    centroid.position.x += target.mass * target.position.x;
    centroid.position.y += target.mass * target.position.y;
    totalMassOfFlock += target.mass;
  }
  centroid.position /= totalMassOfFlock;

  // getting centroid velocity
  for (Rigidbody target : i_targetRigidbodys) {
    centroid.velocity.x += target.mass * target.velocity.x;
    centroid.velocity.y += target.mass * target.velocity.y;
  }
  centroid.velocity /= totalMassOfFlock;

  // getting all movement algorithms
  SteeringOutput seperationSteering =
      DynamicSeperate(i_characterRigidbody, i_targetRigidbodys,
                      i_maxAcceleration, i_fleeRadius, i_decay);
  SteeringOutput velocityMatchSteering = VelocityMatch(
      i_characterRigidbody, centroid, i_maxAcceleration, i_timeToTarget);
  SteeringOutput arriveSteering = PositionMatchingArrive(
      i_characterRigidbody, centroid, i_maxAcceleration, i_maxSpeed,
      i_slowRadius, i_slowRadius, i_timeToTarget);

  SteeringOutput wanderSteering =
      DynamicWander(i_characterRigidbody, 140, 210, ofVec2f(300, 300));

  blendedOutput.linearAcceleration += wanderSteering.linearAcceleration * 1.0f;
  // blending different outputs together
  blendedOutput.linearAcceleration +=
      seperationSteering.linearAcceleration * 2.0f;
  blendedOutput.linearAcceleration +=
      velocityMatchSteering.linearAcceleration * 0.5f;
  blendedOutput.linearAcceleration += arriveSteering.linearAcceleration * 0.6f;

  return blendedOutput;
}

AI::SteeringOutput AI::MovementAlgorithms::FollowPath(
    Rigidbody* character_rigidbody,
    std::vector<int> path,
    int columns,
    float tile_size, 
    float smoothing_radius, 
    float max_acceleration,
    float max_speed,
    float slow_radius,
    float target_radius,
    float time_to_target) {
  Rigidbody target;
  // calculate center of square to move to
  int index_row = (path[character_rigidbody->path_index]) / columns;
  int index_column = (path[character_rigidbody->path_index]) % columns;

  target.position.x = index_column * tile_size + tile_size / 2;
  target.position.y = index_row * tile_size + tile_size / 2;
  
  ofVec2f direction = character_rigidbody->position - target.position;
  float distance = direction.length();
  
  // check if position is path location plus range
  if (distance < smoothing_radius && 
      character_rigidbody->path_index < path.size()-1) {
    character_rigidbody->path_index++;
    index_row = (path[character_rigidbody->path_index]) / columns;
    index_column = (path[character_rigidbody->path_index]) % columns;

    target.position.x = index_column * tile_size + tile_size / 2;
    target.position.y = index_row * tile_size + tile_size / 2;    
  }

  if (character_rigidbody->path_index >= path.size()-1) {
    //return Seek(*character_rigidbody, target, max_acceleration);
    return PositionMatchingArrive(*character_rigidbody, 
                                  target, 
                                  max_acceleration,
                                  max_speed, 
                                  slow_radius, 
                                  target_radius, 
                                  time_to_target);
  } else {
    return PositionMatchingArrive(*character_rigidbody, 
                                  target, 
                                  max_acceleration,
                                  max_speed, 
                                  smoothing_radius, 
                                  target_radius, 
                                  time_to_target);
  }
}
