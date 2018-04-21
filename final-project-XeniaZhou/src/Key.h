#pragma once
#include "ofMain.h"

namespace maps {
	typedef enum {
		REDKEY = 0,
		YELLOWKEY,
		FLOORKEY
	} Keys;

	class Key {
	private:
		Keys k_;
		ofColor key_color_;
	public:
		Key();
		Key(Keys k);
		Key(Key& k);
		void setColor();
		ofColor getColor();
	
		Keys getKeyType();
	};
}
