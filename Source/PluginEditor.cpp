/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
: AudioProcessorEditor (&p), myApvts(apvts), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&myLnF);
    setUpParameter(gainSlider, apvts, "GAIN", this);
    setUpParameter(attackSlider, apvts, "ATTACK", this);
    setUpParameter(decaySlider, apvts, "SUSTAIN", this);
    setUpParameter(sustainSlider, apvts, "DECAY", this);
    setUpParameter(releaseSlider, apvts, "RELEASE", this);
    setSize (800, 600);
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

}

void AudioPluginAudioProcessorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    //make a row of 4 sliders, with extra room
    auto sliderW = w / 6;
    auto sliderH = sliderW;
    auto next = sliderW + sliderW * 0.2f;
    auto xPos = sliderW/2;
    auto yPos = sliderH/2;
    gainSlider.slider->setBounds(xPos, yPos, sliderW, sliderH);
    attackSlider.slider->setBounds(xPos, yPos +=next, sliderW, sliderH);
    decaySlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
    sustainSlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
    releaseSlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
}

void AudioPluginAudioProcessorEditor::setUpParameter(SliderWithAttachment& s, juce::AudioProcessorValueTreeState& apvts, String labelText, Slider::Listener* listener)
{
    s.slider.reset(new juce::Slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox));
    addAndMakeVisible(s.slider.get());
    s.attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, labelText, *s.slider.get()));
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
