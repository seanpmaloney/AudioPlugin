/*
  ==============================================================================

    SynthVoice.h
    Created: 25 Mar 2023 5:04:58pm
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice();
    ~SynthVoice();
    bool canPlaySound (SynthesiserSound* sound) override;

    /** Called to start a new note.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
    void startNote (int midiNoteNumber,
                            float velocity,
                            SynthesiserSound* sound,
                    int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;

    /** Called to let the voice know that the pitch wheel has been moved.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
    void pitchWheelMoved (int newPitchWheelValue) override;

    /** Called to let the voice know that a midi controller has been moved.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void renderNextBlock (AudioBuffer<float>& outputBuffer,
                                  int startSample,
                          int numSamples) override;
    void prepare(double sampleRate, int maximumExpectedSamplesPerBlock, int numChannels);
    dsp::Gain<float> gain;
private:
    dsp::Oscillator<float> osc {[](float x){return std::sin(x);}};
};
