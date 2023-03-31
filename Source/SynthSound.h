/*
  ==============================================================================

    SynthSound.h
    Created: 26 Mar 2023 9:18:33am
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
     
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
};
