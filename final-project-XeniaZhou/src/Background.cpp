#include "Background.h"
#include <vector>

using namespace maps;

const float Background::size_modifier_ = 0.1;

Background::Background() {
	int height = ofGetWindowHeight();
	int width = ofGetWindowWidth();

	screen_dims_.set(width, height);
	if (height > width) {
		background_.setSize(width, width);
		background_position_.set(0, 0);
	}
	else {
		background_.setSize(height, height);
		background_position_.set(width - height, 0);
	}
}

void Background::createMap(std::vector<vector<int>> maps) {
	int count = 0;
	float y_position = background_position_.y;
	for (int i = 0; i < maps.size(); i++) {
		for (int k = 0; k < maps[0].size(); k++) {
			if (count == 100) {
				count = 0;
				y_position += background_.getHeight() * size_modifier_;
			}
			float adding = count * background_.getHeight() * size_modifier_;
			float size = background_.getHeight * size_modifier_;
			BackgroundSegments each = BackgroundSegments(BackgroundElement(maps[i][k]), background_position_.x + adding,
				y_position, size);
			floor_map_[i].push_back(each);
			count++;
		}
	}
	

}

void Background::resize(int w, int h) {

}

void Background::update() {

}