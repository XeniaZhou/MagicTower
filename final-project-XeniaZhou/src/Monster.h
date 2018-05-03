#pragma once
#include "ofMain.h"

namespace tower {
	typedef enum {
		EMPTYMONSTER = 0,
		SLIME,
		GHOST,
		SOLDIER,
		BAT,
		SKELETON

	} Monsters;

	class Monster {
	private:
		Monsters m_;
		ofImage monster_image_;
		ofColor monster_color_;
		double attack_;
		double defence_;
		double health_;
	public:
		Monster();
		Monster(Monsters k);
		Monster(Monster& k);
		ofColor getColor();
		ofImage getImage();
		Monsters getMonsterType();
		void setHealth(double health);
		double getHealth();
		double getAttack();
		double getDefence();
		bool isDead();
	};
}