#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerVSTAudioProcessorEditor::SamplerVSTAudioProcessorEditor (SamplerVSTAudioProcessor& p)
    : AudioProcessorEditor (&p),
                                processorRef (p)
{
    juce::ignoreUnused (processorRef);
    
    processorRef.th.addChangeListener(&sThumb);
    
    addAndMakeVisible(sThumb);

    nLoadButton.onClick = [&] {processorRef.loadFile();};
    addAndMakeVisible(nLoadButton);

    ampSlider.setRange(0.0, 1.0);
    ampSlider.setValue(processorRef.amp);
    ampSlider.onValueChange = [&] {processorRef.setAmp(ampSlider.getValue());};
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible(ampSlider);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 300);
}

SamplerVSTAudioProcessorEditor::~SamplerVSTAudioProcessorEditor()
{
    //set listener?
}

//==============================================================================
void SamplerVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::purple);
    // addAndMakeVisible(sThumb);
    // th.drawChannels(g, getLocalBounds(), 0, th.getTotalLength(), 1.0f);
}

void SamplerVSTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    sThumb.setBounds(getWidth()/2,0,getWidth()/2,getHeight());
    uiArea.setBounds(0, 0, getWidth()/2, getHeight());
    nLoadButton.setBounds(20, 20, uiArea.getWidth() / 3 -50, uiArea.getHeight() / 3 -50);
    ampSlider.setBounds(20, 70, uiArea.getWidth() / 3 , uiArea.getHeight() / 3 );
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
        }
    }
}