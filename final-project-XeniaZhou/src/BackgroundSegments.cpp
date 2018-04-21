#include "BackgroundSegments.h"

using namespace maps;

BackgroundSegments::BackgroundSegments() {
	element_ = FLOOR;
	position_.set(0, 0);
	color_ = ofColor(115, 170, 25);
	rec_.setSize(0.0, 0.0);
}

BackgroundSegments::BackgroundSegments(BackgroundElement e, int x, int y, int size) {
	element_ = e;
	position_.set(x, y);
	rec_.setPosition(x, y);
	rec_.setSize(size, size);
}

void BackgroundSegments::addKey(Key k) {
	key_ = new Key(k);
}

void BackgroundSegments::addGem(Gem g) {
	gem_ = new Gem(g);
}


void BackgroundSegments::addMonster(Monster m) {
	monster_ = new Monster(m);
}

void BackgroundSegments::setColor() {
	switch (element_) {
		case WALL:
			color_ = ofColor(65, 65, 20);
			break;
		case FLOOR:
			color_ = ofColor(115, 170, 25);
			break;
		case REDDOOR:
			color_ = ofColor(160, 45, 10);
			break;
		case YELLOWDOOR:
			color_ = ofColor(225, 180, 60);
			break;
		case FLOORDOOR:
			color_ = ofColor(100, 100, 100);
			break;
	}
}

ofRectangle BackgroundSegments::getRectangle() {
	return rec_;
}

void BackgroundSegments::replaceElement(BackgroundElement e) {
	element_ = e;
	setColor();
}

Keys BackgroundSegments::getKey() {
	return key_->getKeyType;
}

void BackgroundSegments::drawBackgroundSegment() {
	ofSetColor(color_);
	ofDrawRectangle(rec_);
	if (key_) {
		ofSetColor(key_->getColor());
		ofDrawCircle(position_.x, position_.y, rec_.getHeight() / 2);
		

	} else if (gem_) {
		ofSetColor(gem_->getColor());
		ofDrawTriangle(position_.x, position_.y, position_.x + rec_.getHeight(), position_.y, 
			position_.x + rec_.getWidth(), position_.y + rec_.getWidth());

	}
	else if (monster_) {
		ofSetColor(monster_->getColor());
		
	}
}
