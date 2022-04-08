// copyright 2022 Nate Strohmyer

#include "Crumb.h"

AI::Crumb::Crumb() : startTime(ofGetCurrentTime()), position(0, 0) {}

AI::Crumb::Crumb(glm::vec2 i_startingPosition)
    : startTime(ofGetCurrentTime()), position(i_startingPosition) {}

AI::Crumb::~Crumb() {}

void AI::Crumb::Update(double i_dt) {}

void AI::Crumb::Draw() { ofDrawCircle(position, 2); }
