/*
  ==============================================================================

    SampleThumbnail.h
    Author:  budos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SampleThumbnail  : public juce::Component, public juce::ChangeListener, private juce::Timer 
{
public:
    SampleThumbnail(AudioThumbnail& nTh);
    ~SampleThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(ChangeBroadcaster *source) override;

    void paintIfNoFileLoaded(juce::Graphics& g, Rectangle<int> area);
    void paintIfFileLoaded(juce::Graphics& g, Rectangle<int> area);

    void thChanged();

    void timerCallback() override
    {
        repaint();
    }

private:
    AudioThumbnail& th;
    bool draw = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleThumbnail)
};