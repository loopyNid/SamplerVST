#pragma once

#include "PluginProcessor.h"
#include "SampleThumbnail.h"

//==============================================================================
class SamplerVSTAudioProcessorEditor final : public juce::AudioProcessorEditor, public FileDragAndDropTarget
{
public:
    explicit SamplerVSTAudioProcessorEditor (SamplerVSTAudioProcessor&);
    ~SamplerVSTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;

    

private:
    TextButton nLoadButton {"Load"};

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SamplerVSTAudioProcessor& processorRef;

    SampleThumbnail sThumb = SampleThumbnail(processorRef.th);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerVSTAudioProcessorEditor)
};
