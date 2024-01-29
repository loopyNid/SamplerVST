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
class SampleThumbnail  : public juce::Component, public juce::ChangeListener
{
public:
    SampleThumbnail(AudioThumbnail& nTh) : th(nTh){};
    ~SampleThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(ChangeBroadcaster *source) override;
    void paintIfNoFileLoaded(juce::Graphics& g, Rectangle<int> area);
    void paintIfFileLoaded(juce::Graphics& g, Rectangle<int> area);
private:
    AudioThumbnail& th;
    bool draw = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleThumbnail)
};