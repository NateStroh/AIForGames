// copyright 2022 Nate Strohmyer

#include "Boid.h"

#include "math\ofMath.h"
#include "ofTimer.h"

AI::Boid::Boid() {}

AI::Boid::~Boid() {}

void AI::Boid::Update(float i_dt) {
  int64_t currTime = ofGetElapsedTimeMillis();

  rigidbody.position += (rigidbody.velocity * i_dt);
  rigidbody.velocity += (steeringOutput.linearAcceleration * i_dt);
  rigidbody.velocity = rigidbody.velocity - .007 * rigidbody.velocity;

  rigidbody.orientation += (rigidbody.rotation * i_dt);
  rigidbody.rotation += (steeringOutput.rotationAcceleration * i_dt);
  rigidbody.rotation = rigidbody.rotation - .01 * rigidbody.rotation;

  if (currTime % 500 <= 20) {
    crumbs[crumbCount] = Crumb(rigidbody.position);
    crumbCount++;
    if (crumbCount >= NUM_CRUMBS) crumbCount = 0;
  }

  if (rigidbody.position.x > ofGetViewportWidth() + 30) {
    rigidbody.position.x = -30;
  } else if (rigidbody.position.x < -30) {
    rigidbody.position.x = ofGetViewportWidth() + 30;
  }

  if (rigidbody.position.y > ofGetViewportHeight() + 30) {
    rigidbody.position.y = -30;
  } else if (rigidbody.position.y < -30) {
    rigidbody.position.y = ofGetViewportHeight() + 30;
  }
}

void AI::Boid::Draw() {
  // uses the draw presented in class
  ofPushMatrix();

  ofTranslate(rigidbody.position.x, rigidbody.position.y);
  ofRotateRad(rigidbody.orientation);
  ofSetColor(color);

  ofDrawCircle(0, 0, radius);
  ofDrawTriangle(0, -(radius), 0, radius, radius * 2, 0);

  ofPopMatrix();

  // drawing the crumbs related to this object
  for (int i = 0; i < NUM_CRUMBS; i++) {
    crumbs[i].Draw();
  }
}
