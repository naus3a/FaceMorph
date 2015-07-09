//
//  MorphPlayer.h
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
#include "Morph.h"
#include "Clone.h"
#include "NauTimer.h"

class MorphPlayer : public IState{
public:
    struct TestArgs{
        inline TestArgs(){set(0,0);}
        inline TestArgs(float _stopPct, float _stopTime){set(_stopPct, _stopTime);}
        inline void set(float _stopPct, float _stopTime){stopPct=_stopPct; stopTime=_stopTime;getCurTime();}
        inline void getCurTime(){curTime=ofToString(ofGetHours())+":"+ofToString(ofGetMinutes())+":"+ofToString(ofGetSeconds());}
        string curTime;
        float stopTime;
        float stopPct;
    };
    
    MorphPlayer();
    void enter() override;
    void exit() override;
    void update() override;
    void draw() override;
    
    void load();
    void makeReportName();
    void saveReport(TestArgs ta);
    void updateClone(float str);
    
    void start();
    void stop();
    void reset();
    
    void onNaturalStop(int & tick);
    void onKeyPressed(ofKeyEventArgs & e);
    
    NauTimer timer;
    Morph morph;
    Clone clone;
    ofFbo fboSrc;
    ofFbo fboMsk;
    
    ofxUILabelButton * butBack;
    ofxUILabelButton * butLoad;
    ofxUILabelButton * butStart;
    ofxUILabelButton * butStop;
    ofxUILabelButton * butReset;
    ofxUILabel * labStatus;
    
    string reportName;
    const int minStr;
    const int maxStr;
};