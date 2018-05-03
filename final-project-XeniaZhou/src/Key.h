#pragma once
#include "ofMain.h"

namespace tower {
	typedef enum {
		EMPTYKEY = 0,
		REDKEY,
		YELLOWKEY,
		FLOORKEY
	} Keys;

	class Key {
	private:
		Keys k_;
		ofColor key_color_;
		ofImage key_image_;
	public:
		Key();
		Key(Keys k);
		Key(Key& k);
		void setImage();
		ofColor getColor();
		ofImage getImage();
		Keys getKeyType();
	};
}
