#pragma once

#include "ofMain.h"
#include <string>
#include <vector>
#include <regex>
#include "Background.h"
#include "Player.h"


namespace maps {
	typedef enum {
		PROCESSING = 0,
		NEXTFLOOR,
		END
	} States;

	class ofApp : public ofBaseApp{
	private:
		vector<string> selectEachImage(string all);
		string getImageFromFile();
		vector<string> splitter(string in_pattern, string& content);
		Background background_;
		Player player_;
		States state_;
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
		void drawEnd();
		void drawInfo();
};
}

