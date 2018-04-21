#include "Gem.h"

using namespace maps;

Gem::Gem() {}

Gem::Gem(Gems k) {
	g_ = k;
	setColor();
}

Gem::Gem(Gem& k) {
	g_ = k.g_;
	gem_color_ = ofColor(k.gem_color_);
}

void Gem::setColor() {
	if (g_) {
		switch (g_) {
		case REDGEM:
			gem_color_ = ofColor(140, 45, 10);
			break;
		case BLUEGEM:
			gem_color_ = ofColor(105, 195, 205);
			break;
		}
	}
}




ofColor Gem::getColor() {
	return gem_color_;
}




Gems Gem::getGemType() {
	return g_;
}