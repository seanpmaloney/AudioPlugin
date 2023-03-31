/*
  ==============================================================================

    AudioEngine.cpp
    Created: 25 Mar 2023 4:32:12pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include "AudioEngine.h"

AudioEngine::AudioEngine() : AudioProcessor()
{
    for(int i = 0; i < 8; i ++)
    {
        synth.addSound(new SynthSound());
        synth.addVoice(new SynthVoice());
    }
}
AudioEngine::~AudioEngine()
{
    
}

void AudioEngine::prepareToPlay (double sampleRate,
                                 int maximumExpectedSamplesPerBlock)
{
    for(int i = 0; i < synth.getNumVoices(); i ++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepare(sampleRate, maximumExpectedSamplesPerBlock, getTotalNumOutputChannels());
        }
    }
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void AudioEngine::processBlock (juce::AudioSampleBuffer& audioBuffer, juce::MidiBuffer& midiBuffer)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for(auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        audioBuffer.clear (i, 0, audioBuffer.getNumSamples());
    
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        if(auto voice = dynamic_cast<SynthesiserVoice*>(synth.getVoice(i)))
        {
            //osc controls, ADSR, LFO... make sure these params are updated from the value tree
        }
    }
    juce::dsp::AudioBlock<float> audioBlock {audioBuffer};
    synth.renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());
}
