#include "ofMain.h"
#include "ofApp.h"

using namespace tower;

//=================================================================
//ALMOST ALL DOC ABOUT METHODS' PURPOSES ARE IN EACH .h FILES
//==================================================================

//========================================================================
int main( ){
	ofSetupOpenGL(1080,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
