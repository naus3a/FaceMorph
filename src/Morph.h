//
//  Morph.h
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
#include "Face.h"

class Morph{
public:
    Morph();
    void clear();
    inline bool isReady(){return faceSrc.isReady() && faceDst.isReady();}
    bool loadSrcImg();
    bool loadDstImg();
    void load();
    void load(string pth);
    void save();
    void save(string pth);
    
    Face faceSrc;
    Face faceDst;
    string pthSrc;
    string pthDst;
    float time;
    vector<ofVec2f> srcPts;
	int str;
};