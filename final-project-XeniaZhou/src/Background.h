#pragma once
#include "ofMain.h"
#include "BackgroundSegments.h"
#include <vector>

namespace maps {
	class Background {
	private:
		ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
		ofVec2f background_position_;
		ofRectangle background_;
		std::vector<vector<BackgroundSegments>> floor_map_;
		static const float size_modifier_; // The proportion of the screen width a body square is
	public:
		Background();
		void createMap(std::vector<vector<int>> maps);
		void resize(int w, int h);
		void update();


	};
}