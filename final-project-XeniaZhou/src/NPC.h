#pragma once
#include "ofMain.h"
#include <string>
#include <vector>

namespace tower {
	typedef enum {
		NAMELESS = 0,
		RITA,
		NATASHA

	} Npcs;
	class NPC {
		Npcs name_;
	
		ofImage image_;
	
		
	public:
		NPC(Npcs name);
		
		ofImage getImage();
		Npcs getName();
	};
}