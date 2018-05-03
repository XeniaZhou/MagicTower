#include "ofApp.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <chrono>
#include <thread>

using namespace tower;


const vector<vector<string>> ofApp::rita_lines_ = {
	{"???: Hi, stranger, I see your confusion, just like me when I first came to this place.", "I: ...so who are you£¿And where am I?",
	"???: I am Rita, an unfortunate person just like you.", "Rita: I heard a dealer's words that this place is a magic tower, confined many people, \n and the only way to escape from here is to release the princess",
	"Rita: I tried but failed, but I see you may be good at it. I can give you some tips \n as you move forward, and please always remember, keep concious."
},
{"Rita: make sure consider your attack and defense as well as those monsters' \n before you combet them. You cannot get rid of the fight easily, can you?",
"Rita: ...", "Rita: wait a minute...has you done something sinful? I mean, annoy someone or ...", "I: I don't think so", "Rita: alright, just keep going and forget my previous question"

},
{"Rita: hi, well, actually I heard some store about my previous question", "Rita: ...", "Rita: the story says most people prisoned here are guilty and they are \n waiting for one to save them...",
"I: and you know that you are one of 'most people' who cannot leave here", "Rita: ...it's not your business"

},
{"Rita: I have thought about your words for a while...yes, you are right.\n I did do something that did not sound well...but I did not mean that",
"I: you are guilty without punishment", "Rita: RIGHT! But I can pay for that! please, I know you are my only hope..."

},
{"Rita: save me, please"
}
};

const vector<string> ofApp::natasha_lines_ = {
	"???: I am natasha, the princess", "Natasha: you are a person with innocent heart and that is why you are chosen.", 
	"Natasha: I cannot stand with you becasue of my duty, but I believe on your decision", "Natasha: it is your time now"
};




//--------------------------------------------------------------
void ofApp::setup() {
	bgm_.load("music/bgm.mp3");
	combat_sound_.load("music/combat.wav");
	take_item_sound_.load("music/take-gem.wav");
	died_.load("music/died.mp3");
	end_.load("music/end.mp3");
	bgm_.setVolume(0.15);
	died_.setVolume(0.12);
	end_.setVolume(0.15);
	combat_sound_.setVolume(0.3);
	take_item_sound_.setVolume(0.3);
	bgm_.play();							//sound loading and setting

	dialog_box_.setup();
	attack_monster_button_.addListener(this, &ofApp::decideAttackMonster);
	avoid_monster_button_.addListener(this, &ofApp::decideAvoidMonster);			//buttons and panel setup
	dialog_box_.add(attack_monster_button_.setup("yes"));
	dialog_box_.add(avoid_monster_button_.setup("no"));


	state_ = PROCESSING;
	vector<vector<int>> total = getTotalMaps();
	floor_num_ = 0;
	for (int i = 0; i < total.size(); i++) {
		Background temp = Background();
		temp.createMap(total[i]);
		maps_.push_back(temp);
	}
	background_ = &maps_[floor_num_];				//background setup
	

	ofSetFrameRate(60);
	loader_.load("gif/game-over2.gif");
	ofEnableAlphaBlending();
	startTime = ofGetElapsedTimeMillis();
	
	ofSetFrameRate(60);
	loader_rita_.load("gif/change.gif");
	ofEnableAlphaBlending();
	startTime2 = ofGetElapsedTimeMillis();

	ofSetFrameRate(60);
	loader_natasha_.load("gif/order.gif");
	ofEnableAlphaBlending();
	startTime3 = ofGetElapsedTimeMillis();			//gif setup
	
	player_ = Player();
	player_.setPosition(background_->getPosition().x, background_->getPosition().y);
	player_.setSize(background_->getRec().getHeight());									//player setup
	detecter_ = 0;
	floor_num_ = 0;
}

