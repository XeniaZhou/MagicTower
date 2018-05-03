#pragma once

#include "ofMain.h"
#include <string>
#include <vector>
#include <regex>
#include "Background.h"
#include "Player.h"
#include "ofxGui.h"
#include "ofxGif.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"



namespace tower {
	typedef enum {
		START = 0,
		PROCESSING,
		ENCOUNTER_MONS,
		TALK_WITH_NPC,
		NEXTFLOOR,
		DEAD,
		RITAEND,
		NATASHAEND

	} States;

	class ofApp : public ofBaseApp{
	private:

		static const vector<vector<string>> rita_lines_;  
		static const vector<string> natasha_lines_;   //the designed lines of two NPCs

		ofxPanel dialog_box_;
		ofxButton attack_monster_button_;
		ofxButton avoid_monster_button_; //button and panel are used when we asked whether we defeat monsters

		ofSoundPlayer bgm_;
		ofSoundPlayer combat_sound_;
		ofSoundPlayer take_item_sound_;
		ofSoundPlayer died_;
		ofSoundPlayer end_;           //sounds
		
		
		ofxGIF::fiGifLoader loader_; //gif for died
		int index = 0;
		float gifDelay = 100;
		float startTime;

		ofxGIF::fiGifLoader loader_rita_; //gif for ending one
		int index2 = 0;
		float gifDelay2 = 100;
		float startTime2;

		ofxGIF::fiGifLoader loader_natasha_; //gif for ending two
		int index3 = 0;
		float gifDelay3 = 100;
		float startTime3;

		Background* background_;
		Player player_;
		States state_;
		vector<Background> maps_;
		int floor_num_;


		std::string text_;											//this text_ record the information of monsters so that we can draw them in draw method
		std::vector<string> content_;								//this content_ include and update the lines we need to print out for NPC part
		int detecter_;												//this detecter_ is to detect whether the lines has all printed out. It works as when the 
																	//mouse listener works, its value increases by 1, and in the draw method, when its value is the 
																	//same as the size of content_, then change back to 0 and set the state_ to PROCESSINg to end the 
																	//drawing procedure for TALK_WITH_NPC
		vector<string> selectEachImage(string all);
		string getImageFromFile();
		vector<string> splitter(string in_pattern, string& content);//These methods are developed from my assignment about Naive Bayes. The getImageFromFile() works to 
																	//conduct content from file to our local variable, then using selectEachImage() and splitter to seperate them
																	//and conduct "1" to 1

		void goToNextFloor();										//simply add one to the floor num
		
		
		bool play_end = true;			//as we start playing the end music from update(), I set this variable to make sure the .play() only run once
		bool play_died = true;
		bool has_talk_with_npc_ = false;//this bool used to detect whether we can choose an ending, the requirement is that the player needs to talk with at least one of them

		bool should_update_ = true;     // A flag boolean used in the update() function. Due to the frame dependent animation we've
										// written, and the relatively low framerate, a bug exists where users can prefire direction 
										// changes faster than a frame update. Our solution is to force a call to update on direction
										// changes and then not update on the next frame to prevent the snake from skipping across the screen.
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);	//works when we need to continue the talk with NPC and the final ending choosing part
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<vector<int>> getTotalMaps();				//developed from those three private methods, what it does is combine them and used to form the set of maps
		void move();									//this implement decide whether we can move in that direction, which is one of the massy implements.
		void drawRitaEnd();	
		void drawInfo();
		void drawNatashaEnd();
		void drawDied();
		void drawCommunication(vector<string> content);//several draw method for different aspects

		void decideAttackMonster();
		void decideAvoidMonster();						//these two methods work as the reactors after catch the button click
};
}

