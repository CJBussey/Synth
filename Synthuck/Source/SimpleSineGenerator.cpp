
#include "SimpleSineGenerator.h"

///////////////////////////////////////////////////////////////////////////////
const std::string SimpleSineGenerator::s_aProcessorName = "SimpleSineGenerator";
///////////////////////////////////////////////////////////////////////////////

SimpleSineGenerator::SimpleSineGenerator()
:   Processor(s_aProcessorName)
,   m_fFrequency(1000)
,   m_fPhase(0.0f)
,   m_fAmplitude(1)
{
}

///////////////////////////////////////////////////////////////////////////////

void SimpleSineGenerator::initialise(double fSampleRate)
{
    m_fSampleFrequency = fSampleRate;
    m_bInitialised = true;
}

///////////////////////////////////////////////////////////////////////////////

void SimpleSineGenerator::processAudio(AudioSampleBuffer& rAudioSampleBuffer)
{
    const size_t nSamples = rAudioSampleBuffer.getNumSamples();
    const size_t nChannels = rAudioSampleBuffer.getNumChannels();
    
    for (size_t nSample = 0; nSample < nSamples; ++nSample)
    {
        float fSampleData = m_fAmplitude * sin(m_fPhase);
        m_fPhase += 2 * M_PI * m_fFrequency / m_fSampleFrequency;
        
        for (size_t nChannel = 0; nChannel < nChannels; ++nChannel)
        {
            float* pWriteBuffer = rAudioSampleBuffer.getWritePointer(nChannel);
            pWriteBuffer[nSample] = fSampleData;
        }
    }
    
}

///////////////////////////////////////////////////////////////////////////////