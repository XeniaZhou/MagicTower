#include "Player.h"

using namespace tower;

const float Player::modifier_ = 0.1;

Player::Player() {
	int window_width = ofGetWindowWidth();
	int window_height = ofGetWindowHeight();
	screen_dims_.set(window_width, window_height);
	attack_ = 15.0;
	defense_ = 5.0;
	max_health_ = 50.0;
	current_health_ = max_health_;
	current_direction_ = UP;
	red_key_num_ = 0;
	yellow_key_num_ = 0;
	floor_key_num_ = 0;
	coin_ = 0;
	exp_ = 0.0;
	level_ = 0;
	hero_color_ = ofColor(255, 255, 255);
	hero_image_.load("image/hero.png");
}

Player::Player(const Player& other) {
	int window_width = ofGetWindowWidth();
	int window_height = ofGetWindowHeight();
	screen_dims_.set(window_width, window_height);

	attack_ = other.attack_;
	defense_ = other.defense_;
	max_health_ = other.max_health_;
	current_health_ = other.current_health_;
	current_direction_ = other.current_direction_;
	red_key_num_ = other.red_key_num_;
	yellow_key_num_ = other.yellow_key_num_;
	floor_key_num_ = other.floor_key_num_;
	coin_ = other.coin_;
	position_.set(other.position_.x, other.position_.y);
	exp_ = other.exp_;
	level_ = other.level_;
	body_.set(other.body_);
	hero_color_ = ofColor(255, 255, 255);
	hero_image_.load("image/hero.png");
}

void Player::setPosition(float x, float y) {
	position_.set(x, y);
	body_.setPosition(x, y);
}

void Player::setSize(float size) {
	body_.setSize(size * modifier_, size * modifier_);
}

ofColor Player::getColor() {
	return hero_color_;
}
ofImage Player::getImage() {
	return hero_image_;
}
ofRectangle Player::getBody() {
	return body_;
}

void Player::addKey(Key* key) {
	if (key) {
		switch (key->getKeyType()) {
		case REDKEY:
			red_key_num_++;
			break;
		case YELLOWKEY:
			yellow_key_num_++;
			break;
		case FLOORKEY:
			floor_key_num_++;
			break;
		}
	}
}

//void Player::buyWeapon()

bool Player::isDead() {
	return current_health_ <= 0.0;
}

void Player::attackMonster(Monster* monster) {
	while (!isDead()) {
		if (monster->isDead()) {
		coin_ += monster->getAttack() + monster->getDefence();
		levelUp(monster->getAttack() + monster->getDefence());
		break;
	}
		if (attack_ > monster->getDefence()) {
			double new_monster_health = monster->getHealth() + monster->getDefence() - attack_;
			monster->setHealth(new_monster_health);
		} 
		if (monster->getAttack() > defense_) {
			double new_player_health = current_health_ + defense_ - monster->getAttack();
			current_health_ = new_player_health;
		}
	}
	
	
}

void Player::takeGem(Gem* gem) {
	if (gem) {
		switch (gem->getGemType()) {
		case REDGEM:
			attack_ += 2.0;
			break;
		case BLUEGEM:
			defense_ += 2.0;
			break;
		}
	}
}

void Player::levelUp(double experience) {
	exp_ += experience;
	while (true) {
		double reqirement = ((level_ + 1) * level_) * 18.0 + 30.0;
	
		if (exp_ >= reqirement) {
			level_++;
			attack_ += level_ * 0.8;
			defense_ += level_ * 0.8;
			max_health_ += level_ * 10;
			current_health_ = max_health_;
			exp_ -= reqirement;
		}
		else {
			break;
		}
	}
	
}
bool Player::useRedKey() {
	if (red_key_num_ == 0) {
		return false;
	}
	red_key_num_--;
	return true;
}

bool Player::useYellowKey() {
	if (yellow_key_num_ == 0) {
		return false;
	}
	yellow_key_num_--;
	return true;
}

bool Player::useFloorKey() {
	if (floor_key_num_ == 0) {
		return false;
	}
	floor_key_num_--;
	return true;
}

double Player::getAttack() {
	return attack_;
}

double Player::getDefense() {
	return defense_;
}

double Player::getMaxHealth() {
	return max_health_;
}

double Player::getCurrentHealth() {
	return current_health_;
}

Direction Player::getDirection() const {
	return current_direction_;
}

void Player::setDirection(Direction dir) {
	current_direction_ = dir;
}

void Player::drawPlayer() {
	ofSetColor(hero_color_);
	hero_image_.draw(position_.x, position_.y, body_.getHeight(), body_.getHeight());
}

int Player::getRedKeyNum() {
	return red_key_num_;
}

int Player::getYellowKeyNum() {
	return yellow_key_num_;
}

int Player::getFloorKeyNum() {
	return floor_key_num_;
}

int Player::getLevel() {
	return level_;
}

int Player::getCoin() {
	return coin_;
}