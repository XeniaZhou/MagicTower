#pragma once
#include "ofMain.h"
#include "Monster.h"
#include "Gem.h"
#include "Key.h"


namespace tower {

	typedef enum {
		UP = 0,
		DOWN,
		RIGHT,
		LEFT
	} Direction;

	class Player {
	private:
		Direction current_direction_; // The current direction of the snake
		ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
		static const float modifier_; // The proportion of the screen width a body square is
		ofRectangle body_; // the size of a snake body piece based on kbody_size_modifier_
		ofColor hero_color_;
		ofImage hero_image_;
		ofVec2f position_;
		int red_key_num_;
		int yellow_key_num_;
		int floor_key_num_;
		double attack_;
		double defense_;
		double max_health_;
		double current_health_;
		int coin_;
		double exp_;
		int level_;
	public:
		Player(); // Default constructor, initializes and places length 1 snake
		Player(const Player& other); // copy constructor
		void setPosition(float x, float y);
		ofColor getColor();
		ofImage getImage();
		ofRectangle getBody();
		void setSize(float size);
		void addKey(Key* key);
		//void buyWeapon();
		void attackMonster(Monster* monster);
		void takeGem(Gem* gem);
		void levelUp(double experience);
		bool useRedKey();
		bool useYellowKey();
		bool useFloorKey();
		bool isDead();
		double getAttack();
		double getDefense();
		double getMaxHealth();
		double getCurrentHealth();
		int getLevel();
		Direction getDirection() const; // Gets the Snake's current direction
		void setDirection(Direction new_direction); // Sets the Snake's direction
		void drawPlayer();
		int getRedKeyNum();
		int getYellowKeyNum();
		int getFloorKeyNum();
		int getCoin();
	
	};
}