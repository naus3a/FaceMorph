//
//  NauPointDragger.cpp
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

#include "NauPointDragger.h"

NauPointDragger::NauPointDragger(){
    pt = NULL;
    msh = NULL;
    idx = 0;
    sz = 10;
    curSz = sz;
    bActive = false;
    bOver = false;
    bDragging = false;
    curR.set(0,0,curSz,curSz);
}

NauPointDragger::~NauPointDragger(){
    if(bActive){
        setActive(false);
    }
    pt = NULL;
    msh = NULL;
}

void NauPointDragger::setup(ofVec2f *_pt){
    pt = _pt;
    resizeRect();
    setActive(true);
}

void NauPointDragger::linkMesh(ofMesh *_msh, int _idx){
    msh=_msh;
    idx=_idx;
}

void NauPointDragger::setActive(bool b){
    bOver = false;
    bDragging = false;
    bActive = b;
    if(b){
        ofRegisterMouseEvents(this);
    }else{
        ofUnregisterMouseEvents(this);
    }
}

void NauPointDragger::resizeRect(){
    //curSz = bOver?sz*2:sz;
    curR.set(pt->x-(curSz/2), pt->y-(curSz/2), curSz, curSz);
}

void NauPointDragger::moveTo(float nx, float ny){
    pt->x = nx;
    pt->y = ny;
    resizeRect();
    if(msh!=NULL){
        msh->setVertex(idx, ofVec2f(pt->x,pt->y));
    }
}

void NauPointDragger::draw(){
    if(bOver || bDragging){
        //ofRect(curR);
        ofLine(curR.x+curR.width/2,curR.y,curR.x+curR.width/2,curR.y+curR.height);
        ofLine(curR.x, curR.y+curR.height/2, curR.x+curR.width, curR.y+curR.height/2);
    }
}

void NauPointDragger::mousePressed(ofMouseEventArgs &args){
    if(curR.inside(args.x, args.y)){
        bDragging=true;
    }
}

void NauPointDragger::mouseReleased(ofMouseEventArgs &args){
    bDragging=false;
}

void NauPointDragger::mouseDragged(ofMouseEventArgs &args){
    if(bDragging){
        moveTo(args.x, args.y);
    }
}

void NauPointDragger::mouseMoved(ofMouseEventArgs &args){
    if(curR.inside(args.x, args.y)){
     //if(!bOver){
     //resizeRect();
     //}
     bOver = true;
    }else{
     //if(bOver){
     //resizeRect();
     //}
     bOver = false;
    }
}