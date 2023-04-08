/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 28 Mar 2023 11:35:33am
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    MyLookAndFeel();
    //override the parts you want to customize
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, Slider&) override;
    Font getLabelFont (Label& label) override;
private:
    Font type;

};
