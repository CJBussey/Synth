
#include "Processor.h"

///////////////////////////////////////////////////////////////////////////////

Processor::Processor(std::string aProcessorName)
:   m_aProcessorName(aProcessorName)
,   m_bInitialised(false)
{
}

void Processor::process(AudioSampleBuffer& rAudioSampleBuffer,
                        MidiBuffer& rMidiBuffer)
{
    if (!m_bInitialised)
    {
        std::cerr << "Error: "<< m_aProcessorName << "::processAudio"
        << std::endl;
        return;
    }
    
    processAudio(rAudioSampleBuffer);
    processMidi(rMidiBuffer);
}

///////////////////////////////////////////////////////////////////////////////