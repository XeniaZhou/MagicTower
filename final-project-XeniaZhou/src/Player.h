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
		Direction current_direction_;			// The current direction of the player
		ofVec2f screen_dims_;					// The current screen dimensions 
		static const float modifier_;			// The proportion of the screen width a body square is, it is conpare with the background dimension
		ofRectangle body_;						// the rec represent the body of hero
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
		Player(); 
		Player(const Player& other); // copy constructor

		void setPosition(float x, float y);
		void setSize(float size);
		void setDirection(Direction new_direction); // Sets the direction

		double getAttack();
		double getDefense();
		double getMaxHealth();
		double getCurrentHealth();
		int getLevel();
		ofColor getColor();
		ofImage getImage();
		ofRectangle getBody();
		Direction getDirection() const; // Gets the current direction
		int getRedKeyNum();
		int getYellowKeyNum();
		int getFloorKeyNum();
		int getCoin();//getter


		void addKey(Key* key);
		void attackMonster(Monster* monster);
		void takeGem(Gem* gem);//interact methods

		void levelUp(double experience);

		bool useRedKey();
		bool useYellowKey();
		bool useFloorKey();      //this three use-- methods do use keys when we have then and return true, else do nothing and return false

		bool isDead();
		
		 
		void drawPlayer();
		
	
	};
}