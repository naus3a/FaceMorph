//
//  MorphSetup.cpp
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

#include "MorphSetup.h"

MorphSetup::MorphSetup(){
    scPv.set(1,1);
    float ww = 200;
    gui = new ofxUICanvas(ofGetWidth()-ww,0,ww,ofGetHeight());
    gui->addWidgetDown(new ofxUILabel("Morph Setup", OFX_UI_FONT_LARGE));
    butSrc = new ofxUILabelButton("Source Face", false);
    butDst = new ofxUILabelButton("Final Face", false);
    gui->addWidgetDown(butSrc);
    gui->addWidgetDown(butDst);
    nuTime = new ofxUINumberDialer(0.5, 60.0, &morph.time, 2, "seconds", OFX_UI_FONT_MEDIUM);
    gui->addWidgetDown(nuTime);
    butSave = new ofxUILabelButton("Save",false);
    gui->addWidgetDown(butSave);
    butLoad = new ofxUILabelButton("Load", false);
    gui->addWidgetDown(butLoad);
    butBack = new ofxUILabelButton("Main Menu", false);
    gui->addWidgetDown(butBack);
    gui->setVisible(false);
}

void MorphSetup::enter(){
    ofSetWindowShape(1024, 768);
    gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
    gui->setHeight(ofGetHeight());
    gui->setVisible(true);
}

void MorphSetup::update(){
    
}

void MorphSetup::draw(){
    ofPushMatrix();
    ofTranslate(0, 0);
    if(morph.faceSrc.isReady()){
        ofPushMatrix();
        ofScale(scPv.x, scPv.x);
        morph.faceSrc.img.draw(0, 0);
        morph.faceSrc.msh.drawWireframe();
        ofPopMatrix();
    }
    ofTranslate(400, 0);
    if(morph.faceDst.isReady()){
        ofPushMatrix();
        ofScale(scPv.y, scPv.y);
        morph.faceDst.img.draw(0,0);
        morph.faceDst.msh.drawWireframe();
        ofPopMatrix();
    }
    ofPopMatrix();
}

void MorphSetup::loadSrcFace(){
    if(morph.loadSrcImg()){
        scPv.x = 400/morph.faceSrc.img.getWidth();
    }
}

void MorphSetup::loadDstFace(){
    if(morph.loadDstImg()){
        scPv.y = 400/morph.faceDst.img.getWidth();
    }
}

void MorphSetup::save(){
    morph.save();
}

void MorphSetup::load(){
    morph.load();
    if(morph.faceDst.isReady()){
        scPv.x = 400/morph.faceSrc.img.getWidth();
    }
    if(morph.faceDst.isReady()){
        scPv.y = 400/morph.faceDst.img.getWidth();
    }
}

