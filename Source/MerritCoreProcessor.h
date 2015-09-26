//
//  MerritCoreProcessor.h
//  merrit-console
//
//  Created by Minwei Gu on 9/26/15.
//
//  read audio file, analyze, and send json

#ifndef __merrit_console__MerritCoreProcessor__
#define __merrit_console__MerritCoreProcessor__

#include <stdio.h>
#include "JuceHeader.h"
#include "AudioInputSource.h"
#include <map>

class MerritCoreProcessor {

public:
    MerritCoreProcessor(File const &audioFile);  // maybe add input here?
    ~MerritCoreProcessor();
    void processAudio(bool debug);
    void dumpJson(String songName);
    
    
private:
    // auio objects
    std::map<int, int> rawOnsets;
    AudioDeviceManager deviceManager;
    juce::AudioDeviceManager::AudioDeviceSetup audioDeviceSetup;
    ScopedPointer<AudioInputSource> inputSource;
    ScopedPointer<MusicXmlParser> notation;
    ScopedPointer<AudioAnalyzer> audioAnalyzer;
    String jsonObject;
    File _audioFile;
};

#endif /* defined(__merrit_console__MerritCoreProcessor__) */
