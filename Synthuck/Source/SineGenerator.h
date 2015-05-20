//
//  SineGenerator.h
//  Synthuck
//
//  Created by Carl Bussey on 21/05/2015.
//
//

#pragma once

#include "Processor.h"
#include <memory>

///////////////////////////////////////////////////////////////////////////////

class SineGenerator : public Processor
{
public:
    SineGenerator();
    
    void initialise(double fSampleRate) override;
    
    void processAudio(AudioSampleBuffer& rAudioSampleBuffer) override;
    void processMidi(MidiBuffer& rMidiBuffer) override {};
    
private:
    double m_fSampleFrequency;
    
    float m_fFrequency;
    float m_fPhase;
    float m_fAmplitude;
};

///////////////////////////////////////////////////////////////////////////////