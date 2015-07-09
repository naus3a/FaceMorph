//
//  NauPointDragger.h
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
#include "ofMain.h"

class NauPointDragger{
public:
    NauPointDragger();
    ~NauPointDragger();
    void setup(ofVec2f * _pt);
    void linkMesh(ofMesh * _msh, int _idx);
    void draw();
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mouseMoved(ofMouseEventArgs & args);
    
    void setActive(bool b);
    void resizeRect();
    void moveTo(float _nx, float ny);
    
    ofRectangle curR;
    ofVec2f * pt;
    ofMesh * msh;
    float sz;
    float curSz;
    int idx;
    bool bActive;
    bool bOver;
    bool bDragging;
};