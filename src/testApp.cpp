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


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(50);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetWindowTitle("FaceMorph");
	ofEnableSmoothing();
    
    ofAddListener(mainMenu.gui->newGUIEvent, this, &testApp::onMenuEvent);
    ofAddListener(faceMaker.gui->newGUIEvent, this, &testApp::onFaceEvent);
    ofAddListener(morphSetup.gui->newGUIEvent, this, &testApp::onMorphSetup);
    ofAddListener(mPlayer.gui->newGUIEvent, this, &testApp::onMorph);
    
    states.push_back(&mainMenu);
    states.push_back(&faceMaker);
    states.push_back(&morphSetup);
    states.push_back(&mPlayer);
    
    goState(STATE_MENU, false);
}

void testApp::goState(AppState as, bool bExit){
    
    if(bExit)states[int(curState)]->exit();
    curState = as;
    states[int(curState)]->enter();
    
}

//--------------------------------------------------------------
void testApp::update(){
    states[(int)curState]->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    states[(int)curState]->draw();
}

void testApp::onMenuEvent(ofxUIEventArgs &e){
    if(e.widget==mainMenu.butMakeFace){
        if(mainMenu.butMakeFace->getValue()){
            goState(STATE_FACE);
        }
    }else if(e.widget==mainMenu.butMorphSetup){
        if(mainMenu.butMorphSetup->getValue()){
            goState(STATE_MORPH_SET);
        }
    }else if(e.widget==mainMenu.butMorph){
        if(mainMenu.butMorph->getValue()){
            goState(STATE_MORPH);
        }
    }
}

void testApp::onFaceEvent(ofxUIEventArgs &e){
    if(e.widget==faceMaker.butBack){
        if(faceMaker.butBack->getValue()){
            goState(STATE_MENU);
        }
    }else if(e.widget==faceMaker.butLoadImg){
        if(faceMaker.butLoadImg->getValue()){
            faceMaker.loadImage();
        }
    }else if(e.widget==faceMaker.butFind){
        if(faceMaker.butFind->getValue()){
            faceMaker.findFace();
        }
    }else if(e.widget==faceMaker.butSave){
        if(faceMaker.butSave->getValue()){
            faceMaker.saveFace();
        }
    }else if(e.widget==faceMaker.butLoadFace){
        if(faceMaker.butLoadFace->getValue()){
            faceMaker.loadFace();
        }
    }
}

void testApp::onMorphSetup(ofxUIEventArgs & e){
    if(e.widget==morphSetup.butBack){
        if(morphSetup.butBack->getValue()){
            goState(STATE_MENU);
        }
    }else if(e.widget==morphSetup.butSrc){
        if(morphSetup.butSrc->getValue()){
            morphSetup.loadSrcFace();
        }
    }else if(e.widget==morphSetup.butDst){
        if(morphSetup.butDst->getValue()){
            morphSetup.loadDstFace();
        }
    }else if(e.widget==morphSetup.butSave){
        if(morphSetup.butSave->getValue()){
            morphSetup.save();
        }
    }else if(e.widget==morphSetup.butLoad){
        if(morphSetup.butLoad->getValue()){
            morphSetup.load();
        }
    }
}

void testApp::onMorph(ofxUIEventArgs &e){
    if(e.widget==mPlayer.butBack){
        if(mPlayer.butBack->getValue()){
            goState(STATE_MENU);
        }
    }else if(e.widget==mPlayer.butLoad){
        if(mPlayer.butLoad->getValue()){
            mPlayer.load();
        }
    }else if(e.widget==mPlayer.butStart){
        if(mPlayer.butStart->getValue()){
            mPlayer.start();
        }
    }else if(e.widget==mPlayer.butStop){
        if(mPlayer.butStop->getValue()){
            mPlayer.stop();
        }
    }else if(e.widget==mPlayer.butReset){
        if(mPlayer.butReset->getValue()){
            mPlayer.reset();
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
