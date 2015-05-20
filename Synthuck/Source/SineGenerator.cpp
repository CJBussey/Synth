//
//  SineGenerator.cpp
//  Synthuck
//
//  Created by Carl Bussey on 21/05/2015.
//
//

#include "SineGenerator.h"

///////////////////////////////////////////////////////////////////////////////

SineGenerator::SineGenerator()
:   m_fFrequency(1000)
,   m_fPhase(0.0f)
,   m_fAmplitude(1)
{
}

///////////////////////////////////////////////////////////////////////////////

void SineGenerator::initialise(double fSampleRate)
{
    m_fSampleFrequency = fSampleRate;
    m_bInitialised = true;
}

///////////////////////////////////////////////////////////////////////////////

void SineGenerator::processAudio(AudioSampleBuffer& rAudioSampleBuffer)
{
    const size_t nSamples = rAudioSampleBuffer.getNumSamples();
    float* pWriteBuffer = rAudioSampleBuffer.getWritePointer(0);
    
    if (!pWriteBuffer || !m_bInitialised)
    {
        std::cerr << "Error: SineGenerator::processAudio"
            << std::endl;
        return;
    }
    
    float fTmpPhase = m_fPhase;
    for (size_t nIndex = 0; nIndex < nSamples; ++nIndex)
    {
        pWriteBuffer[nIndex] = m_fAmplitude * sin(fTmpPhase);
        fTmpPhase += 2 * M_PI * m_fFrequency / m_fSampleFrequency;
    }
    m_fPhase = fmod(fTmpPhase, 2.0 * M_PI);
    
}

///////////////////////////////////////////////////////////////////////////////