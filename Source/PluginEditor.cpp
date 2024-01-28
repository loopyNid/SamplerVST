#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerVSTAudioProcessorEditor::SamplerVSTAudioProcessorEditor (SamplerVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    nLoadButton.onClick = [&] {processorRef.loadFile();};
    addAndMakeVisible(nLoadButton);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SamplerVSTAudioProcessorEditor::~SamplerVSTAudioProcessorEditor()
{
}

//==============================================================================
void SamplerVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SamplerVSTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    nLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}

bool SamplerVSTAudioProcessorEditor::isInterestedInFileDrag(const StringArray& files)
{
    for(auto file: files)
    {
        if(file.contains (".wav") || file.contains (".mp3") || file.contains (".aif") || file.contains (".aiff"))
        {
            return true;
        }
    }
    
    return false;
}

void SamplerVSTAudioProcessorEditor::filesDropped(const StringArray& files, int x, int y)
{
    for( auto file : files) {
        if(isInterestedInFileDrag(file))
        {
            processorRef.loadFile(file);
            // std::cout << "loaded file" << std::endl;
        }
    }
}