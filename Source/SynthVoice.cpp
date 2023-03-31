/*
  ==============================================================================

    SamplePlayer.cpp
    Created: 25 Mar 2023 5:04:58pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    
}
SynthVoice::~SynthVoice()
{
    
}
bool SynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<SynthesiserSound*>(sound) != nullptr;
}

/** Called to start a new note.
    This will be called during the rendering callback, so must be fast and thread-safe.
*/
void SynthVoice::startNote (int midiNoteNumber,
                        float velocity,
                        SynthesiserSound* sound,
                int currentPitchWheelPosition)
{
    
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    
}

/** Called to let the voice know that the pitch wheel has been moved.
    This will be called during the rendering callback, so must be fast and thread-safe.
*/
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

/** Called to let the voice know that a midi controller has been moved.
    This will be called during the rendering callback, so must be fast and thread-safe.
*/
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                              int startSample,
                      int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void SynthVoice::prepare(double sampleRate, int maximumExpectedSamplesPerBlock, int numChannels)
{
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = maximumExpectedSamplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    osc.prepare(spec);
    gain.prepare(spec);
    //osc.setFrequency(440);
    //gain.setGainLinear(0.05f);
}
