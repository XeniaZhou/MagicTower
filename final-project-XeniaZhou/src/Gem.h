#pragma once
#include "ofMain.h"

namespace maps {
	typedef enum {
		BLUEGEM = 0,
		REDGEM
	} Gems;

	class Gem {
	private:
		Gems g_;
		ofColor gem_color_;
	public:
		Gem();
		Gem(Gems k);
		Gem(Gem& k);
		void setColor();
		ofColor getColor();
		Gems getGemType();
	};
}