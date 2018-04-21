#include "Key.h"

using namespace maps;

Key::Key() {}

Key::Key(Keys k) {
	k_ = k;
	setColor();
}



Key::Key(Key& k) {
	k_ = k.k_;
	key_color_ = ofColor(k.key_color_);
}

void Key::setColor() {
	if (k_) {
		switch (k_) {
		case REDKEY:
			key_color_ = ofColor(160, 45, 10);
			break;
		case YELLOWKEY:
			key_color_ = ofColor(225, 180, 60);
			break;
		case FLOORKEY:
			key_color_ = ofColor(100, 100, 100);
			break;
		}
	}
}




ofColor Key::getColor() {
	return key_color_;
}




Keys Key::getKeyType() {
	return k_;
}