#pragma once
#include "ofMain.h"

namespace tower {
	typedef enum {
		EMPTYGEM = 0,
		BLUEGEM,
		REDGEM
	} Gems;

	class Gem {
	private:
		Gems g_;
		ofImage gem_image_;
		ofColor gem_color_;
	public:
		Gem();
		Gem(Gems k);
		Gem(Gem& k);
		void setImage();
		ofImage getImage();
		ofColor getColor();
		Gems getGemType();
	};
}