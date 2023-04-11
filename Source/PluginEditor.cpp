/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
: AudioProcessorEditor (&p), myApvts(apvts),waveformVisual(p), audioProcessor (p)
{
    setLookAndFeel(&myLnF);
    setUpParameter(gainSlider, apvts, "GAIN", this);
    setUpParameter(attackSlider, apvts, "ATTACK", this);
    setUpParameter(decaySlider, apvts, "SUSTAIN", this);
    setUpParameter(sustainSlider, apvts, "DECAY", this);
    setUpParameter(releaseSlider, apvts, "RELEASE", this);
    addAndMakeVisible(waveformVisual);
    setResizable(true, false);
    setSize (800, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);
    g.setColour(juce::Colours::white.darker());
    int w = getWidth();
    auto sliderW = w / 5;
    auto sliderH = sliderW;
    auto next = sliderW;
    auto xPos = sliderW * 0.5f;
    auto yPos = sliderH;
    g.drawRoundedRectangle(xPos + next, yPos, sliderW * 3, sliderH, w*.02f,w*.01f);
}

void AudioPluginAudioProcessorEditor::resized()
{
    int w = getWidth();
    //make a row of 4 sliders, with extra room
    auto sliderW = w / 5;
    auto sliderH = sliderW;
    auto next = sliderW;
    auto xPos = sliderW * 0.5f;
    auto yPos = sliderH;
    waveformVisual.setBounds(xPos + next, yPos, sliderW * 3, sliderH);
    gainSlider.slider->setBounds(xPos, yPos, sliderW, sliderH);
    attackSlider.slider->setBounds(xPos, (yPos += (next * 1.2)), sliderW, sliderH);
    decaySlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
    sustainSlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
    releaseSlider.slider->setBounds(xPos+=next, yPos, sliderW, sliderH);
}

void AudioPluginAudioProcessorEditor::setUpParameter(SliderWithAttachment& s, juce::AudioProcessorValueTreeState& apvts, String labelText, Slider::Listener* listener)
{
    s.slider.reset(new juce::Slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxAbove));
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

void AudioPluginAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
    
}

