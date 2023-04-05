/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
: AudioProcessorEditor (&p), myApvts(apvts), visual(512, frmtMgr, thmbnlCache), thmbnlCache(5) ,audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&myLnF);
    setUpParameter(gainSlider, apvts, "GAIN", this);
    setUpParameter(attackSlider, apvts, "ATTACK", this);
    setUpParameter(decaySlider, apvts, "SUSTAIN", this);
    setUpParameter(sustainSlider, apvts, "DECAY", this);
    setUpParameter(releaseSlider, apvts, "RELEASE", this);
    setResizable(true, false);

    visual.addChangeListener(this);
    
    loadSampleButton.reset(new TextButton);
    loadSampleButton->setButtonText("LOAD");
    addAndMakeVisible(loadSampleButton.get());
    loadSampleButton->onClick = [this]()
    {
        chooser = std::make_unique<juce::FileChooser> ("Select a Wave file to play...",
                                                       juce::File{},
                                                       "*.wav");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
                {
                    auto file = fc.getResult();
         
                    if (file != juce::File{})
                    {
                        auto* reader = frmtMgr.createReaderFor (file);
         
                        if (reader != nullptr)
                        {
                            auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
                            transport.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                            visual.setSource (new juce::FileInputSource (file));                            // [7]
                            readerSrc.reset (newSource.release());
                        }
                    }
                });
    };
    frmtMgr.registerBasicFormats();
    setSize (800, 600);
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
    int w = getWidth();
    auto sliderW = w / 5;
    auto sliderH = sliderW;
    auto next = sliderW;
    auto xPos = sliderW * 0.5f;
    auto yPos = sliderH;
    juce::Rectangle<float> thumbnailBounds (xPos +=next, yPos, sliderW * 3, sliderH);
    g.setColour (juce::Colours::black);
    g.fillRoundedRectangle(thumbnailBounds, (w*.02f));
    g.setColour (juce::Colours::white);
    g.drawRoundedRectangle(thumbnailBounds, (w*.02f), (w*.002f));
    g.setColour (juce::Colours::red);
    visual.drawChannels (g, thumbnailBounds.toNearestInt(),
                        0.0, visual.getTotalLength(), 1.0f);

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
    loadSampleButton->setBounds(w - sliderW, 0, sliderW, sliderH/2);
    gainSlider.slider->setBounds(xPos, yPos, sliderW, sliderH);
    attackSlider.slider->setBounds(xPos, (yPos += (next * 1.2)), sliderW, sliderH);
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

void AudioPluginAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == &visual) repaint();
}

