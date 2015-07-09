//
//  NauTimer.h
//
//  Created by enrico<naus3a>viola on 3/13/14.
//
//

#pragma once
#include "ofMain.h"

class NauTimer{
public:
    NauTimer();
    virtual void setup(float _tick, int _rounds=0);
    virtual void reset();
    virtual void start();
    virtual void stop();
    virtual void setPaused(bool b);
    virtual void update();
    virtual void onTick();
    
    virtual float getPct();
    virtual float getLastPct();
    virtual float getCurTime();
    virtual float getLocalTime();
    
    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method){
        ofAddListener(tickEvent, listener, method);
        someoneListening=true;
    }
    
    template<class ListenerClass, typename ListenerMethod>
    void removeListener(ListenerClass * listener, ListenerMethod method){
        ofRemoveListener(tickEvent, listener, method);
        someoneListening=false;
    }
    
    ofEvent<int>tickEvent;
    float curTime;
    float tick;
    float startTime;
    float endTime;
    int rounds;
    int curRound;
    bool bRunning;
    bool isSet;
    bool someoneListening;
    bool bStarted;
    
    float pct;
};