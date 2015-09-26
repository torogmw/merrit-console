//
//  MerritCoreProcessor.cpp
//  merrit-console
//
//  Created by Minwei Gu on 9/26/15.
//
//

#include "MerritCoreProcessor.h"

#include <fstream>
#include <string>
#include <iostream>

MerritCoreProcessor::MerritCoreProcessor(File const &audioFile):
_audioFile(audioFile)
{
    //Audio setup
    //audioDeviceSetup.bufferSize = 512; // 0.04s if sample rate is 11.025kHz
    deviceManager.initialise(1, /* number of input channels */
                             2, /* number of output channels */
                             0, /* no XML settings*/
                             true, /* select default device on failure */
                             String::empty, /* preferred device name */
                             &audioDeviceSetup /* preferred setup options */);
    audioAnalyzer = new AudioAnalyzer(FS_MIR, 512);
    inputSource = new AudioInputSource(deviceManager, audioAnalyzer);
    //[/Constructor]
}

MerritCoreProcessor::~MerritCoreProcessor(){
    
}

void MerritCoreProcessor::processAudio(bool debug){
    // read audio
    inputSource->setFile(_audioFile);
    // play audio
    if (debug) {
        inputSource-> filePlayingControl();
        while(inputSource -> isPlaying());
    }
    // analyze audio
    printf("analyze_audio");
    // dumpJson
    String jsonName = _audioFile.getFileName() + "_score";
}

void MerritCoreProcessor::dumpJson(String songName) {
    // let's hack some fake data
    Array<int> time;
    time.set(0, 1200);
    time.set(1, 2200);
    time.set(2, 3200);
    time.set(3, 4200);
    time.set(4, 5200);
    time.set(5, 6200);
    Array<int> score;
    score.set(0,50);
    score.set(1,70);
    score.set(2,90);
    score.set(3,60);
    score.set(4,50);
    score.set(5,40);
    
    // onsets generator
    String jsonString;
    jsonString.append("{\"onsets\":[", 11);

    for (int i = 0; i<time.size(); i++) {
        jsonString.append("{\"time\":", 10);
        jsonString.append(String(time[i]), 5);
        jsonString.append(",", 1);
        jsonString.append("\"score\":", 10);
        jsonString.append(String(score[i]), 5);
        jsonString.append("}",1);
        if (i != time.size()-1) {
            // if not the last element
            jsonString.append(",", 1);
        }
    }
    jsonString.append("]}", 3);
    var jsonStream = JSON::fromString(jsonString);
    std::ofstream out(songName.toStdString());
    out << jsonString.toStdString();
    out.close();
    
    
}