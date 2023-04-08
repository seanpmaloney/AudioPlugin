/*
  ==============================================================================

    WaveformVisual.h
    Created: 4 Apr 2023 8:26:06pm
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class WaveformVisual : public FileDragAndDropTarget, public Component
{
public:
    WaveformVisual(AudioPluginAudioProcessor& p);
    ~WaveformVisual();
    //component overrides
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //drag and drop overrides
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;
private:
    std::vector<float> audioPoints;
    bool shouldDrawNewWave = false;
    AudioPluginAudioProcessor& audioProcessor;
};
