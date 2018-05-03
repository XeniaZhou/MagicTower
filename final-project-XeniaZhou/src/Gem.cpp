#include "Gem.h"

using namespace tower;

Gem::Gem() {}

Gem::Gem(Gems k) {
	g_ = k;
	setImage();
}

Gem::Gem(Gem& k) {
	g_ = k.g_;
	setImage();
}

void Gem::setImage() {
	if (g_) {
		switch (g_) {
		case REDGEM:
			gem_color_ = ofColor(255, 155, 125);
			gem_image_.load("image/red-gem.png");
			break;
		case BLUEGEM:
			gem_color_ = ofColor(125, 215, 225);
			gem_image_.load("image/blue-gem.png");
			break;
		}
	}
}

ofImage Gem::getImage() {
	return gem_image_;
}


ofColor Gem::getColor() {
	return gem_color_;
}




Gems Gem::getGemType() {
	return g_;
}