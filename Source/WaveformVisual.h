/*
  ==============================================================================

    WaveformVisual.h
    Created: 4 Apr 2023 8:26:06pm
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class WaveformVisual : public AudioThumbnail, public FileDragAndDropTarget, public Component
{
public:
    //audio thumbnail overrides
    void reset (int numChannels, double sampleRate, int64 totalSamplesInSource) override;
    //drag and drop overrides
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;
private:
    AudioFormatManager frmtMgr;
    AudioThumbnailCache thmbnlCache;
};
