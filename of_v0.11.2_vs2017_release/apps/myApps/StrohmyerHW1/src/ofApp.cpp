// copyright 2022 Nate Strohmyer

#include "ofApp.h"

#include "MovementAlgorithms\MovementAlgorithms.h"
#include "math\ofMath.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);
  AI::Boid b;
  b.rigidbody.position = {100, 100};
  flock.push_back(b);
  AI::Boid b1;
  b1.rigidbody.position = {0, 0};
  flock.push_back(b1);
  AI::Boid b2;
  b2.rigidbody.position = {130, 130};
  flock.push_back(b2);
  AI::Boid b3;
  b3.rigidbody.position = {30, 30};
  flock.push_back(b3);
  AI::Boid b4;
  b4.rigidbody.position = {20, 70};
  flock.push_back(b4);
  AI::Boid b5;
  b5.rigidbody.position = {39, 51};
  flock.push_back(b5);
  AI::Boid b6;
  b6.rigidbody.position = {200, 100};
  flock.push_back(b6);
  AI::Boid b7;
  b7.rigidbody.position = {100, 300};
  flock.push_back(b7);
  AI::Boid b8;
  b8.rigidbody.position = {50, 150};
  flock.push_back(b8);
  AI::Boid b9;
  b9.rigidbody.position = {10, 40};
  flock.push_back(b9);
  AI::Boid b10;
  b10.rigidbody.position = {20, 100};
  flock.push_back(b10);
  AI::Boid b11;
  b11.rigidbody.position = {200, 20};
  flock.push_back(b11);
  AI::Boid b12;
  b12.rigidbody.position = {300, 50};
  flock.push_back(b12);
  AI::Boid b13;
  b13.rigidbody.position = {200, 150};
  flock.push_back(b13);
  AI::Boid b14;
  b14.rigidbody.position = {350, 120};
  flock.push_back(b14);
  AI::Boid b15;
  b15.rigidbody.position = {20, 190};
  flock.push_back(b15);
  AI::Boid b16;
  b16.rigidbody.position = {70, 130};
  flock.push_back(b16);
  AI::Boid b17;
  b17.rigidbody.position = {40, 300};
  flock.push_back(b17);
  AI::Boid b18;
  b18.rigidbody.position = {30, 240};
  flock.push_back(b18);

  leadBoid.rigidbody.position = {100,
                                 ofGetCurrentViewport().getBottom() - 100.0f};
  leadBoid.rigidbody.orientation = ofDegToRad(0);
  leadBoid.color = ofColor::greenYellow;
  leadBoid.rigidbody.mass = 20;
}

