/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "MerritCoreProcessor.h"

//==============================================================================
int main (int argc, char* argv[])
{
    // read fileparth through argument
    File audioFile = File(argv[1]);
    MerritCoreProcessor* core = new MerritCoreProcessor(audioFile);
   
    core->processAudio(argv[3]);
    //output json
    String jsonName = argv[2];
    
    core->dumpJson(jsonName);
    
    deleteAndZero(core);
    
    return 0;
}
