
#include "SineGenerator.h"

///////////////////////////////////////////////////////////////////////////////
const std::string SineGenerator::s_aProcessorName = "SineGenerator";
///////////////////////////////////////////////////////////////////////////////

SineGenerator::SineGenerator()
:   Processor(s_aProcessorName)
,   m_fFrequency(1000)
,   m_fAmplitude(1.)
,   m_fCosDelta(0.)
,   m_fSinDelta(0.)
,   m_fCosX(1.)
,   m_fSinX(0.)
{
}

///////////////////////////////////////////////////////////////////////////////

void SineGenerator::initialise(double fSampleRate)
{
    m_fSampleFrequency = fSampleRate;
    calculateDeltas();
    
    m_bInitialised = true;
}

///////////////////////////////////////////////////////////////////////////////

void SineGenerator::processAudio(juce::AudioSampleBuffer &rAudioSampleBuffer)
{
    const size_t nSamples = rAudioSampleBuffer.getNumSamples();
    const size_t nChannels = rAudioSampleBuffer.getNumChannels();
    
    for (size_t nSample = 0; nSample < nSamples; ++nSample)
    {
        for (size_t nChannel = 0; nChannel < nChannels; ++nChannel)
        {
            float* pWriteBuffer = rAudioSampleBuffer.getWritePointer(nChannel);
            pWriteBuffer[nSample] = m_fSinX;
        }
        
        incrementWaves();
    }
}

///////////////////////////////////////////////////////////////////////////////
// Helpers
///////////////////////////////////////////////////////////////////////////////

void SineGenerator::calculateDeltas()
{
    float fDelta = 2 * M_PI * m_fFrequency / m_fSampleFrequency;
    m_fCosDelta = cos(fDelta);
    m_fSinDelta = sin(fDelta);
}

///////////////////////////////////////////////////////////////////////////////

void SineGenerator::incrementWaves()
{
    // NOTE: m_fSinDelta and m_fCosDelta shouldn't change during this call
    
    float fTmpSinX = m_fSinX;
    float fTmpCosX = m_fCosX;

    // sin(x + delta) = sin(x)cos(delta) + sin(delta)cos(x)
    m_fSinX = fTmpSinX*m_fCosDelta + m_fSinDelta*fTmpCosX;
    // cos(x + delta) = cos(x)cos(delta) - sin(x)sin(delta)
    m_fCosX = fTmpCosX*m_fCosDelta - fTmpSinX*m_fSinDelta;
}

///////////////////////////////////////////////////////////////////////////////
