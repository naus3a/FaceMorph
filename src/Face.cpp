//
//  Face.cpp
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

#include "Face.h"

Face::Face(){
    clear();
}

void Face::clear(){
    hasImg = false;
    hasMsh = false;
    img.clear();
    msh.clear();
    tmpPth = "";
}

bool Face::loadImage(){
    bool b = false;
    ofFileDialogResult dr = ofSystemLoadDialog("img/","Load Image");
    if(dr.bSuccess){
        b = loadImage(dr.getPath());
    }
    return b;
}

bool Face::loadImage(string pth){
    bool b  = false;
    if(ofFile::doesFileExist(pth)){
        clear();
        if(img.loadImage(pth)){
            hasImg = true;
            tmpPth = pth;
            b = true;
        }
    }
    return b;
}

bool Face::load(){
    bool b = false;
    ofFileDialogResult dr = ofSystemLoadDialog("faces/","Load Face");
    if(dr.bSuccess){
        b = load(dr.getPath());
        tmpPth = dr.getPath();
    }
    return b;
}

bool Face::load(string pth){
    bool b = false;
    if(ofFile::doesFileExist(pth)){
        ofxXmlSettings xml;
        if(xml.load(pth)){
            b = true;
            tmpPth = pth;
            clear();
            vector<ofVec2f> vv;
            vector<int> ii;
            if(xml.tagExists("face")){
                xml.pushTag("face");
                if(xml.tagExists("vtx")){
                    xml.pushTag("vtx");
                    int n = xml.getNumTags("v");
                    for(int i=0;i<n;i++){
                        ofVec2f v;
                        v.x = xml.getAttribute("v", "x", 0.0, i);
                        v.y = xml.getAttribute("v", "y", 0.0, i);
                        vv.push_back(v);
                    }
                    xml.popTag();
                }
                if(xml.tagExists("idx")){
                    xml.pushTag("idx");
                    int n = xml.getNumTags("i");
                    for (int i=0; i<n; i++) {
                        int idx = xml.getValue("i", 0, i);
                        ii.push_back(idx);
                    }
                    xml.popTag();
                }
                
                ofxBase64 b64;
                ofPixels pix = b64.loadPixelsFromXml(&xml);
                img.setFromPixels(pix);
                if(img.getWidth()>0)hasImg=true;
                xml.popTag();
            }
            
            if(vv.size()>0){
                msh.clear();
                msh.setMode(OF_PRIMITIVE_TRIANGLES);
                for(int i=0;i<vv.size();i++){
                    msh.addVertex(vv[i]);
                    msh.addTexCoord(vv[i]);
                }
                for(int i=0;i<ii.size();i++){
                    msh.addIndex(ii[i]);
                }
                hasMsh = true;
            }
        }
    }
    return b;
}

void Face::save(){
    if(hasImg && hasMsh){
        string pth;
        if(tmpPth!=""){
            pth = ofFilePath::getBaseName(tmpPth)+".face";
        }else{
            pth = "new_face.face";
        }
        ofFileDialogResult dr = ofSystemSaveDialog(pth, "Save Face");
        if(dr.bSuccess){
            save(dr.getPath());
        }
    }
}

void Face::save(string pth){
    ofxXmlSettings xml;
    xml.addTag("face");
    xml.pushTag("face");
    
    xml.addTag("vtx");
    xml.pushTag("vtx");
    for(int i=0;i<msh.getNumVertices();i++){
        ofVec2f v = msh.getVertex(i);
        xml.addTag("v");
        xml.setAttribute("v", "x", v.x, i);
        xml.setAttribute("v", "y", v.y, i);
    }
    xml.popTag();
    
    xml.addTag("idx");
    xml.pushTag("idx");
    for(int i=0;i<msh.getNumIndices();i++){
        xml.addTag("i");
        xml.setValue("i", int(msh.getIndex(i)), i);
    }
    xml.popTag();
    
    ofxBase64 b64;
    b64.savePixelsToXml(&xml, &img.getPixelsRef());
    
    xml.popTag();
    
    xml.save(pth);
}


void Face::setMesh(ofMesh _msh){
    hasMsh = true;
    msh = _msh;
}