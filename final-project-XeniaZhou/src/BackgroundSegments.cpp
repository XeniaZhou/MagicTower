#include "BackgroundSegments.h"

using namespace maps;

BackgroundSegments::BackgroundSegments() {
	element_ = FLOOR;
	position_.set(0, 0);
	color_ = ofColor(115, 170, 25);
	rec_.setSize(0.0, 0.0);
}

BackgroundSegments::BackgroundSegments(int e, int x, int y, int size) {
	
	position_.set(x, y);
	rec_.setPosition(x, y);
	rec_.setSize(size, size);
	switch (e) {
	case 0:
		element_ = WALL;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 1:
		element_ = FLOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 2:
		element_ = REDDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 3:
		element_ = YELLOWDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 4:
		element_ = FLOORDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 5:
		element_ = FLOOR;
		gem_ = new Gem(REDGEM);
		key_ = nullptr;

		monster_ = nullptr;
		break;
	case 6:
		element_ = FLOOR;
		gem_ = new Gem(BLUEGEM);
		key_ = nullptr;

		monster_ = nullptr;
		break;
	case 7:
		element_ = FLOOR;
		key_ = new Key(REDKEY);
	
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 8:
		element_ = FLOOR;
		key_ = new Key(YELLOWKEY);

		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 9:
		element_ = FLOOR;
		key_ = new Key(FLOORKEY);
	
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 10:
		element_ = FLOOR;
		monster_ = new Monster(SLIME);
		key_ = nullptr;
		gem_ = nullptr;
	
		break;
	case 11:
		element_ = FLOOR;
		monster_ = new Monster(GHOST);
		key_ = nullptr;
		gem_ = nullptr;
		break;
	case 12:
		element_ = FLOOR;
		monster_ = new Monster(SOLDIER);
		key_ = nullptr;
		gem_ = nullptr;
		break;
	
	}
	setColor();
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

void BackgroundSegments::removeGem() {
	gem_ = nullptr;
}

void BackgroundSegments::removeKey() {
	key_ = nullptr;
}

void BackgroundSegments::removeMonster() {
	monster_ = nullptr;
}

void BackgroundSegments::setColor() {
	switch (element_) {
		case WALL:
			color_ = ofColor(31, 31, 7);
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

void BackgroundSegments::replaceElement() {
	element_ = FLOOR;
	setColor();
}

Key* BackgroundSegments::getKey() {
	return key_;
}

Gem* BackgroundSegments::getGem() {
	return gem_;
}

Monster* BackgroundSegments::getMonster() {
	return monster_;
}

BackgroundElement BackgroundSegments::getElement() {
	return element_;
}

bool BackgroundSegments::containKey() {
	return key_;
}
bool BackgroundSegments::containGem() {
	return gem_;
}
bool BackgroundSegments::containMonster() {
	return monster_;
}

void BackgroundSegments::drawBackgroundSegment() {
	ofSetColor(color_);
	ofDrawRectangle(rec_);
	if (key_) {
		ofSetColor(key_->getColor());
		ofDrawCircle(position_.x + rec_.getHeight() / 2, position_.y + rec_.getHeight() / 2, rec_.getHeight() / 2);
		

	} else if (gem_) {
		ofSetColor(gem_->getColor());
		ofDrawTriangle(position_.x, position_.y, position_.x + rec_.getHeight(), position_.y, 
			position_.x + rec_.getWidth(), position_.y + rec_.getWidth());

	}
	else if (monster_) {
		ofSetColor(monster_->getColor());
		ofDrawRectangle(rec_);
	}
}
