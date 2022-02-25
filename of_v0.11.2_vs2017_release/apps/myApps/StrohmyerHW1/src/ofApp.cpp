// copyright 2022 Nate Strohmyer

#include "ofApp.h"

#include "MovementAlgorithms\MovementAlgorithms.h"
#include "Pathfinding\PathfindingAlgorithms.h"
#include "math\ofMath.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);

  int graph[9][9] = {
      {0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
      {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
      {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
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

  int grid_test[25][25] = {{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 4, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 3, 0, 3, 0, 0, 0, 1, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
                            0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                            0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 5, 0, 1,
                            0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
                            1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1,
                            0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
                            1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
                            0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                            0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                            0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 1},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0}};

  // AI::PathfindingAlgorithms::ConnectionGraph cg(9, 8);
  // for (int i = 0; i < 9; i++) {
  //   for (int j = 0; j < 9; j++) {
  //     cg.data[i][j] = graph[i][j];
  //   }
  // }

  AI::PathfindingAlgorithms::ConnectionGraph cg(5, 5);
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      cg.data[i][j] = grid_test[i][j];
    }
  }

  AI::PathfindingAlgorithms::ConnectionGraph cg1 =
      ReadInGraph("Grid10000NodesRandom.txt");

  cg_graph = ReadInGraph("Grid15by20BlockedTiles.txt");

  std::vector<int> vec =
      AI::PathfindingAlgorithms::DijkstraSearch(&cg1, cg1.num_nodes, 0, 5004);

  vec = AI::PathfindingAlgorithms::AStarSearchMDH(&cg1, cg1.num_nodes, 0, 5004);

  leadBoid.rigidbody.position = {100, 100.0f};
  leadBoid.rigidbody.orientation = ofDegToRad(0);
  leadBoid.color = ofColor::greenYellow;
  leadBoid.rigidbody.mass = 20;
}

//--------------------------------------------------------------
void ofApp::update() {
  float deltaTime = ofGetLastFrameTime();

  if (!current_path.empty()) {
    leadBoid.steeringOutput.linearAcceleration =
        AI::MovementAlgorithms::FollowPath(
            &leadBoid.rigidbody,  // character rigidbody
            current_path,         // path to follow - vector<int>
            columns,              // number of columns
            tile_size,            // tile size
            55.0f,                // smoothing radius
            20.0f,                // max acceleration
            80.0f,                // max speed
            200.0f,               // slow radius
            5.0f,                 // target radius
            0.01f)
            .linearAcceleration;
    leadBoid.steeringOutput.rotationAcceleration =
        AI::MovementAlgorithms::LookWhereYouAreGoing(leadBoid.rigidbody, 10.0f,
                                                     20.0f, 10.0f, 100.0f, 5.0f)
            .rotationAcceleration;
    // leadBoid.rigidbody, 10.0f, 20.0f, 5, 30, 10)
    // leadBoid.rigidbody.orientation =
    //     AI::MovementAlgorithms::KinematicAlign(
    //         leadBoid.rigidbody.velocity).rotationAcceleration;
  } else {
    leadBoid.rigidbody.velocity = {0, 0};
    leadBoid.rigidbody.rotation = 0.0f;
  }

  leadBoid.Update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw() {
  leadBoid.Draw();
  // drawing grid
  if (draw_grid) {
    ofSetColor(ofColor::forestGreen);
    for (int i = 0; i <= rows; i++) {
      ofDrawRectangle({0, tile_size * i},
                      (tile_size * columns) + grid_thickness, grid_thickness);
    }
    for (int i = 0; i <= columns; i++) {
      ofDrawRectangle({tile_size * i, 0}, grid_thickness, tile_size * rows);
    }
  }

  // drawing tiles
  if (draw_blocked_tiles) {
    ofSetColor(ofColor::black);
    for (int index : tilesblocked) {
      ofVec2f draw_position;
      int index_row = index / columns;
      int index_column = index % columns;
      draw_position.x = index_column * tile_size + grid_thickness;
      draw_position.y = index_row * tile_size + grid_thickness;

      ofDrawRectangle(draw_position, tile_size, tile_size);
    }
  }
  if (draw_walls) {
    ofSetColor(ofColor::crimson);
    ofDrawRectangle({118, 272}, 80, 80);

    ofDrawRectangle({377, 172}, 20, 125);
    ofDrawRectangle({580, 172}, 20, 125);
    ofDrawRectangle({395, 277}, 202, 20);

    ofDrawRectangle({630, 20}, 170, 20);
    ofDrawRectangle({785, 20}, 20, 170);
    ofDrawRectangle({800, 120}, 100, 20);
    ofDrawRectangle({887, 68}, 20, 72);

    ofDrawRectangle({130, 425}, 60, 175);
    ofDrawRectangle({190, 530}, 150, 70);

    ofDrawRectangle({15, 682}, 370, 20);

    ofDrawRectangle({480, 480}, 20, 300);

    ofDrawRectangle({795, 485}, 160, 210);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  // changing what algorithms are running
  // toggle grid drawing
  if (key == 'a') {
    draw_grid = !draw_grid;
    corner = 0;
    // toggle wall drawing
  } else if (key == 's') {
    draw_walls = !draw_walls;
  } else if (key == 'd') {
    draw_blocked_tiles = !draw_blocked_tiles;
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
  clickLocation = ofVec2f(x, y);
  int click_row = (clickLocation.y / tile_size);
  int click_col = (clickLocation.x / tile_size);
  int click_to_index = ((click_row * columns) + click_col);

  if (std::find(tilesblocked.begin(), tilesblocked.end(), click_to_index) ==
      tilesblocked.end()) {
    int char_row = (leadBoid.rigidbody.position.y / tile_size);
    int char_col = (leadBoid.rigidbody.position.x / tile_size);
    int character_pos_to_index = (char_row * columns) + char_col;

    leadBoid.rigidbody.path_index = 0;

    current_path = AI::PathfindingAlgorithms::AStarSearchMDH(
        &cg_graph, cg_graph.num_nodes, character_pos_to_index, click_to_index);
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
      int from_index = std::stoi(words[1]) - 1;
      int to_index = std::stoi(words[2]) - 1;
      int cost = std::stoi(words[3]);

      return_graph.data[from_index][to_index] = cost;
    }
  }

  return return_graph;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
