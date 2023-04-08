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
    shouldDrawNewWave = true;
}

void WaveformVisual::paint (juce::Graphics& g)
{
    auto w = getWidth();
    auto h = getHeight();
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(0, 0, w, h, w*.02f);
    g.setColour(Colours::white);
    if(shouldDrawNewWave)
    {
        Path p;
        auto waveform = audioProcessor.getWaveform();
        auto ratio = waveform.getNumSamples() / w;
        auto buffer = waveform.getReadPointer(0);
        for(int i = 0; i < waveform.getNumSamples(); i+=ratio)
        {
            audioPoints.push_back(buffer[i]);
        }
        //start the waveform from the left of the component
        p.startNewSubPath(0, h/2);
        //scale for y axis
        for(int i = 0; i < audioPoints.size(); i++)
        {
            auto point = jmap<float>(audioPoints[i], -1.0f, 1.0f, h, 0);
            p.lineTo(i, point);
        }
        g.strokePath(p, PathStrokeType(1.0f));
        shouldDrawNewWave = false;
    }
}
void WaveformVisual::resized()
{
    
}
