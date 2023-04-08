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
    g.setColour(juce::Colours::white);
    g.fillAll();
    
}
void WaveformVisual::resized()
{
    
}
