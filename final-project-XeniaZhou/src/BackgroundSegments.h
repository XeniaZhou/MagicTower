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
		ofRectangle rec_;
	public:
		BackgroundSegments();
		BackgroundSegments(int element, int x, int y, int size);
		
		void addKey(Key k);
		void addGem(Gem g);
		void addMonster(Monster m);
		void setImage();
		ofRectangle getRectangle();
		void replaceElement();

		NPC* getNPC();
		Key* getKey();
		Gem* getGem();
		Monster* getMonster();
		BackgroundElement getElement();

		bool containKey();
		bool containGem();
		bool containMonster();
		bool containNPC();

		void drawBackgroundSegment();
		void removeMonster();
		void removeKey();
		void removeGem();
	};
}