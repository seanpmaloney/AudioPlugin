/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 28 Mar 2023 11:35:33am
    Author:  Sean Maloney

  ==============================================================================
*/

#include "MyLookAndFeel.h"

void MyLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = juce::Colours::darkgrey ;
    auto fill    = juce::Colours::white;

    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = 3.0f;
    auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    g.setColour (fill);
    g.drawEllipse(bounds.getCentreX() - arcRadius, bounds.getCentreY() - arcRadius, arcRadius*2, arcRadius*2, lineW);

    auto thumbWidth = lineW * 2.0f;
    Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));
    
    if (slider.isEnabled())
    {
        Path valueLine;
        Line line(thumbPoint.x, thumbPoint.y, bounds.getCentreX(), bounds.getCentreY());
    
        valueLine.addLineSegment(line, lineW);

        g.setColour (fill);
        g.strokePath(valueLine, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
}
