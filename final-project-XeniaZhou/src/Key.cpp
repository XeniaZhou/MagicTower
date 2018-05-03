#include "Key.h"

using namespace tower;

Key::Key() {}

Key::Key(Keys k) {
	k_ = k;
	setImage();
}



Key::Key(Key& k) {
	k_ = k.k_;
	setImage();
}

void Key::setImage() {
	if (k_) {
		switch (k_) {
		case REDKEY:
			key_color_ = ofColor(255, 155, 125);
			key_image_.load("image/red-key.png");
			break;
		case YELLOWKEY:
			key_color_ = ofColor(255, 235, 90);
			key_image_.load("image/yellow-key.png");
			break;
		case FLOORKEY:
			key_color_ = ofColor(180, 180, 180);
			key_image_.load("image/floor-key.png");
			break;
		}
	}
}




ofImage Key::getImage() {
	return key_image_;
}


ofColor Key::getColor() {
	return key_color_;
}

Keys Key::getKeyType() {
	return k_;
}