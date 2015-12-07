//
//  MorphPlayer.cpp
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

#include "MorphPlayer.h"

MorphPlayer::MorphPlayer() : minStr(0), maxStr(25){
    timer.addListener(this, &MorphPlayer::onNaturalStop);
    float ww = 200;
	bMask = true;
    //recorder.setup();
    gui = new ofxUICanvas(ofGetWidth()-ww,0,ww,ofGetHeight());
    gui->addWidgetDown(new ofxUILabel("Morph", OFX_UI_FONT_LARGE));
    butLoad = new ofxUILabelButton("Load",false);
    gui->addWidgetDown(butLoad);
	togMask = new ofxUILabelToggle("Use Mask", &bMask);
	gui->addWidgetDown(togMask);
    gui->addSpacer();
    butReset = new ofxUILabelButton("Reset", false);
    gui->addWidgetDown(butReset);
    butStart = new ofxUILabelButton("Start", false);
    gui->addWidgetDown(butStart);
    butStop =  new ofxUILabelButton("Stop", false);
    gui->addWidgetDown(butStop);
    butVideo = new ofxUILabelButton("Record Video", false);
    gui->addWidgetDown(butVideo);
    gui->addWidgetDown(new ofxUILabel("[space bar] to stop", OFX_UI_FONT_SMALL));
    gui->addSpacer();
    gui->addWidgetDown(new ofxUILabel("Status:", OFX_UI_FONT_MEDIUM));
    labStatus = new ofxUILabel("IDLE", OFX_UI_FONT_MEDIUM);
    gui->addWidgetDown(labStatus);
    gui->addSpacer();
    butBack = new ofxUILabelButton("Main Menu", false);
    gui->addWidgetDown(butBack);
    gui->setVisible(false);

#ifdef TARGET_WIN32
	recorder.setFfmpegLocation("C:\\ffmpeg\\bin\\ffmpeg");
	recorder.setMovFileExtension(".avi");
	bRec = false;
#endif
}

#ifndef TARGET_WIN32
bool MorphPlayer::isContainerSupported(string ext){
    ostringstream oss;
    oss<<"amovie."<<ext;
    AVOutputFormat * of;
    of = av_guess_format(NULL, oss.str().c_str(), NULL);
    bool b = of;
    delete of;
    return b;
}
#endif

void MorphPlayer::enter(){
    ofSetWindowShape(1024, 768);
    gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
    gui->setHeight(ofGetHeight());
    gui->setVisible(true);
    ofAddListener(ofEvents().keyPressed , this, &MorphPlayer::onKeyPressed);
    makeReportName();
	bMask = true;
#ifdef TARGET_WIN32
	bRec=false;
#endif
}

void MorphPlayer::exit(){
    IState::exit();
    ofRemoveListener(ofEvents().keyPressed , this, &MorphPlayer::onKeyPressed);
}

void MorphPlayer::makeReportName(){
    reportName = "";
    reportName+= "report_";
    reportName+= ofToString(ofGetDay())+"_"+ofToString(ofGetMonth())+"_"+ofToString(ofGetYear());
    ofDirectory repDir("reports/");
    repDir.allowExt("xml");
    if(repDir.listDir()>0){
        int num = 0;
        vector<ofFile> ff = repDir.getFiles();
        for(int i=0;i<ff.size();i++){
            string fn = ff[i].getBaseName();
            if(ofStringTimesInString(fn, reportName)>0){
                num++;
            }
        }
        if(num>0){
            reportName+= "_"+ofToString(num);
        }
    }
    reportName+= ".xml";
}

void MorphPlayer::saveReport(MorphPlayer::TestArgs ta){
    ofxXmlSettings xml;
    bool bExists = xml.load("reports/"+reportName);
    if(!bExists){
        xml.clear();
    }
    if(!xml.tagExists("report")){
        xml.addTag("report");
        string sDate = ofToString(ofGetDay())+"/"+ofToString(ofGetMonth())+"/"+ofToString(ofGetYear());
        xml.addAttribute("report", "date", sDate, 0);
    }
    xml.pushTag("report");
    int nTests = xml.getNumTags("test");
    xml.addTag("test");
    xml.pushTag("test", nTests);
    xml.setValue("time", ta.curTime);
    xml.setValue("stopTime", ta.stopTime);
    xml.setValue("stopPct", ta.stopPct);
    xml.popTag();
    
    xml.popTag();
    
    xml.save("reports/"+reportName);
}

void MorphPlayer::update(){
    if(timer.bRunning){
        timer.update();
		updateClone(ofMap(timer.getPct(), 0, 1, minStr, morph.str));
    }
}

