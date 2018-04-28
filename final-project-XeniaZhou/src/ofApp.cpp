#include "ofApp.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>


using namespace maps;
//--------------------------------------------------------------
void ofApp::setup() {
	state_ = PROCESSING;
	background_ = Background();

	background_.createMap(getTotalMaps());
	player_ = Player();
	player_.setPosition(background_.getPosition().x, background_.getPosition().y);
	player_.setSize(background_.getRec().getHeight());
}


//--------------------------------------------------------------
void ofApp::update(){
	if (should_update_) {
		if (state_ == PROCESSING) {
			BackgroundSegments *segment = &background_.findIntersectPart(player_.getBody());
			if (segment->containKey()) {
				player_.addKey(segment->getKey());
				segment->removeKey();
				cout << 60 + player_.getRedKeyNum() << endl;
			}
			if (segment->containGem()) {
				player_.takeGem(segment->getGem());
				segment->removeGem();
			}
			if (segment->containMonster()) {
				player_.attackMonster(segment->getMonster());
				if (player_.isDead()) {
					state_ = END;			
				}
				else {
					segment->removeMonster();
				}
			}
			
		}	
		draw();
	}

	should_update_ = true;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawInfo();
	if (state_ == NEXTFLOOR) {
		background_.goToNextFloor();
		if (background_.isEnd()) {
			state_ = END;
		} else {
			state_ = PROCESSING;
		}
		
	}
	if (state_ == PROCESSING) {
		std::vector<vector<BackgroundSegments>> floor_map = background_.getFloorMap();
		for (int i = 0; i < floor_map[0].size(); i++) {
			floor_map[0][i].drawBackgroundSegment();
		}
		player_.drawPlayer();
	}
	if (state_ == END) {
		drawEnd();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	}

	int upper_key = toupper(key); // Standardize on upper case

	if (state_ == PROCESSING)
	{
		Direction current_direction = player_.getDirection();

		// If current direction has changed to a valid new one, force an immediate update and skip the next frame update
		if (upper_key == 'W') {
			player_.setDirection(UP);
			move();
			update();
			should_update_ = false;
		}
		else if (upper_key == 'A') {
			player_.setDirection(LEFT);
			move();
			update();
			should_update_ = false;
		}
		else if (upper_key == 'S') {
			player_.setDirection(DOWN);
			move();
			update();
			should_update_ = false;
		}
		else if (upper_key == 'D') {
			player_.setDirection(RIGHT);
			move();
			update();
			should_update_ = false;
		}
	}
	else if (upper_key == 'R' && state_ == END) {
		setup();
	}
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
vector<string> ofApp::splitter(string in_pattern, string& content) {
	vector<string> split_content;

	regex pattern(in_pattern);
	copy(sregex_token_iterator(content.begin(), content.end(), pattern, -1),
		sregex_token_iterator(), back_inserter(split_content));
	return split_content;
}

string ofApp::getImageFromFile() {
	ifstream infile;
	string total_image = "";
	string path = "../maps.txt";
	
	infile.open(path);

	if (!infile.is_open()) {
		cout << "Error in opening file..!!";
		return "";
	}

	while (infile.eof() == 0) {
		string s;
		getline(infile, s);
		total_image += s + "\n";
	}
	cout << "you have successfully read the training images" << endl;
	infile.close();
	return total_image;
}

vector<std::string> ofApp::selectEachImage(string all) {
	vector<string> each_line = splitter("\n", all);
	string each_image = "";
	vector<string> total;
	int count_for_separate = 10;

	for (int i = 0; i < each_line.size(); i++) {
		if (each_line[i] != "") {
			each_image += each_line[i];
			count_for_separate--;
		}
		if (count_for_separate == 0) {
			total.push_back(each_image);
			each_image = "";
			count_for_separate = 10;
		}
	
	}

	return total;
}

std::vector<vector<int>> ofApp::getTotalMaps() {
	string total_map_string = getImageFromFile();
	vector<std::string> string_maps = selectEachImage(total_map_string);
	vector<vector<int>> result;
	for (int i = 0; i < string_maps.size(); i++) {
		vector<string> string_array = splitter(" ", string_maps[i]);
		vector<int> each_map;
		for (int k = 0; k < string_array.size(); k++) {
			int temp;
			temp = atoi(string_array[k].c_str());
			each_map.push_back(temp);
		}
		result.push_back(each_map);
	}
	return result;
}

void ofApp::move() {
	ofRectangle new_step = ofRectangle(player_.getBody());
	switch (player_.getDirection()) {
	case UP:
		new_step.setPosition(new_step.getX(), new_step.getY() - new_step.getHeight());
		break;
	case RIGHT:
		new_step.setPosition(new_step.getX() + new_step.getHeight(), new_step.getY());
		break;
	case LEFT:
		new_step.setPosition(new_step.getX() - new_step.getHeight(), new_step.getY());
		break;
	case DOWN:
		new_step.setPosition(new_step.getX(), new_step.getY() + new_step.getHeight());
		break;
	}
	BackgroundSegments *intersect_segment = &background_.findIntersectPart(new_step);
	cout << intersect_segment->getElement() << endl;

	switch (intersect_segment->getElement()) {
	case FLOOR:
		player_.setPosition(new_step.getX(), new_step.getY());
		break;
	case WALL:
		break;
	case REDDOOR:
		if (player_.useRedKey()) {
			
			intersect_segment->replaceElement();   //QUESTION???
			cout << 3 + intersect_segment->getElement() << endl;

			if (intersect_segment->getElement() != NULL) {
				cout << intersect_segment->getElement() << endl;
			}
			else {
				cout << "NONE" << endl;
			}
			
			player_.setPosition(new_step.getX(), new_step.getY());
			cout << "??" << endl;
			break;
		}
		break;
	case YELLOWDOOR:
		if (player_.useYellowKey()) {
			intersect_segment->replaceElement();
			player_.setPosition(new_step.getX(), new_step.getY());
			break;
		}
		break;
	case FLOORDOOR:
		if (player_.useFloorKey()) {
			intersect_segment->replaceElement();
			player_.setPosition(new_step.getX(), new_step.getY());
			state_ = NEXTFLOOR;
			break;
		}
		break;
	}
	
}

void ofApp::drawEnd() {

}

void ofApp::drawInfo() {
	std::string total_info = "-----Player-----\n";
	total_info += "--Level: " + std::to_string(player_.getLevel()) + "\n";
	total_info += "--Max health: " + std::to_string(player_.getMaxHealth()) + "\n";
	total_info += "--Current health: " + std::to_string(player_.getCurrentHealth()) + "\n";
	total_info += "--Attack: " + std::to_string(player_.getAttack()) + "\n";
	total_info += "--Defense: " + std::to_string(player_.getDefense()) + "\n";
	total_info += "--Red key number: " + std::to_string(player_.getRedKeyNum()) + "\n";
	total_info += "--Yellow key number: " + std::to_string(player_.getYellowKeyNum()) + "\n";
	total_info += "--Floor key number: " + std::to_string(player_.getFloorKeyNum()) + "\n";
	total_info += "--Coin: " + std::to_string(player_.getCoin()) + "\n";

	ofSetColor(0, 0, 0);
	ofDrawBitmapString(total_info, ofGetWindowWidth() / 10, ofGetWindowHeight() / 10);
}