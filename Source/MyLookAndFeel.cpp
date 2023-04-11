/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 28 Mar 2023 11:35:33am
    Author:  Sean Maloney

  ==============================================================================
*/

#include "MyLookAndFeel.h"

MyLookAndFeel::MyLookAndFeel()
{
    type = Font(Typeface::createSystemTypefaceFor(BinaryData::SFProDisplayBold_otf, BinaryData::SFProDisplayBold_otfSize));
    setDefaultSansSerifTypeface(type.getTypefacePtr());
}

void MyLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto fill    = juce::Colours::white;
    auto bounds = Rectangle<int> (x , y, width , height).toFloat().reduced (width*height*.001);
    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = width * .015f;
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
    g.setColour (fill.darker());
    g.fillEllipse(bounds.getCentreX() - arcRadius + 4, bounds.getCentreY() - arcRadius + 4, arcRadius*2, arcRadius*2);
    g.setColour (fill);
    g.fillEllipse(bounds.getCentreX() - arcRadius, bounds.getCentreY() - arcRadius, arcRadius*2, arcRadius*2);
    g.setColour (fill.darker());
    g.drawEllipse(bounds.getCentreX() - arcRadius, bounds.getCentreY() - arcRadius, arcRadius*2, arcRadius*2, lineW);

    Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));
    
    if (slider.isEnabled())
    {
        Path valueLine;
        Line line(thumbPoint.x, thumbPoint.y, (bounds.getCentreX() + thumbPoint.x)/2, (bounds.getCentreY() + thumbPoint.y)/2);
    
        valueLine.addLineSegment(line, lineW);

        g.setColour (fill.darker());
        g.strokePath(valueLine, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
//    g.drawEllipse(thumbPoint.getX() - (lineW * 5), thumbPoint.getY() - (lineW * 5), lineW * 10, lineW * 10, lineW);
//    g.setColour(Colours::black);
//    g.fillEllipse(thumbPoint.getX() - (lineW * 5), thumbPoint.getY() - (lineW * 5), lineW * 10, lineW * 10);
    
}

Font MyLookAndFeel::getLabelFont (Label& label)
{
    return type;
}

void MyLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));

        g.setColour (Colours::white.darker());
        g.setFont (font);

        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}