//--------------------------------------------------------------
void ofApp::update() {
  float deltaTime = ofGetLastFrameTime();

  switch (mode) {
    default:
      break;
    // kinematic seek 4 corners
    case 0:
      leadBoid.rigidbody.velocity = GoToCorner(corner, leadBoid);
      leadBoid.rigidbody.orientation =
          AI::MovementAlgorithms::KinematicAlign(leadBoid.rigidbody.velocity)
              .rotationAcceleration;
      break;
    // seek steering behaviors
    case 1:
      // changing movement algorithm
      // dynamic seek
      if (modeChanges == 1)
        leadBoid.steeringOutput.linearAcceleration =
            AI::MovementAlgorithms::Seek(leadBoid.rigidbody,
                                         AI::Rigidbody(clickLocation, 0), 120)
                .linearAcceleration;
      // position matching arrive
      else if (modeChanges == 2)
        leadBoid.steeringOutput.linearAcceleration =
            AI::MovementAlgorithms::PositionMatchingArrive(
                leadBoid.rigidbody, AI::Rigidbody(clickLocation, 0), 30.0f,
                60.0f, 200.0f, 10.0f, .5f)
                .linearAcceleration;
      // pursue
      else
        leadBoid.steeringOutput.linearAcceleration =
            AI::MovementAlgorithms::DynamicPursue(
                leadBoid.rigidbody, AI::Rigidbody(clickLocation, 0), 30, .1f)
                .linearAcceleration;

      leadBoid.steeringOutput.rotationAcceleration =
          AI::MovementAlgorithms::LookWhereYouAreGoing(leadBoid.rigidbody,
                                                       10.0f, 20.0f, 5, 30, 10)
              .rotationAcceleration;
      break;
    // wander steering behaviors
    case 2:
      leadBoid.steeringOutput.linearAcceleration =
          AI::MovementAlgorithms::DynamicWander(leadBoid.rigidbody, 140, 210,
                                                ofVec2f(300, 300))
              .linearAcceleration;

      // look where you are going
      if (modeChanges == 1) {
        leadBoid.steeringOutput.rotationAcceleration =
            AI::MovementAlgorithms::LookWhereYouAreGoing(
                leadBoid.rigidbody, 10.0f, 20.0f, 5, 30, 10)
                .rotationAcceleration;
      // calling special wander with face called on the target it's seeking
      } else if (modeChanges == 2) {
            AI::SteeringOutput steeringOutput =
            AI::MovementAlgorithms::DynamicWanderFaceTarget(
                leadBoid.rigidbody, 140, 210, ofVec2f(300, 300), 30.0f, 60.0f,
                6, 60, 10);
        leadBoid.steeringOutput = steeringOutput;
      // kinematic align
      } else {
        leadBoid.rigidbody.orientation =
            AI::MovementAlgorithms::KinematicAlign(leadBoid.rigidbody.velocity)
                .rotationAcceleration;
      }
      break;
    // flocking behaviors
    case 3:

      leadBoid.steeringOutput.linearAcceleration =
          AI::MovementAlgorithms::DynamicWander(leadBoid.rigidbody, 140, 210,
                                                ofVec2f(300, 300))
              .linearAcceleration;
      leadBoid.steeringOutput.rotationAcceleration =
          AI::MovementAlgorithms::LookWhereYouAreGoing(leadBoid.rigidbody,
                                                       10.0f, 20.0f, 5, 30, 10)
              .rotationAcceleration;

      if (modeChanges == 2) {
        // looping over all boids except the last one, our lead boid
        for (unsigned int i = 0; i < flock.size() - 1; i++) {
          flock[i].steeringOutput.linearAcceleration =
              AI::MovementAlgorithms::Flock(flock[i].rigidbody,
                                            GetRigidbodies(flock), 100, 200, 50,
                                            10, 0.5f, 150, 10000)
                  .linearAcceleration;
          flock[i].steeringOutput.rotationAcceleration =
              AI::MovementAlgorithms::LookWhereYouAreGoing(
                  flock[i].rigidbody, 10.0f, 20.0f, 5, 30, 10)
                  .rotationAcceleration;
        }
      } else {
        // calling flock - adding testBoid as the leader
        flock.push_back(leadBoid);
        // looping over all boids except the last one, our lead boid
        for (unsigned int i = 0; i < flock.size() - 1; i++) {
          flock[i].steeringOutput.linearAcceleration =
              AI::MovementAlgorithms::Flock(flock[i].rigidbody,
                                            GetRigidbodies(flock), 100, 200, 50,
                                            10, 0.5f, 150, 10000)
                  .linearAcceleration;
          flock[i].steeringOutput.rotationAcceleration =
              AI::MovementAlgorithms::LookWhereYouAreGoing(
                  flock[i].rigidbody, 10.0f, 20.0f, 5, 30, 10)
                  .rotationAcceleration;
        }
        flock.pop_back();
      }
      // updating all flock boids
      for (unsigned int i = 0; i < flock.size(); i++) {
        flock[i].Update(deltaTime);
      }

      break;
  }

  leadBoid.Update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw() {
  switch (mode) {
    default:
      break;
    // kinematic motion
    case 0:
      leadBoid.Draw();
      // drawing goal locations
      ofSetColor(ofColor::orangeRed);
      ofDrawCircle({100, 100}, 10);
      ofDrawCircle({ofGetCurrentViewport().getRight() - 100.0f, 100}, 10);
      ofDrawCircle({ofGetCurrentViewport().getRight() - 100.0f,
                    ofGetCurrentViewport().getBottom() - 100.0f},
                   10);
      ofDrawCircle({100, ofGetCurrentViewport().getBottom() - 100.0f}, 10);

      break;
    // seek steering behaviors
    case 1:
      leadBoid.Draw();
      // drawing where user clicked
      ofSetColor(ofColor::orangeRed);
      ofDrawCircle(clickLocation, 20);
      break;
    // wander steering behavior
    case 2:
      leadBoid.Draw();

      break;
    // flocking behaviors
    case 3:
      leadBoid.Draw();
      for (unsigned int i = 0; i < flock.size(); i++) {
        flock[i].Draw();
      }
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  // changing what algorithms are running
  // kinematic motion
  if (key == 'a') {
    mode = 0;
    modeChanges = 1;
    corner = 0;
    leadBoid.rigidbody.position = {100,
                                   ofGetCurrentViewport().getBottom() - 100.0f};
  // seek steering behaviors
  } else if (key == 's') {
    mode = 1;
    modeChanges = 1;
    clickLocation = {400, 400};
  // wander steering behavior
  } else if (key == 'd') {
    mode = 2;
    modeChanges = 1;
  // flocking behaviors
  } else if (key == 'f') {
    mode = 3;
    modeChanges = 1;
  // changing specifics in algorithm
  } else if (key == '1') {
    modeChanges = 1;
  } else if (key == '2') {
    modeChanges = 2;
  } else if (key == '3') {
    modeChanges = 3;
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
  if (mode == 1) {
    clickLocation = ofVec2f(x, y);
  }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

std::vector<AI::Rigidbody> ofApp::GetRigidbodies(
    std::vector<AI::Boid> i_boids) {
  std::vector<AI::Rigidbody> rigidbodies;

  for (AI::Boid boid : i_boids) {
    rigidbodies.push_back(boid.rigidbody);
  }

  return rigidbodies;
}

ofVec2f ofApp::GoToCorner(int i_corner, AI::Boid i_boidToMove) {
  ofVec2f positionToSeekTo;

  switch (corner) {
    default:
      corner = 0;
      break;
    case 0:
      positionToSeekTo = {100, 100};
      if (i_boidToMove.rigidbody.position.y < positionToSeekTo.y) corner = 1;
      break;
    case 1:
      positionToSeekTo = {ofGetCurrentViewport().getRight() - 100.0f, 100};
      if (i_boidToMove.rigidbody.position.x > positionToSeekTo.x) corner = 2;
      break;
    case 2:
      positionToSeekTo = {ofGetCurrentViewport().getRight() - 100.0f,
                          ofGetCurrentViewport().getBottom() - 100.0f};
      if (i_boidToMove.rigidbody.position.y > positionToSeekTo.y) corner = 3;
      break;
    case 3:
      positionToSeekTo = {100, ofGetCurrentViewport().getBottom() - 100.0f};
      break;
  }

  return AI::MovementAlgorithms::Seek(i_boidToMove.rigidbody,
                                      AI::Rigidbody(positionToSeekTo, 0), 120)
      .linearAcceleration;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
