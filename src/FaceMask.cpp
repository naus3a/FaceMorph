//
//  FaceMask.cpp
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

#include "FaceMask.h"

char mskShdSrc[] =
"#extension GL_ARB_texture_rectangle : enable\n"
"uniform sampler2DRect tex;\
void main(){\
vec2 tc = gl_TexCoord[0].st;\
vec4 texel = texture2DRect(tex, tc);\
if(texel.r>0.0){\
	gl_FragColor = vec4(0.0,0.0,0.0,0.0);\
}else{\
	gl_FragColor = vec4(0.0,0.0,0.0,1.0);\
}\
}";

FaceMask::FaceMask(){
	faceMesh = NULL;
	bReady = false;
	shdMsk.setupShaderFromSource(GL_FRAGMENT_SHADER, mskShdSrc);
	shdMsk.linkProgram();
	ofSetCircleResolution(100);
}

FaceMask::~FaceMask(){
	faceMesh = NULL;
}

void FaceMask::linkMesh(ofMesh * _msh, float w, float h){
	faceMesh = _msh;
	if(faceMesh->getNumVertices()>50){
		ofVec3f ctr3 = faceMesh->getVertex(29);
		ofVec3f lx = faceMesh->getVertex(2);
		ofVec3f bt = faceMesh->getVertex(8);
		ctr.set(ctr3.x, ctr3.y);
		radia.x = ctr3.distance(lx)*2;
		radia.y = ctr3.distance(bt)*2;

		ofFbo fboTmp;
		fboMask.allocate(w, h, GL_RGBA);
		fboTmp.allocate(w, h, GL_RGBA);
		
		fboTmp.begin();
		ofClear(0,0,0,0);
		ofEllipse(ctr.x, ctr.y, radia.x, radia.y);
		fboTmp.end();

		fboMask.begin();
		ofClear(0,0,0,0);
		shdMsk.begin();
		fboTmp.draw(0,0);
		shdMsk.end();
		fboMask.end();

		bReady = true;
	}else{
		bReady = false;
	}
}

void FaceMask::draw(){
	if(isReady()){
		fboMask.draw(0,0);
	}
}