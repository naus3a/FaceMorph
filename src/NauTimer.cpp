//
//  NauTimer.cpp
//
//  Created by enrico<naus3a>viola on 3/13/14.
//
//

#include "NauTimer.h"

NauTimer::NauTimer(){
    someoneListening=false;
    isSet = false;
    bStarted = false;
}

void NauTimer::setup(float _tick, int _rounds){
    tick=_tick;
    rounds=_rounds;
    isSet = true;
    bStarted=false;
    reset();
}

void NauTimer::reset(){
    bRunning=false;
    bStarted=false;
    curRound=0;
}

void NauTimer::start(){
    if(!bRunning){
        bRunning=true;
        bStarted=true;
        startTime = ofGetElapsedTimef();
        pct = 0;
        endTime = startTime + tick;
        cout << "Timer started" << endl;
    }
}

void NauTimer::stop(){
    if(bRunning){
        bRunning=false;
        cout << "Timer stopped" << endl;
    }
}

void NauTimer::setPaused(bool b){
    if(b){
        getPct();
        stop();
    }else{
        if(!bRunning){
            endTime = ofGetElapsedTimef() + ((1 - pct) * tick);
            bRunning = true;
        }
    }
}

void NauTimer::update(){
    if(bRunning){
        curTime = ofGetElapsedTimef();
        
        if(curTime>=endTime){
            curRound++;
            endTime = endTime + tick;
            onTick();
        }
        
        if(curRound>=rounds){
            stop();
        }
    }
}

void NauTimer::onTick(){
    ofNotifyEvent(tickEvent,curRound);
    cout << "Timer tick" << endl;
}

float NauTimer::getPct(){
    if(bRunning){
        pct = ofMap(ofGetElapsedTimef(), startTime, endTime, 0, 1);
    }
    return pct;
}

float NauTimer::getLastPct(){
    return pct;
}

float NauTimer::getCurTime(){
    return (bRunning?curTime:0);
}

float NauTimer::getLocalTime(){
    return (curTime-startTime);
}