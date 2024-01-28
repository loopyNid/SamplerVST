#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerVSTAudioProcessor::SamplerVSTAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
    nFormatManager.registerBasicFormats();
    for (int i = 0; i < nVoices; i++)
    {
        nikkSampler.addVoice (new SamplerVoice());
    }
}

SamplerVSTAudioProcessor::~SamplerVSTAudioProcessor()
{
}

//==============================================================================
const juce::String SamplerVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamplerVSTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamplerVSTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamplerVSTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamplerVSTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamplerVSTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamplerVSTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamplerVSTAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String SamplerVSTAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void SamplerVSTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void SamplerVSTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);

    nikkSampler.setCurrentPlaybackSampleRate(sampleRate);
}

void SamplerVSTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool SamplerVSTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void SamplerVSTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    nikkSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SamplerVSTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SamplerVSTAudioProcessor::createEditor()
{
    return new SamplerVSTAudioProcessorEditor (*this);
}

//==============================================================================
void SamplerVSTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void SamplerVSTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

// ADDED BY NIKK ===============================================================

void SamplerVSTAudioProcessor::loadFile()
{
    FileChooser chooser {"Please load a file"};

    if (chooser.browseForFileToOpen ())
    {
        auto file = chooser.getResult();
        std::unique_ptr<AudioFormatReader> formatReader(nFormatManager.createReaderFor(file));
        if(formatReader)
        {
            BigInteger range;
            range.setRange(0, 128, true);
            nikkSampler.addSound(new SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10.0));
        }
    }
}

void SamplerVSTAudioProcessor::loadFile(const String& path)
{
    auto file = File(path);
    std::unique_ptr<AudioFormatReader> formatReader(nFormatManager.createReaderFor(file));
    AudioBuffer<float> waveForm;
    if(formatReader)
    {
        auto sampleLeght = static_cast<int>(formatReader->lengthInSamples);
        waveForm.setSize(1, sampleLeght);
        formatReader->read(&waveForm, 0, sampleLeght, 0, true, false);
        auto buffer = waveForm.getReadPointer(0);

        for(int sample = 0; sample < waveForm.getNumSamples(); sample++)
        {
            DBG(buffer[sample]);
        }
        
        BigInteger range;
        range.setRange(0, 128, true);
        nikkSampler.addSound(new SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10.0));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplerVSTAudioProcessor();
}