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
    // read audio and analyze
    rawOnsets = inputSource->setFile(_audioFile);
    // play audio
    if (debug) {
        inputSource-> filePlayingControl();
        while(inputSource -> isPlaying());
    }
    
}

void MerritCoreProcessor::dumpJson(String songName) {
    
    String jsonString;
    jsonString.append("{\"onsets\":[", 11);
    // onsets generator
    for (std::map<int,int>::iterator it=rawOnsets.begin(); it!=rawOnsets.end(); ++it) {
        jsonString.append("{\"time\":", 10);
        jsonString.append(String(it->first), 5);
        jsonString.append(",", 1);
        jsonString.append("\"score\":", 10);
        jsonString.append(String(it->second), 5);
        jsonString.append("}",1);
        if (it != rawOnsets.end()) {
            // if not the last element
            jsonString.append(",", 1);
        }
    }
    jsonString = jsonString.substring(0, jsonString.length()-1);
    jsonString.append("]}", 3);
    var jsonStream = JSON::fromString(jsonString);
    std::ofstream out(songName.toStdString());
    out << jsonString.toStdString();
    out.close();
    
    
}