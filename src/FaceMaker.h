//
//  FaceMaker.h
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

#pragma once
#include "IState.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "NauPointDragger.h"

class FaceMaker : public IState{
public:
    FaceMaker();
    void enter() override;
    void update() override;
    void draw() override;
    
    void loadImage();
    void loadFace();
    void findFace();
    void saveFace();
    ofMesh makeDefaultMesh();
    
    Face face;
    ofxFaceTracker tracker;
    vector<ofVec2f> srcPts;
    vector<NauPointDragger> draggers;
    ofxUILabelButton * butLoadImg;
    ofxUILabelButton * butLoadFace;
    ofxUILabelButton * butFind;
    ofxUILabelButton * butBack;
    ofxUILabelButton * butSave;
};