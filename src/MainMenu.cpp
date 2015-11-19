//
//  MainMenu.cpp
//  FaceMorph
//
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

#include "MainMenu.h"

MainMenu::MainMenu(){
    float ww = 200;
    gui = new ofxUICanvas(ofGetWidth()/2-ww/2,0,ww,ofGetHeight());
    gui->addWidgetDown(new ofxUILabel("FaceMorph 0.1", OFX_UI_FONT_LARGE));
    butMakeFace = new ofxUILabelButton("Make a Face", false);
    butMorphSetup = new ofxUILabelButton("Setup Morph", false);
    butMorph = new ofxUILabelButton("Morph", false);
    gui->addWidgetDown(butMakeFace);
    gui->addWidgetDown(butMorphSetup);
    gui->addWidgetDown(butMorph);
    gui->setVisible(false);
}

void MainMenu::enter(){
    ofSetWindowShape(1024, 768);
    gui->setPosition(ofGetWidth()/2-gui->getRect()->width/2, 0);
    gui->setHeight(ofGetHeight());
    gui->setVisible(true);
}
