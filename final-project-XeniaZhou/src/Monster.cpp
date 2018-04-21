#include "Monster.h"

using namespace maps;

Monster::Monster() {
	attack_ = 0.0;
	defence_ = 0.0;
	health_ = 0.0;
}

Monster::Monster(Monsters monster) {
	monster_color_ = ofColor(200, 10, 10);
	switch (monster) {
	case SLIME:
		m_ = SLIME;
		attack_ = 10;
		defence_ = 10;
		health_ = 10;
		break;
	case GHOST:
		m_ = GHOST;
		attack_ = 30;
		defence_ = 5;
		health_ = 10;
		break;
	case SOLDIER:
		m_ = SOLDIER;
		attack_ = 20;
		defence_ = 20;
		health_ = 20;
		break;
	}
}

Monster::Monster(Monster& monster) {
	m_ = monster.m_;
	attack_ = monster.attack_;
	defence_ = monster.defence_;
	health_ = monster.health_;
}

ofColor Monster::getColor() {
	return monster_color_;
}

Monsters Monster::getMonsterType() {
	return m_;
}

