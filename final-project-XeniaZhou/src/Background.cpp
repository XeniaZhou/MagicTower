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
	floor_map_ = vector<vector<BackgroundSegments>>(5);
	int count = 0;
	float y_position = background_position_.y;
	for (int i = 0; i < maps.size(); i++) {
		for (int k = 0; k < maps[i].size(); k++) {
			if (count == 10) {
				count = 0;
				y_position += background_.getHeight() * size_modifier_;
			}
			float adding = count * background_.getHeight() * size_modifier_;
			float size = background_.getHeight() * size_modifier_;
			BackgroundSegments each = BackgroundSegments(maps[i][k], background_position_.x + adding,
				y_position, size);
			floor_map_[i].push_back(each);
			count++;
		}
	}
	

}

bool Background::isEnd() {
	return floor_map_.empty();
}

void Background::goToNextFloor() {
	floor_map_.erase(floor_map_.begin());
}

void Background::update() {
	for (auto each_segment : floor_map_[0]) {
		each_segment.drawBackgroundSegment();
	}
}

std::vector<vector<BackgroundSegments>> Background::getFloorMap() {
	return floor_map_;
}

ofVec2f Background::getPosition() {
	return background_position_;
}

ofRectangle Background::getRec() {
	return background_;
}

BackgroundSegments& maps::Background::findIntersectPart(ofRectangle player) {
	for (int i = 0; i < floor_map_[0].size(); i++) {
		BackgroundSegments &segment = floor_map_[0][i];
		if (player.intersects(segment.getRectangle())) {
			return segment;
		}
	}
	return BackgroundSegments();
	
}

