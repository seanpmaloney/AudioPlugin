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
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, Slider::Listener, ChangeListener
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
    void changeListenerCallback (ChangeBroadcaster* source) override;
private:
    MyLookAndFeel myLnF;
    AudioProcessorValueTreeState& myApvts;
    SliderWithAttachment gainSlider;
    SliderWithAttachment attackSlider;
    SliderWithAttachment decaySlider;
    SliderWithAttachment sustainSlider;
    SliderWithAttachment releaseSlider;
    Array<SliderWithAttachment> sliders;
    AudioThumbnail visual;
    AudioFormatManager frmtMgr;
    AudioThumbnailCache thmbnlCache;
    AudioTransportSource transport;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSrc;
    std::unique_ptr<TextButton> loadSampleButton;
    std::unique_ptr<FileChooser> chooser;
    AudioPluginAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
