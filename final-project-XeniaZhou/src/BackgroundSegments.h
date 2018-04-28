#pragma once
#include "ofMain.h"
#include "Key.h"
#include "Gem.h"
#include "Monster.h"

namespace maps {
	typedef enum {
		WALL = 0,
		FLOOR,
		REDDOOR,
		YELLOWDOOR,
		FLOORDOOR
	} BackgroundElement;



	class BackgroundSegments {
	private:
		Gem* gem_;
		Key* key_;
		Monster* monster_;
		ofVec2f position_;
		BackgroundElement element_;
		ofColor color_;
		ofRectangle rec_;
	public:
		BackgroundSegments();
		BackgroundSegments(int element, int x, int y, int size);
		void addKey(Key k);
		void addGem(Gem g);
		void addMonster(Monster m);
		void setColor();
		ofRectangle getRectangle();
		void replaceElement();
		Key* getKey();
		Gem* getGem();
		Monster* getMonster();
		BackgroundElement getElement();
		bool containKey();
		bool containGem();
		bool containMonster();
		void drawBackgroundSegment();
		void removeMonster();
		void removeKey();
		void removeGem();
	};
}