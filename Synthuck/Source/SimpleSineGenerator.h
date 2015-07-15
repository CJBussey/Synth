
#pragma once

#include "Processor.h"

///////////////////////////////////////////////////////////////////////////////

class SimpleSineGenerator : public Processor
{
public:
    SimpleSineGenerator();
    
    void initialise(double fSampleRate) override;
    
    void processAudio(AudioSampleBuffer& rAudioSampleBuffer) override;
    void processMidi(MidiBuffer& rMidiBuffer) override {};
    
    void setFrequency(float fFrequency) { m_fFrequency = fFrequency; };
    void setPhase(float fPhase) { m_fPhase = fPhase; };
    void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; };
    
private:
    double m_fSampleFrequency;
    
    float m_fFrequency;
    float m_fPhase;
    float m_fAmplitude;
    
    static const std::string s_aProcessorName;
};

///////////////////////////////////////////////////////////////////////////////