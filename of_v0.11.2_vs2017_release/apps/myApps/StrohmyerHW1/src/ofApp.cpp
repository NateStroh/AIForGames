// copyright 2022 Nate Strohmyer

#include "ofApp.h"

#include "MovementAlgorithms\MovementAlgorithms.h"
#include "Pathfinding\PathfindingAlgorithms.h"
#include "math\ofMath.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);

  int graph[9][9] = {
      {0, 4, 0, 0, 0, 0, 0, 8, 0},
      {4, 0, 8, 0, 0, 0, 0, 11, 0},
      {0, 8, 0, 7, 0, 4, 0, 0, 2},
      {0, 0, 7, 0, 9, 14, 0, 0, 0},
      {0, 0, 0, 9, 0, 10, 0, 0, 0},
      {0, 0, 4, 14, 10, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 1, 6},
      {8, 11, 0, 0, 0, 0, 1, 0, 7},
      {0, 0, 2, 0, 0, 0, 6, 7, 0}};

//  int grid_test[25][25] = {
//      {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
//      {0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
//      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
//      {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
//      {0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
//      {0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0},
//      {0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0},
//      {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
//      {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
//      {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
//      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0}
//  };

  int grid_test[25][25] = {
      {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,5,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,4,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,1,0,0,0,3,0,3,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,2,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,1,0,0,0,5,0,1,0,0,0,2,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,2,0,0,0,1,0,1,0,0,0,3,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,3,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,2,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,1,0,1},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,0}
  };

  //AI::PathfindingAlgorithms::ConnectionGraph cg(9, 8);
  //for (int i = 0; i < 9; i++) {
  //  for (int j = 0; j < 9; j++) {
  //    cg.data[i][j] = graph[i][j];
  //  }
  //}

  AI::PathfindingAlgorithms::ConnectionGraph cg(5,5);
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      cg.data[i][j] = grid_test[i][j];
    }
  }

  AI::PathfindingAlgorithms::ConnectionGraph cg1 = ReadInGraph("Grid10000NodesRandom.txt");

  cg_graph = ReadInGraph("Grid15by20BlockedTiles.txt");

  std::vector<int> vec =
      AI::PathfindingAlgorithms::DijkstraSearch(&cg1, cg1.num_nodes, 0, 5004);

  vec = AI::PathfindingAlgorithms::AStarSearch(&cg1, cg1.num_nodes, 0, 5004);

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

  leadBoid.rigidbody.position = {100, 100.0f};
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
      if (!current_path.empty()) {
      leadBoid.steeringOutput.linearAcceleration = 
          AI::MovementAlgorithms::FollowPath(
            &leadBoid.rigidbody, // character rigidbody
            current_path, // path to follow - vector<int>
            columns, // number of columns
            tile_size, // tile size
            55.0f, // smoothing radius
            50.0f, // max acceleration
            100.0f, // max speed
            200.0f, // slow radius 
            40.0f, // target radius
            0.1f).linearAcceleration;
      //leadBoid.rigidbody.velocity = GoToCorner(corner, leadBoid);
      leadBoid.rigidbody.orientation =
          AI::MovementAlgorithms::KinematicAlign(leadBoid.rigidbody.velocity)
              .rotationAcceleration;
      }
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
      
      for (int i = 0; i <= rows; i++) {
        ofDrawRectangle({0, tile_size * i},
                        (tile_size * columns) + grid_thickness, grid_thickness);
      }
      for (int i = 0; i <= columns; i++) {
        ofDrawRectangle({tile_size*i, 0}, grid_thickness, tile_size * rows);
      }

      for (int index : tilesblocked) {
        ofVec2f draw_position;
        int index_row = index / columns;
        int index_column = index % columns;
        draw_position.x = index_column * tile_size + grid_thickness * 3;
        draw_position.y = index_row * tile_size + grid_thickness * 3;
        
        ofDrawRectangle(draw_position, tile_size - 25,
                        tile_size - 25);
      }

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
  // if (mode == 1) {
  //   clickLocation = ofVec2f(x, y);
  // }
  clickLocation = ofVec2f(x, y);
  int char_row = (leadBoid.rigidbody.position.y / tile_size);
  int char_col = (leadBoid.rigidbody.position.x / tile_size);
  int character_pos_to_index = (char_row * columns) + char_col;

  int click_row = (clickLocation.y / tile_size);
  int click_col = (clickLocation.x / tile_size);
  int click_to_index = ((click_row * columns) + click_col);

  leadBoid.rigidbody.path_index = 0;
  current_path = AI::PathfindingAlgorithms::AStarSearch(&cg_graph,
                                                        cg_graph.num_nodes,
                                                        character_pos_to_index,
                                                        click_to_index);
  //current_path = AI::PathfindingAlgorithms::DijkstraSearch(&cg_graph, cg_graph.num_nodes, character_pos_to_index, click_to_index);
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

AI::PathfindingAlgorithms::ConnectionGraph ofApp::ReadInGraph(
    std::string file_path) {
  ofFile file;
  file.open(ofToDataPath(file_path), ofFile::ReadOnly, false);

  unsigned int nodes = 0;
  unsigned int row_num = 0;
  unsigned int col_num = 0;
  auto lines = ofSplitString(ofBufferFromFile(file_path).getText(), "\n");
  for (string line : lines) {
    if (line[0] == 'p') {
      vector<string> words = ofSplitString(line, " ");
      nodes = std::stoi(words[2]);
      row_num = std::stoi(words[4]);
      col_num = std::stoi(words[5]);
      break;
    }
  }
  if (nodes == 0) {
    return AI::PathfindingAlgorithms::ConnectionGraph();
  }
  
  AI::PathfindingAlgorithms::ConnectionGraph return_graph(row_num, col_num);

  for (string line : lines) {
    if (line[0] == 'a') {
      vector<string> words = ofSplitString(line, " ");
      int from_index = std::stoi(words[1])-1;
      int to_index = std::stoi(words[2])-1;
      int cost = std::stoi(words[3]);
      
      return_graph.data[from_index][to_index] = cost;
    }
  }

  return return_graph;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
