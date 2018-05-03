#include "BackgroundSegments.h"

using namespace tower;

BackgroundSegments::BackgroundSegments() {
	element_ = FLOOR;
	position_.set(0, 0);
	setImage();
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
		npc_ = nullptr;
		break;
	case 1:
		element_ = FLOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		npc_ = nullptr;
		break;
	case 2:
		element_ = REDDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		npc_ = nullptr;
		break;
	case 3:
		element_ = YELLOWDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		npc_ = nullptr;
		break;
	case 4:
		element_ = FLOORDOOR;
		key_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		npc_ = nullptr;
		break;
	case 5:
		element_ = FLOOR;
		gem_ = new Gem(REDGEM);
		key_ = nullptr;
		npc_ = nullptr;
		monster_ = nullptr;
		break;
	case 6:
		element_ = FLOOR;
		gem_ = new Gem(BLUEGEM);
		key_ = nullptr;
		npc_ = nullptr;
		monster_ = nullptr;
		break;
	case 7:
		element_ = FLOOR;
		key_ = new Key(REDKEY);
		npc_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 8:
		element_ = FLOOR;
		key_ = new Key(YELLOWKEY);
		npc_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 9:
		element_ = FLOOR;
		key_ = new Key(FLOORKEY);
		npc_ = nullptr;
		gem_ = nullptr;
		monster_ = nullptr;
		break;
	case 10:
		element_ = FLOOR;
		monster_ = new Monster(SLIME);
		key_ = nullptr;
		gem_ = nullptr;
		npc_ = nullptr;
		break;
	case 11:
		element_ = FLOOR;
		monster_ = new Monster(GHOST);
		key_ = nullptr;
		gem_ = nullptr;
		npc_ = nullptr;
		break;
	case 12:
		element_ = FLOOR;
		monster_ = new Monster(SOLDIER);
		key_ = nullptr;
		gem_ = nullptr;
		npc_ = nullptr;
		break;
	case 13:
		element_ = FLOOR;
		monster_ = new Monster(SKELETON);
		key_ = nullptr;
		gem_ = nullptr;
		npc_ = nullptr;
		break;
	case 14:
		element_ = FLOOR;
		monster_ = new Monster(BAT);
		key_ = nullptr;
		gem_ = nullptr;
		npc_ = nullptr;
		break;
	case 15: {
		element_ = FLOOR;
		npc_ = new NPC(RITA);
		monster_ = nullptr;
		key_ = nullptr;
		gem_ = nullptr;
		break;
	}
	case 16:
		element_ = FLOOR;
		npc_ = new NPC(NATASHA);
		monster_ = nullptr;
		key_ = nullptr;
		gem_ = nullptr;
		break;
	
	}
	setImage();
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

void BackgroundSegments::setImage() {
	switch (element_) {
		case WALL:
			segment_color_ = ofColor(140, 135, 115);
			segment_image_.load("image/wall.png");
			break;
		case FLOOR:
			segment_color_ = ofColor(105, 190, 95);
			segment_image_.load("image/floor.png");
			break;
		case REDDOOR:
			segment_color_ = ofColor(255, 155, 125);
			segment_image_.load("image/red-door.png");
			break;
		case YELLOWDOOR:
			segment_color_ = ofColor(255, 235, 90);
			segment_image_.load("image/yellow-door.png");
			break;
		case FLOORDOOR:
			segment_color_ = ofColor(180, 180, 180);
			segment_image_.load("image/floor-door.png");
			break;
	}
}

ofRectangle BackgroundSegments::getRectangle() {
	return rec_;
}

void BackgroundSegments::replaceElement() {
	element_ = FLOOR;
	setImage();
}

NPC* BackgroundSegments::getNPC() {
	return npc_;
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

bool BackgroundSegments::containNPC() {
	return npc_;
}

void BackgroundSegments::drawBackgroundSegment() {
	ofSetColor(segment_color_);
	segment_image_.draw(position_.x, position_.y, rec_.getHeight(), rec_.getHeight());
	if (key_) {
		ofSetColor(key_->getColor());
		key_->getImage().draw(position_.x, position_.y, rec_.getHeight(), rec_.getHeight());
		

	} else if (gem_) {
		ofSetColor(gem_->getColor());
		gem_->getImage().draw(position_.x, position_.y, rec_.getHeight(), rec_.getHeight());

	}
	else if (monster_) {
		ofSetColor(monster_->getColor());
		monster_->getImage().draw(position_.x, position_.y, rec_.getHeight(), rec_.getHeight());
	}
	else if (npc_) {
		ofSetColor(255, 255, 255);
		npc_->getImage().draw(position_.x, position_.y, rec_.getHeight(), rec_.getHeight());
	}
}
