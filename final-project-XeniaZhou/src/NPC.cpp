#include "NPC.h"

using namespace tower;


NPC::NPC(Npcs name) {
	name_ = name;
	switch (name_) {
	case RITA:
		image_.load("image/fake-princess.png");
		break;
	case NATASHA:
		image_.load("image/true-princess.png");
		break;
	}
	
}





ofImage NPC::getImage() {
	return image_;
}

Npcs NPC::getName() {
	return name_;
}