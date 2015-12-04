//
//  Morph.cpp
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

#include "Morph.h"

Morph::Morph(){
    clear();
}

void Morph::clear(){
    pthSrc="";
    pthDst="";
    fileName="";
    faceSrc.clear();
    faceDst.clear();
    srcPts.clear();
    time = 1.0;
	str = 25;
}

bool Morph::loadSrcImg(){
    bool b = false;
    b = faceSrc.load();
    pthSrc = faceSrc.tmpPth;
    return b;
}

bool Morph::loadDstImg(){
    bool b = false;
    b = faceDst.load();
    pthDst = faceDst.tmpPth;
    srcPts.clear();
    for(int i=0;i<faceDst.msh.getNumVertices();i++){
        srcPts.push_back(faceDst.msh.getVertex(i));
    }
    return b;
}

void Morph::save(){
    if(isReady()){
        ofFileDialogResult dr = ofSystemSaveDialog("new_morph.mph", "Save Morph");
        if(dr.bSuccess){
            save(dr.getPath());
        }
    }
}

void Morph::save(string pth){
    ofxXmlSettings xml;
    xml.addTag("morph");
    xml.pushTag("morph");
    
    xml.addTag("src");
    xml.setValue("src", pthSrc);
    
    xml.addTag("dst");
    xml.setValue("dst", pthDst);
    
    xml.addTag("time");
    xml.setValue("time", time);

	xml.addTag("strength");
    xml.setValue("strength",str);

    xml.popTag();
    
    xml.save(pth);
}

void Morph::load(){
#ifdef TARGET_WIN32
    ofFileDialogResult dr = ofSystemLoadDialog("Load Morph");
#else
	ofFileDialogResult dr = ofSystemLoadDialog("morphs/", "Load Morph");
#endif
    if(dr.bSuccess){
        load(dr.getPath());
    }
}

void Morph::load(string pth){
    if(ofFile::doesFileExist(pth)){
        ofxXmlSettings xml;
        if(xml.load(pth)){
            clear();
            fileName=pth;
            if(xml.tagExists("morph")){
                xml.pushTag("morph");
                pthSrc = xml.getValue("src", "");
                pthDst = xml.getValue("dst", "");
                time = xml.getValue("time", 1.0);
				str = xml.getValue("strength",25);
                xml.popTag();
                faceSrc.load(pthSrc);
                faceDst.load(pthDst);
            }
        }
    }
}