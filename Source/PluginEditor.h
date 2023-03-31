/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyLookAndFeel.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, Slider::Listener
{
public:
    struct SliderWithAttachment
    {
        std::unique_ptr<Slider> slider;
        std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attachment;
        Label label;
        String labeltext;
    };
    AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setUpParameter(SliderWithAttachment& s, juce::AudioProcessorValueTreeState& apvts, String labelText, Slider::Listener* listener);
    void sliderValueChanged (Slider* slider) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& audioProcessor;
    MyLookAndFeel myLnF;
    std::unique_ptr<SliderWithAttachment> gainSlider;
    AudioProcessorValueTreeState& myApvts;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
