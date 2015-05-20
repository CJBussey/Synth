//
//  Processor.cpp
//  Synthuck
//
//  Created by Carl Bussey on 21/05/2015.
//
//

#include "Processor.h"

///////////////////////////////////////////////////////////////////////////////

Processor::Processor()
:   m_bInitialised(false)
{
}

void Processor::process(AudioSampleBuffer& rAudioSampleBuffer,
                        MidiBuffer& rMidiBuffer)
{
    processAudio(rAudioSampleBuffer);
    processMidi(rMidiBuffer);
}

///////////////////////////////////////////////////////////////////////////////