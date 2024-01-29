#pragma once

#include <JuceHeader.h>//added by Nikk
#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class SamplerVSTAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    SamplerVSTAudioProcessor();
    ~SamplerVSTAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void loadFile();
    void loadFile(const String& path);

    AudioThumbnail th;
private:
    AudioFormatManager nFormatManager;
    Synthesiser nikkSampler;
    const int nVoices {10};

    AudioThumbnailCache thCache;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerVSTAudioProcessor)
};
