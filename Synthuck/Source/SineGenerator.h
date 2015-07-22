
#pragma once

#include "Processor.h"

///////////////////////////////////////////////////////////////////////////////

class SineGenerator : public Processor
{
public:
    SineGenerator();
    
    void initialise(double fSampleRate) override;
    
    void processAudio(AudioSampleBuffer& rAudioSampleBuffer) override;
    void processMidi(MidiBuffer& rMidiBuffer) override {};
    
    void setFrequency(float fFrequency) { m_fFrequency = fFrequency; };
    void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; };
    
private:
    double m_fSampleFrequency;
    
    float m_fFrequency;
    float m_fAmplitude;
    
    float m_fCosDelta;
    float m_fSinDelta;
    
    float m_fCosX;
    float m_fSinX;
    
    // Helpers
    
    void calculateDeltas();
    void incrementWaves();
    
    static const std::string s_aProcessorName;
};
