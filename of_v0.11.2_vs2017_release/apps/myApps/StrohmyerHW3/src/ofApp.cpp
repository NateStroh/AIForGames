// copyright 2022 Nate Strohmyer

#include "ofApp.h"

#include <inttypes.h>
#include "MovementAlgorithms\MovementAlgorithms.h"
#include "Pathfinding\PathfindingAlgorithms.h"
#include "math\ofMath.h"

#include "DecisionMaking\DecisionTree\DecisionTree.h"
#include "DecisionMaking\DecisionTree\DecisionTreeAction.h"
#include "../TestAction.h"
#include "../TestDTConditionNode.h"

#include "DecisionMaking\BehaviorTree\BehaviorTree.h"
#include "DecisionMaking\BehaviorTree\Limit.h"
#include "DecisionMaking\BehaviorTree\NonDeterministicSequence.h"
#include "DecisionMaking\BehaviorTree\Selector.h"
#include "DecisionMaking\BehaviorTree\Sequencer.h"
#include "../TestBTNode.h"

#include "DecisionMaking\GOAP\GOAP.h"
#include "DecisionMaking\GOAP\Task.h"

#include "DecisionMaking\BehaviorTree\AttackActionLeft.h"
#include "DecisionMaking\BehaviorTree\AttackActionRight.h"
#include "DecisionMaking\BehaviorTree\BehaviorTree.h"
#include "DecisionMaking\BehaviorTree\HaveEnemyFlagCondition.h"
#include "DecisionMaking\BehaviorTree\IsMyFlagSafeCondition.h"
#include "DecisionMaking\BehaviorTree\Limit.h"
#include "DecisionMaking\BehaviorTree\MoveToEnemyAction.h"
#include "DecisionMaking\BehaviorTree\MoveToEnemyFlagAction.h"
#include "DecisionMaking\BehaviorTree\MoveToMyFlagAction.h"
#include "DecisionMaking\BehaviorTree\NonDeterministicSequence.h"
#include "DecisionMaking\BehaviorTree\Selector.h"
#include "DecisionMaking\BehaviorTree\Sequencer.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);

  AI::DecisionMaking::Action test_action;
  test_action.priority_ = 5;
  test_action.expiry_time_ = ofGetCurrentTime().getAsMilliseconds() + 10000;
  AI::DecisionMaking::Action test_action1;
  test_action1.priority_ = 5;
  test_action1.expiry_time_ = ofGetCurrentTime().getAsMilliseconds() + 10000;
  AI::DecisionMaking::Action test_action2;
  test_action2.priority_ = 9;
  test_action2.expiry_time_ = ofGetCurrentTime().getAsMilliseconds() + 10000;
  AI::DecisionMaking::Action test_action3;
  test_action3.priority_ = 1;
  test_action3.expiry_time_ = ofGetCurrentTime().getAsMilliseconds() + 10000;
  AI::DecisionMaking::Action test_action4;
  test_action4.priority_ = 3;
  test_action4.expiry_time_ = ofGetCurrentTime().getAsMilliseconds() + 10000;
  
  action_manager.ScheduleAction(&test_action);
  action_manager.ScheduleAction(&test_action1);
  action_manager.ScheduleAction(&test_action2);
  action_manager.ScheduleAction(&test_action3);
  action_manager.ScheduleAction(&test_action4);

  action_manager.Execute();
  action_manager.Execute();
  action_manager.Execute();
  action_manager.Execute();
  action_manager.Execute();

  TestAction test0 = *new TestAction("action 0!");
  TestAction test1 = *new TestAction("action 1!");
  TestAction test2 = *new TestAction("action 2!");
  TestAction test3 = *new TestAction("action 3!");
  TestAction test4 = *new TestAction("action 4!");

  TestDTConditionNode condition0;
  TestDTConditionNode condition1;
  TestDTConditionNode condition2;
  TestDTConditionNode condition3;

  AI::DecisionMaking::DecisionTreeAction action0(&test0);
  AI::DecisionMaking::DecisionTreeAction action1(&test1);
  AI::DecisionMaking::DecisionTreeAction action2(&test2);
  AI::DecisionMaking::DecisionTreeAction action3(&test3);
  AI::DecisionMaking::DecisionTreeAction action4(&test4);

  condition0.false_node_ = &condition1;
  condition0.true_node_ = &condition2;
  
  condition1.false_node_ = &condition3;
  condition1.true_node_ = &action0;
  
  condition2.false_node_ = &action1;
  condition2.true_node_ = &action2;
  
  condition3.false_node_ = &action3;
  condition3.true_node_ = &action4;

  DT.action_manager_ = &action_manager;
  DT.root_node_ = &condition0;

  DT.MakeDecision();

  action_manager.Execute();

  TestAction goapm1to2("Moving 1 to 2");
  TestAction goapm1to3("Moving 1 to 3");
  TestAction goapm2to1("Moving 2 to 1");
  TestAction goapm2to4("Moving 2 to 4");
  TestAction goapm3to1("Moving 3 to 1");
  TestAction goapm3to4("Moving 3 to 4");
  TestAction goapm4to3("Moving 4 to 3");
  TestAction goapm4to2("Moving 4 to 2");
  TestAction take_flag("Taking flag");
  TestAction deliv_flag("Delivering flag!");

  std::vector<bool> start_state({ 0, 1, 0, 0, 0, 0, 0, 0, 1 });
  std::vector<bool> goal_state({ 0, 1, 0, 0, 0, 1, 0, 0, 0 });

  AI::DecisionMaking::Task m1to2;
  m1to2.pre_ = std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0, 0 });
  m1to2.add_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m1to2.del_ = std::vector<bool>({0, 1, 0, 0, 0, 0, 0, 0, 0});
  m1to2.action_to_schedule = &goapm1to2;

  AI::DecisionMaking::Task m1to3;
  m1to3.pre_ = std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0, 0 });
  m1to3.add_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m1to3.del_ = std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0, 0 });
  m1to3.action_to_schedule = &goapm1to3;

  AI::DecisionMaking::Task m2to1;
  m2to1.pre_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m2to1.add_ = std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0, 0 });
  m2to1.del_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m2to1.action_to_schedule = &goapm2to1;

  AI::DecisionMaking::Task m2to4;
  m2to4.pre_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m2to4.add_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m2to4.del_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m2to4.action_to_schedule = &goapm2to4;

  AI::DecisionMaking::Task m3to1;
  m3to1.pre_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m3to1.add_ = std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0, 0 });
  m3to1.del_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m3to1.action_to_schedule = &goapm3to1;

  AI::DecisionMaking::Task m3to4;
  m3to4.pre_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m3to4.add_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m3to4.del_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m3to4.action_to_schedule = &goapm3to4;

  AI::DecisionMaking::Task m4to3;
  m4to3.pre_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m4to3.add_ = std::vector<bool>({ 0, 0, 0, 1, 0, 0, 0, 0, 0 });
  m4to3.del_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m4to3.action_to_schedule = &goapm4to3;

  AI::DecisionMaking::Task m4to2;
  m4to2.pre_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m4to2.add_ = std::vector<bool>({ 0, 0, 1, 0, 0, 0, 0, 0, 0 });
  m4to2.del_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 0 });
  m4to2.action_to_schedule = &goapm4to2;

  AI::DecisionMaking::Task takeFlag;
  takeFlag.pre_ = std::vector<bool>({ 0, 0, 0, 0, 1, 0, 0, 0, 1 });
  takeFlag.add_ = std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0 });
  takeFlag.del_ = std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 0, 1 });
  takeFlag.action_to_schedule = &take_flag;

  AI::DecisionMaking::Task deliverFlag;
  deliverFlag.pre_ = std::vector<bool>({ 1, 1, 0, 0, 0, 0, 0, 0, 0 });
  deliverFlag.add_ = std::vector<bool>({ 0, 0, 0, 0, 0, 1, 0, 0, 0 });
  deliverFlag.del_ = std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0 });
  deliverFlag.action_to_schedule = &deliv_flag;
  
  std::vector<AI::DecisionMaking::Task> tasks =
      std::vector<AI::DecisionMaking::Task>(
          {m1to2, m1to3, m2to1, m2to4, m3to1, m3to4, m4to3, m4to2,
           takeFlag, deliverFlag});

  auto taskList = goap.GetBestAction(start_state, goal_state, tasks);

  BT.action_manager_ = &action_manager;
  
  bool b_isFlagSafe = true;
  bool b_haveEnemyFlag = false;

  TestAction moveToEnemy = *new TestAction("Moving to the enemy");
  TestAction leftAttack  = *new TestAction("hit em with the left");
  TestAction rightAttack  = *new TestAction("mean right hook");
  TestAction moveToEnemyFlag = *new TestAction("Moving to enemy flag");
  TestAction moveToMyFlag = *new TestAction("Moving to my flag");

  // composite nodes
  AI::DecisionMaking::Sequencer root_selector;
  AI::DecisionMaking::Selector selector1;
  AI::DecisionMaking::Selector selector2;
  AI::DecisionMaking::Sequencer sequence1;
  AI::DecisionMaking::Selector sequence2;
  AI::DecisionMaking::Limit limit;
  AI::DecisionMaking::NonDetermenisticSequence randomSequence;

  // condition nodes
  AI::DecisionMaking::IsMyFlagSafeCondition isMyFlagSafe;
  isMyFlagSafe.flag_taken_ = &b_isFlagSafe;
  AI::DecisionMaking::HaveEnemyFlagCondition haveEnemyFlag;
  haveEnemyFlag.flag_taken_ = &b_haveEnemyFlag;

  // actions
  AI::DecisionMaking::MoveToEnemyAction moveToEnemyActionNode;
  moveToEnemyActionNode.move_action_ = &moveToEnemy;
  AI::DecisionMaking::AttackActionLeft attackLeftActionNode;
  attackLeftActionNode.attack_action_ = &leftAttack;
  AI::DecisionMaking::AttackActionRight attackRightActionNode;
  attackRightActionNode.attack_action_ = &rightAttack;
  AI::DecisionMaking::MoveToEnemyFlagAction moveToEnemyFlagActionNode;
  moveToEnemyFlagActionNode.move_action_ = &moveToEnemyFlag;
  AI::DecisionMaking::MoveToMyFlagAction moveToMyFlagActionNode;
  moveToMyFlagActionNode.move_action_ = &moveToMyFlag;

  // setting up connections
  root_selector.children_.push_back(&selector1);
  root_selector.children_.push_back(&selector2);
  selector1.children_.push_back(&isMyFlagSafe);
  selector1.children_.push_back(&sequence1);
  sequence1.children_.push_back(&moveToEnemyActionNode);
  sequence1.children_.push_back(&limit);
  limit.child_ = &randomSequence;
  limit.run_limit_ = 4;
  randomSequence.children_.push_back(&attackLeftActionNode);
  randomSequence.children_.push_back(&attackRightActionNode);
  selector2.children_.push_back(&haveEnemyFlag);
  selector2.children_.push_back(&sequence2);
  sequence2.children_.push_back(&moveToEnemyFlagActionNode);
  sequence2.children_.push_back(&moveToMyFlagActionNode);

  BT.root_node_ = &root_selector;
  AI::DecisionMaking::Action* asdf = BT.GetAction();

  cg_graph = ReadInGraph("Grid15by20BlockedTiles.txt");

  action_manager.Execute();
  action_manager.Execute();
  action_manager.Execute();

  leadBoid.rigidbody.position = {100, 100.0f};
  leadBoid.rigidbody.orientation = ofDegToRad(0);
  leadBoid.color = ofColor::greenYellow;
  leadBoid.rigidbody.mass = 20;

  monsterBoid.rigidbody.position = {300, 300.0f};
  monsterBoid.rigidbody.orientation = ofDegToRad(0);
  monsterBoid.color = ofColor::red;
  monsterBoid.rigidbody.mass = 20;
}

//--------------------------------------------------------------
void ofApp::update() {
  float deltaTime = ofGetLastFrameTime();

  action_manager.Execute();
  // MTA.Execute();
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
  monsterBoid.Update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw() {
  leadBoid.Draw();
  monsterBoid.Draw();
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

void ofApp::PrintVector(vector<int> path) {
  for (int i : path) {
    printf("%d, ", i);
  }
  printf("\n");
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
