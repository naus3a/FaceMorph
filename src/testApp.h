// author Enrico <naus3a> Viola 2015
// This file is part of FaceMorph.
//
//FaceMorph is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//FaceMorph is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with FaceMorph.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "IState.h"
#include "MainMenu.h"
#include "FaceMaker.h"
#include "MorphSetup.h"
#include "MorphPlayer.h"

class testApp : public ofBaseApp{

	public:
        enum AppState{
            STATE_MENU,
            STATE_FACE,
            STATE_MORPH_SET,
            STATE_MORPH
        };
    
		void setup();
		void update();
		void draw();
    
    void goState(AppState as, bool bExit=true);
    void onMenuEvent(ofxUIEventArgs & e);
    void onFaceEvent(ofxUIEventArgs & e);
    void onMorphSetup(ofxUIEventArgs & e);
    void onMorph(ofxUIEventArgs & e);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    MainMenu mainMenu;
    FaceMaker faceMaker;
    MorphSetup morphSetup;
    MorphPlayer mPlayer;
    vector<IState *> states;
    AppState curState;
};
