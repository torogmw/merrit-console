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
    //File audioFile = File("../Debug/meditation.aiff");
    File audioFile = File(argv[1]);
    MerritCoreProcessor* core = new MerritCoreProcessor(audioFile);
   
    core->processAudio(false);
    //output json
    String jsonName = argv[2];
    
    core->dumpJson(jsonName);
    //core->dumpJson("fake.json");
    deleteAndZero(core);
    
    return 0;
}
