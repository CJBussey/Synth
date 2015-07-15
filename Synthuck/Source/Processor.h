
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

///////////////////////////////////////////////////////////////////////////////

class Processor
{
public:
    // Lifetime
    Processor(std::string aProcessorName);
    virtual ~Processor() {};
    
    // Initialisation
    virtual void initialise(double fSampleRate) = 0;
    
    // Process
    virtual void process(AudioSampleBuffer& rAudioSampleBuffer,
                         MidiBuffer& rMidiBuffer);
    virtual void processAudio(AudioSampleBuffer& rAudioSampleBuffer) = 0;
    virtual void processMidi(MidiBuffer& rMidiBuffer) = 0;

protected:
    const std::string m_aProcessorName;
    
    bool m_bInitialised;
};

///////////////////////////////////////////////////////////////////////////////