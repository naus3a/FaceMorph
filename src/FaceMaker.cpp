//
//  FaceMaker.cpp
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

#include "FaceMaker.h"

FaceMaker::FaceMaker(){
    tracker.setup();
    tracker.setIterations(25);
    tracker.setAttempts(4);
    float ww = 200;
    gui = new ofxUICanvas(ofGetWidth()-ww,0,ww,ofGetHeight());
    gui->addWidgetDown(new ofxUILabel("Face Maker", OFX_UI_FONT_LARGE));
    butLoadImg =  new ofxUILabelButton("Load Image",false);
    gui->addWidgetDown(butLoadImg);
    butLoadFace = new ofxUILabelButton("Load Face", false);
    gui->addWidgetDown(butLoadFace);
    butFind = new ofxUILabelButton("Find Face",false);
    gui->addWidgetDown(butFind);
    butSave = new ofxUILabelButton("Save Face",false);
    gui->addWidgetDown(butSave);
    butBack = new ofxUILabelButton("Main Menu", false);
    gui->addWidgetDown(butBack);
    gui->setVisible(false);
}

void FaceMaker::enter(){
    ofSetWindowShape(1024, 768);
    gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
    gui->setHeight(ofGetHeight());
    gui->setVisible(true);
    face.clear();
    draggers.clear();
    srcPts.clear();
}

void FaceMaker::update(){}

void FaceMaker::draw(){
    if(face.hasImg){
        ofPushStyle();
        ofSetColor(ofColor::white);
        face.img.draw(0,0);
        if(face.hasMsh){
            face.msh.drawWireframe();
            ofSetColor(ofColor::red);
            ofSetLineWidth(2);
            for(int i=0;i<draggers.size();i++){
                draggers[i].draw();
            }
        }
        ofPopStyle();
    }
}


void FaceMaker::loadImage(){
    if(face.loadImage()){
        ofSetWindowShape(face.img.getWidth()+gui->getRect()->width, face.img.getHeight()>ofGetHeight()?face.img.getHeight():ofGetHeight());
        gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
    }
}

void FaceMaker::loadFace(){
    if(face.load()){
        ofSetWindowShape(face.img.getWidth()+gui->getRect()->width, face.img.getHeight()>ofGetHeight()?face.img.getHeight():ofGetHeight());
        gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
        draggers.clear();
        srcPts.clear();
        if(face.hasMsh){
            for(int i=0;i<face.msh.getNumVertices();i++){
                srcPts.push_back(face.msh.getVertex(i));
            }
            draggers.resize(srcPts.size());
            for(int i=0;i<srcPts.size();i++){
                draggers[i].setup(&srcPts[i]);
                draggers[i].linkMesh(&face.msh, i);
            }
        }
    }
}

void FaceMaker::findFace(){
    if(face.hasImg){
        tracker.update(ofxCv::toCv(face.img));
        draggers.clear();
        srcPts.clear();
        srcPts = tracker.getImagePoints();
        if(srcPts.size()>0){
            face.setMesh(tracker.getImageMesh());
        }else{
            face.setMesh(makeDefaultMesh());
        }
        draggers.resize(srcPts.size());
        for(int i=0;i<srcPts.size();i++){
            draggers[i].setup(&srcPts[i]);
            draggers[i].linkMesh(&face.msh, i);
        }
    }
}

void FaceMaker::saveFace(){
    face.save();
}

ofMesh FaceMaker::makeDefaultMesh(){
    ofMesh msh;
    string vertexFile = "mesh/mesh.vtx";
    string texCoordFile = "mesh/mesh.tcx";
    string indexFile = "mesh/mesh.idx";
    
    msh.setMode(OF_PRIMITIVE_TRIANGLES);
	ofBuffer bV = ofBufferFromFile(vertexFile);
	ofBuffer bT = ofBufferFromFile(texCoordFile);
	ofBuffer bI = ofBufferFromFile(indexFile);
	int sz;
	sz = ofToInt(bV.getNextLine());
	while(!bV.isLastLine()){
		string riga = bV.getNextLine();
		vector<string> split = ofSplitString(riga, ",", true, true);
		ofVec3f v = ofVec3f(ofToFloat(split[0]),ofToFloat(split[1]),ofToFloat(split[2]));
		msh.addVertex(v);
	}
	sz = ofToInt(bT.getNextLine());
	while(!bT.isLastLine()){
		string riga = bT.getNextLine();
		vector<string> split = ofSplitString(riga, ",", true, true);
		ofVec2f t = ofVec2f(ofToFloat(split[0]),ofToFloat(split[1]));
		msh.addTexCoord(t);
	}
	sz = ofToInt(bI.getNextLine());
	while(!bI.isLastLine()){
		string riga = bI.getNextLine();
		msh.addIndex(ofToInt(riga));
	}
	bV.clear();
	bT.clear();
	bI.clear();
	return msh;
}