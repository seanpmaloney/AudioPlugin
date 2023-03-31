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
    setSize (400, 300);
    setResizable(true, false);
//    setUpParameter(gainSlider, myApvts, "Gain", this);

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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AudioPluginAudioProcessorEditor::setUpParameter(SliderWithAttachment& s, juce::AudioProcessorValueTreeState& apvts, String labelText, Slider::Listener* listener)
{

    //myLnF.getLabelFont(s.label);
    s.slider.reset(new juce::Slider(juce::Slider::LinearHorizontal, juce::Slider::NoTextBox));
    addAndMakeVisible(s.slider.get());
    //s.slider->setLookAndFeel(&myLnF);
//    juce::String sID = "0." + byteOffset;
//    juce::String aID = "0." + String(offsetof(SynthModulation, destination));
//    juce::String bID = "0." + String(offsetof(SynthPatch, octave));
    s.attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, "", *s.slider.get()));
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
