#pragma once
#include "ofMain.h"
#include "BackgroundSegments.h"
#include <vector>

namespace tower {
	class Background {
	private:
		int floor_num_;
		ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
		ofVec2f background_position_;
		ofRectangle background_;
		std::vector<BackgroundSegments> floor_map_;
		static const float size_modifier_; // The proportion of the screen width a body square is
	public:
		Background();
		void createMap(std::vector<int> maps);
		//void goToNextFloor();
		void update();
		std::vector<BackgroundSegments> getFloorMap();
		ofVec2f getPosition();
		ofRectangle getRec();
		BackgroundSegments &findIntersectPart(ofRectangle player);
		bool isEnd();
	};
}