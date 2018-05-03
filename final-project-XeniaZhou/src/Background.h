#pragma once
#include "ofMain.h"
#include "BackgroundSegments.h"
#include <vector>

namespace tower {
	class Background {
	private:							
		ofVec2f screen_dims_;							// The current screen dimensions (needed to calculate values on resize(). Though this game does not support resize
														
		ofVec2f background_position_;					//locate the position of background, the rectangle contains maps, so that all segments are easier to locate their spots
		ofRectangle background_;                        //the vague rectangle of the background. its height and width are frequently used to measure the layout
		std::vector<BackgroundSegments> floor_map_;     //contain all segments in one floor
		static const float size_modifier_;				// The proportion of the screen width a body square is. Mainly used for the segments
	public:
		Background();
		void createMap(std::vector<int> maps);			//create a map through a int vector, like I dveid in Naive Bayes when loading the image from .txt file
		void update();									//redraw the map to update image of elements
		std::vector<BackgroundSegments> getFloorMap();  
		ofVec2f getPosition();
		ofRectangle getRec();
		BackgroundSegments &findIntersectPart(ofRectangle player);//thie method return a address of segments that intersect with the param rectangle. 
																  //It is one of the most important implements. It works when the game need to check whether the player can move in 
																  //his direction. When the intersect segments are WALL or DOOR without keys or contain monsters player do not want to duel 
																  //or NPC, then by using this implement, we can decide the movement. 
	};
}