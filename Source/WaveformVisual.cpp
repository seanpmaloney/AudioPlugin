/*
  ==============================================================================

    WaveformVisual.cpp
    Created: 4 Apr 2023 8:26:06pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include "WaveformVisual.h"

WaveformVisual::WaveformVisual(AudioPluginAudioProcessor& p) : audioProcessor(p)
{
    setSize(100, 20);    
}

WaveformVisual::~WaveformVisual()
{
    
}

bool WaveformVisual::isInterestedInFileDrag (const StringArray& files)
{
    return true;
}
void WaveformVisual::filesDropped (const StringArray& files, int x, int y)
{
    
        audioProcessor.loadSample(files[0]);
}

void WaveformVisual::paint (juce::Graphics& g)
{
    auto w = getWidth();
    auto h = getHeight();
    g.setColour(juce::Colours::white);
    g.fillAll();
    //steps to draw the waveform
    //Get the waveform
    auto waveform = audioProcessor.getWaveform();
    //Find ratio of samples to the width of this component
    auto ratio = waveform.getNumSamples() / w;
    auto buffer = waveform.getReadPointer(0);
    //scale for x axis
    for(int i = 0; i < waveform.getNumSamples(); i+=ratio)
    {
        audioPoints.push_back(buffer[i]);
    }
    //scale for y axis
    for(int i = 0; i < audioPoints.size(); i++)
    {
        jmap<float>(audioPoints[i], -1.0f, 1.0f, h, 0);
    }
    //TODO: draw using the vector..
}
void WaveformVisual::resized()
{
    
}