void MorphPlayer::draw(){
    if(morph.isReady()){
#ifdef TARGET_WIN32
		fboOutput.begin();
		ofClear(0,0,0);
#endif
		clone.draw(0, 0);
		if(bMask){
			mask.draw();
		}
#ifdef TARGET_WIN32
		fboOutput.end();
		fboOutput.draw(0,0);

		if(recorder.isRecording()){
			ofPixels pix;
			fboOutput.readToPixels(pix);
			recorder.addFrame(pix);
		}
#endif
    }
}

void MorphPlayer::load(){
    morph.load();
    if(morph.faceSrc.isReady()){
        ofSetWindowShape(morph.faceSrc.img.getWidth()+gui->getRect()->width, morph.faceSrc.img.getHeight()>ofGetHeight()?morph.faceSrc.img.getHeight():ofGetHeight());
        gui->setPosition(ofGetWidth()-gui->getRect()->width, 0);
        
        clone.setup(morph.faceSrc.img.getWidth(), morph.faceSrc.img.getHeight());
        ofFbo::Settings settings;
        settings.width = morph.faceSrc.img.getWidth();
        settings.height = morph.faceSrc.img.getHeight();
        fboSrc.allocate(settings);
        fboMsk.allocate(settings);
        
        ofMesh mshSrc = morph.faceSrc.msh;
        mshSrc.clearTexCoords();
        for(int i=0;i<mshSrc.getNumVertices();i++){
            mshSrc.addTexCoord(ofVec2f(morph.faceDst.msh.getVertex(i).x,morph.faceDst.msh.getVertex(i).y));
        }
        
        fboMsk.begin();
        ofClear(0, 255);
        mshSrc.draw();
        fboMsk.end();
        
        fboSrc.begin();
        ofClear(0, 255);
        morph.faceDst.img.bind();
        mshSrc.draw();
        morph.faceDst.img.unbind();
        fboSrc.end();
        
        updateClone(minStr);
        
        timer.setup(morph.time, 1);
        labStatus->setLabel("IDLE");

		mask.linkMesh(&morph.faceSrc.msh, morph.faceSrc.img.getWidth(), morph.faceSrc.img.getHeight());

#ifdef TARGET_WIN32
		fboOutput.allocate(morph.faceSrc.img.getWidth(), morph.faceSrc.img.getHeight(), GL_RGB);
		fboOutput.begin();
		ofClear(0,0,0);
		fboOutput.end();
#endif
    }
	bMask = true;
}

void MorphPlayer::updateClone(float str){
	if(morph.isReady()){
		clone.setStrength(str);
		clone.update(fboSrc.getTextureReference(), morph.faceSrc.img.getTextureReference(), fboMsk.getTextureReference());
	}
}

void MorphPlayer::start(){
    if(morph.isReady()){
        timer.reset();
        timer.start();
        labStatus->setLabel("RUNNING...");
    }
}

void MorphPlayer::stop(){
    MorphPlayer::TestArgs ta(timer.getLastPct(), timer.getLocalTime());
    if(timer.bRunning){
        timer.stop();
        labStatus->setLabel("IDLE");
        saveReport(ta);
    }

#ifdef TARGET_WIN32
	if(bRec){
		recorder.close();
	}
#else
    if(recorder.isRecording()){
        recorder.stop();
    }
#endif
}

void MorphPlayer::reset(){
    timer.stop();
    timer.reset();
    updateClone(0);
}

void MorphPlayer::startRecord(){
#ifdef TARGET_WIN32
	if(morph.isReady() && !bRec){
#else
    if(morph.isReady() && !recorder.isRecording()){
#endif
		string vidName = "";
        if(morph.fileName!=""){
            vidName = ofFilePath::getBaseName(morph.fileName);
        }else{
            vidName = "vid";
        }
#ifdef TARGET_WIN32
		recorder.setup(vidName,morph.faceSrc.img.getWidth(),morph.faceSrc.img.getHeight(),30);
		recorder.start();
		bRec = true;
#else
        recorder.setup(morph.faceSrc.img.getWidth(), morph.faceSrc.img.getHeight(),
                       recorder.BIT_RATE, recorder.FRAME_RATE, recorder.CODEC_ID,
                       recorder.CONTAINER);

        recorder.setRecordingArea(0, 0, morph.faceSrc.img.getWidth(), morph.faceSrc.img.getHeight());
        recorder.record(vidName);
#endif
		timer.reset();
        timer.start();
        labStatus->setLabel("RECORDING...");
    }
}

void MorphPlayer::onNaturalStop(int &tick){
    stop();
}

void MorphPlayer::onKeyPressed(ofKeyEventArgs & e){
    if(e.key==' '){
        stop();
    }
}

void MorphPlayer::close(){
#ifdef _THREAD_CAPTURE
    recorder.waitForThread();
#endif


}
