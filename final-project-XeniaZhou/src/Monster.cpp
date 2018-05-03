#include "Monster.h"

using namespace tower;

Monster::Monster() {
	attack_ = 0.0;
	defence_ = 0.0;
	health_ = 0.0;
}

Monster::Monster(Monsters monster) {
	monster_color_ = ofColor(255, 255, 255);
	switch (monster) {
	case SLIME:
		m_ = SLIME;
		attack_ = 10;
		defence_ = 10;
		health_ = 10;
		monster_image_.load("image/slime.png");
		break;
	case GHOST:
		m_ = GHOST;
		attack_ = 25;
		defence_ = 10;
		health_ = 15;
		monster_image_.load("image/ghost.png");
		break;
	case SOLDIER:
		m_ = SOLDIER;
		attack_ = 40;
		defence_ = 40;
		health_ = 50;
		monster_image_.load("image/soldier.png");
		break;
	case BAT:
		m_ = BAT;
		attack_ = 35;
		defence_ = 35;
		health_ = 20;
		monster_image_.load("image/bat.png");
		break;
	case SKELETON:
		m_ = SKELETON;
		attack_ = 25;
		defence_ = 25;
		health_ = 35;
		monster_image_.load("image/skeleton.png");
		break;
	}
}

Monster::Monster(Monster& monster) {
	m_ = monster.m_;
	Monster(m_);
}

ofColor Monster::getColor() {
	return monster_color_;
}

ofImage Monster::getImage() {
	return monster_image_;
}

Monsters Monster::getMonsterType() {
	return m_;
}

double Monster::getAttack() {
	return attack_;
}

double Monster::getDefence() {
	return defence_;
}

double Monster::getHealth() {
	return health_;
}

void Monster::setHealth(double health) {
	health_ = health;
}

bool Monster::isDead() {
	return health_ <= 0.0;
}
