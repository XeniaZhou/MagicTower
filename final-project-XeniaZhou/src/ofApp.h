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
		static const vector<string> natasha_lines_;
		ofxPanel dialog_box_;
		ofxButton attack_monster_button_;
		ofxButton avoid_monster_button_;
		ofSoundPlayer bgm_;
		ofSoundPlayer combat_sound_;
		ofSoundPlayer take_item_sound_;
		ofSoundPlayer died_;
		ofSoundPlayer end_;
		
		
		ofxGIF::fiGifLoader loader_;
		int index = 0;
		float gifDelay = 100;
		float startTime;

		ofxGIF::fiGifLoader loader_rita_;
		int index2 = 0;
		float gifDelay2 = 100;
		float startTime2;

		ofxGIF::fiGifLoader loader_natasha_;
		int index3 = 0;
		float gifDelay3 = 100;
		float startTime3;

		std::string text_;
		std::vector<string> content_;
		int detecter_;
		vector<string> selectEachImage(string all);
		string getImageFromFile();
		vector<string> splitter(string in_pattern, string& content);
		void goToNextFloor();
		Background* background_;
		Player player_;
		States state_;
		vector<Background> maps_;
		int floor_num_;
		

		bool has_talk_with_npc_ = false;
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
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		vector<vector<int>> getTotalMaps();
		void move();
		void drawRitaEnd();
		void drawInfo();
		void drawNatashaEnd();
		void decideAttackMonster();
		void decideAvoidMonster();
		void drawDied();
		void drawCommunication(vector<string> content);
};
}

