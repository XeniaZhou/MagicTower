#pragma once
#include "ofMain.h"

namespace maps {
	typedef enum {
		SLIME = 0,
		GHOST,
		SOLDIER

	} Monsters;

	class Monster {
	private:
		Monsters m_;
		ofColor monster_color_;
		double attack_;
		double defence_;
		double health_;
	public:
		Monster();
		Monster(Monsters k);
		Monster(Monster& k);
		ofColor getColor();

		Monsters getMonsterType();
	};
}