int index = 0;
int index2 = 0;
int index3 = 0;
//--------------------------------------------------------------
void ofApp::update(){
	

	if (should_update_) {
		draw();
		if (state_ == DEAD) {
			bgm_.stop();
			if (play_died) {
				died_.play();
				play_died = false;
			}
			
			if (ofGetElapsedTimeMillis() - startTime >= gifDelay) {			//
				index++;													//
				if (index > loader_.pages.size() - 1) {						//parts like this are used to form the gif
					index = 0;												//
				}															//
				startTime = ofGetElapsedTimeMillis();						//
			}
		} else 
		if (state_ == RITAEND) {
			bgm_.stop();
			if (play_end) {
				end_.play();
				play_end = false;
			}
			
			if (ofGetElapsedTimeMillis() - startTime2 >= gifDelay2) {
				index2++;
				if (index2 > loader_rita_.pages.size() - 1) {
					index2 = 0;
				}
				startTime2 = ofGetElapsedTimeMillis();
			}
		} else 
		if (state_ == NATASHAEND) {
			bgm_.stop();
			if (play_end) {
				end_.play();
				play_end = false;
			}
			if (ofGetElapsedTimeMillis() - startTime3 >= gifDelay3) {
				index3++;
				if (index3 > loader_rita_.pages.size() - 1) {
					index3 = 0;
				}
				startTime3 = ofGetElapsedTimeMillis();
			}
		} else 
		if (state_ == PROCESSING) {
			if (!bgm_.getIsPlaying()) {
				bgm_.play();
			}
			BackgroundSegments *segment = &background_->findIntersectPart(player_.getBody());
			if (segment->containKey()) {
				take_item_sound_.play();
				player_.addKey(segment->getKey());
				segment->removeKey();
				
			}
			if (segment->containGem()) {
				take_item_sound_.play();
				player_.takeGem(segment->getGem());
				segment->removeGem();
			}
			if (segment->containMonster()) {
				combat_sound_.play();
				player_.attackMonster(segment->getMonster());							//148-171 are interactions with the current segment
				if (player_.isDead()) {
					state_ = DEAD;			
				}
				else {
					segment->removeMonster();
				}
			}
			
		}	
		
	}

	should_update_ = true;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawInfo();
	switch (state_) {
	case NEXTFLOOR:
		goToNextFloor();
		
		has_talk_with_npc_ = false;
		state_ = PROCESSING;
		player_.setPosition(background_->getPosition().x, background_->getPosition().y);//reset positon when go to next floor
		

		break;
	case PROCESSING:
		background_ = &maps_[floor_num_];
		background_->update();

		player_.drawPlayer();				//normally keep trake of the change
		break;
	case RITAEND:
		drawRitaEnd();
		break;
	case NATASHAEND:
		drawNatashaEnd();
		break;
	case ENCOUNTER_MONS: {
		background_->update();

		player_.drawPlayer();
		ofSetColor(150, 195, 180);
		ofRectangle temp = ofRectangle(ofGetWindowWidth() / 4.7, ofGetWindowHeight() / 2.5, ofGetWindowHeight(), ofGetWindowWidth() / 6);
		dialog_box_.setPosition(temp.x + temp.getWidth() / 2, temp.y + temp.getHeight() / 2);
		ofDrawRectangle(temp);																	//here we draw a rectangle as a dialog box
		ofSetColor(0, 0, 0);
		ofDrawBitmapString(text_, ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);				//and add text

		dialog_box_.draw();																		//draw the panel and buttons
		break;
	}
	case DEAD:
		drawDied();
		break;
	case TALK_WITH_NPC: {
		if (detecter_ >= content_.size()) {														//here we used detecter I mentioned in .h file
			detecter_ = 0;
			state_ = PROCESSING;
			has_talk_with_npc_ = true;
			break;
		}
		background_->update();

		player_.drawPlayer();
		
			ofSetColor(150, 195, 180);
			ofRectangle temp2 = ofRectangle(ofGetWindowWidth() / 4.5, ofGetWindowHeight() / 2.5, ofGetWindowHeight(), ofGetWindowWidth() / 6);
			dialog_box_.setPosition(temp2.x + temp2.getWidth() / 2, temp2.y + temp2.getHeight() / 2);
			ofDrawRectangle(temp2);
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(content_[detecter_], ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
			
		
		
		break;
	}
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

}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofRectangle intersect = player_.getBody();
	intersect.setPosition(x, y);
	BackgroundSegments *intersect_segment = &background_->findIntersectPart(intersect);
	if (button == 0 && state_ == TALK_WITH_NPC) {										//when talking with npc, left click works as continue print out new line
		detecter_++;
	}
	else if (has_talk_with_npc_ && button == 0 && intersect_segment->containNPC() && floor_num_ == 4) { //this is the place decide which ending
		switch (intersect_segment->getNPC()->getName()) {
		case RITA:
			state_ = RITAEND;
			break;
		case NATASHA:
			state_ = NATASHAEND;
			break;
		}
	}
	
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
		if (!each_line[i].empty()) {
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
	switch (player_.getDirection()) {					//form a new_step in front of the player
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
	if (new_step.x < background_->getPosition().x || new_step.x > background_->getPosition().x + background_->getRec().getHeight()
		|| new_step.y < background_->getPosition().y || new_step.y > background_->getPosition().y + background_->getRec().getHeight()) {
		return;						//if the new_step is out of bound, then return.
	}
	BackgroundSegments *intersect_segment = &background_->findIntersectPart(new_step);


	switch (intersect_segment->getElement()) {
	case FLOOR:
		if (intersect_segment->containMonster()) {					//when encounter monsters, collate the information and wait for the response
			text_ = "the monster has " + to_string(intersect_segment->getMonster()->getAttack()) + " attack, ";
			text_ += to_string(intersect_segment->getMonster()->getDefence()) + " defense, and ";
			text_ += to_string(intersect_segment->getMonster()->getHealth()) + " health.\n";
			text_ += "Do you want to defeat it?";
			state_ = ENCOUNTER_MONS;
			break;
		}
		else if (intersect_segment->containNPC()) { //place to set the content_
			if (intersect_segment->getNPC()->getName() == RITA) {
				content_ = rita_lines_[floor_num_];		
			}
			else {
				content_ = natasha_lines_;
			}
			state_ = TALK_WITH_NPC;
			break;
		}
		player_.setPosition(new_step.getX(), new_step.getY());
		
		break;
	case WALL:
		break;
	case REDDOOR:
		if (player_.useRedKey()) {
			
			intersect_segment->replaceElement();   //QUESTION???
			player_.setPosition(new_step.getX(), new_step.getY());
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
	
			state_ = NEXTFLOOR;
			break;
		}
		break;
	}
	
}

void ofApp::drawRitaEnd() {
	ofBackground(0);

	ofSetColor(255, 255, 255, 255);
	ofImage img = loader_rita_.pages[index2]; //methods from ofxGif

	ofPixels pix = img.getPixels();
	img.setFromPixels(pix);
	img.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void ofApp::drawNatashaEnd() {
	ofBackground(0);

	ofSetColor(255, 255, 255, 255);
	ofImage img = loader_natasha_.pages[index3];

	ofPixels pix = img.getPixels();
	img.setFromPixels(pix);
	img.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
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


void ofApp::goToNextFloor() {
	floor_num_++;
}



void ofApp::decideAttackMonster() {
	state_ = PROCESSING;
	switch (player_.getDirection()) {
	case UP:
		player_.setPosition(player_.getBody().x, player_.getBody().y - player_.getBody().getHeight());
		break;
	case RIGHT:
		player_.setPosition(player_.getBody().x + player_.getBody().getHeight(), player_.getBody().y);
		break;
	case LEFT:
		player_.setPosition(player_.getBody().x - player_.getBody().getHeight(), player_.getBody().y);
		break;
	case DOWN:
		player_.setPosition(player_.getBody().x, player_.getBody().y + player_.getBody().getHeight());
		break;
	}
}

void ofApp::decideAvoidMonster() {
	state_ = PROCESSING;
}

void ofApp::drawDied() {
	ofBackground(0);

	ofSetColor(255, 255, 255, 255);
	ofImage img = loader_.pages[index];
	
	ofPixels pix = img.getPixels();
	img.setFromPixels(pix);
	img.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void ofApp::drawCommunication(vector<string> content) {
	ofSetColor(150, 195, 180);
	ofRectangle temp = ofRectangle(ofGetWindowWidth() / 4.7, ofGetWindowHeight() / 2.5, ofGetWindowHeight(), ofGetWindowWidth() / 6);
	dialog_box_.setPosition(temp.x + temp.getWidth() / 2, temp.y + temp.getHeight() / 2);
	ofDrawRectangle(temp);
	for (int i = 0; i < content.size(); i++) {
		ofSetColor(0, 0, 0);
		ofDrawBitmapString(content[i], ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
		Sleep(10000);
	}
}