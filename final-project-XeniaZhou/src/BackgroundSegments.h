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
		BackgroundSegments(BackgroundElement e, int x, int y, int size);
		void addKey(Key k);
		void addGem(Gem g);
		void addMonster(Monster m);
		void setColor();
		ofRectangle getRectangle();
		void replaceElement(BackgroundElement e);
		Keys getKey();
		void drawBackgroundSegment();
	};
}