/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), audioProcessor (p), myApvts(apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setUpParameter(gainSlider, myApvts, "Gain", this);
    setSize (400, 300);
    setResizable(true, false);

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("synth", 0, 0, getWidth()/2, getHeight()/9, Justification::centredLeft);

}

void AudioPluginAudioProcessorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    gainSlider.slider->setBounds(w/4, h/4, w/2, h/2);
}

void AudioPluginAudioProcessorEditor::setUpParameter(SliderWithAttachment& s, juce::AudioProcessorValueTreeState& apvts, String labelText, Slider::Listener* listener)
{
    s.slider.reset(new juce::Slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox));
    addAndMakeVisible(s.slider.get());
    s.attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, "GAIN", *s.slider.get()));
    s.slider->addListener(listener);
    if(labelText != "")
    {
        addAndMakeVisible(s.label);
        s.label.setText(labelText, juce::dontSendNotification);
        s.label.attachToComponent(s.slider.get(), false);
        s.label.setJustificationType(juce::Justification::centredBottom);
    }
}

void AudioPluginAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    
}
