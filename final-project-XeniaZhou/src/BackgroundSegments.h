#pragma once
#include "ofMain.h"
#include "Key.h"
#include "Gem.h"
#include "Monster.h"
#include "NPC.h"

namespace tower {
	typedef enum {
		WALL = 0,
		FLOOR,
		REDDOOR,
		YELLOWDOOR,
		FLOORDOOR
	} BackgroundElement;



	class BackgroundSegments {
	private:
		NPC * npc_;
		Gem* gem_;
		Key* key_;
		Monster* monster_;
		ofVec2f position_;
		BackgroundElement element_;
		ofColor segment_color_;
		ofImage segment_image_;
		ofRectangle rec_;												//these are all pointers and containers of data
	public:
		BackgroundSegments();
		BackgroundSegments(int element, int x, int y, int size);		//constructor
		
		void addKey(Key k);
		void addGem(Gem g);
		void addMonster(Monster m);
		void setImage();
		void replaceElement();											//data change method

		ofRectangle getRectangle();
		NPC* getNPC();
		Key* getKey();
		Gem* getGem();
		Monster* getMonster();
		BackgroundElement getElement();									//getter

		bool containKey();
		bool containGem();
		bool containMonster();
		bool containNPC();												//used when we need to detect whether we have items to pick, monster to fight or NPC to talk

		void drawBackgroundSegment();									//draw each segment

		void removeMonster();
		void removeKey();
		void removeGem();												//delete and set to nullptr
	};
}