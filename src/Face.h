//
//  Face.h
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
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxBase64.h"

class Face{
public:
    Face();
    void clear();
    bool loadImage();
    bool loadImage(string pth);
    bool load();
    bool load(string pth);
    void save();
    void save(string pth);
    void setMesh(ofMesh _msh);
    inline bool isReady(){return hasImg && hasMsh;}
    ofImage img;
    ofMesh msh;
    string tmpPth;
    bool hasImg;
    bool hasMsh;
};