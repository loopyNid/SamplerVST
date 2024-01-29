/*
  ==============================================================================

    SampleThumbnail.cpp
    Author:  budos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SampleThumbnail.h"

//==============================================================================
// SampleThumbnail::SampleThumbnail(AudioThumbnail& nTh) : th(nTh)
// {
//     // In your constructor, you should add any child components, and
//     // initialise any special settings that your component needs.
// }

SampleThumbnail::~SampleThumbnail()
{
}

void SampleThumbnail::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    Rectangle<int> area = getLocalBounds();
    if(th.getNumChannels() == 0)
    {
      paintIfNoFileLoaded(g, area);
    } else {
      paintIfFileLoaded(g, area);
    }
    // std::cout << th.getNumChannels() << std::endl;
    // g.setColour(Colours::orangered);
    // th.drawChannels(g, getBounds(), 0, th.getTotalLength(), 1.0f);
    // DBG("drawing");

}

void SampleThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SampleThumbnail::changeListenerCallback(ChangeBroadcaster *source)
{
    if (source == &th){
        DBG("changeListened");
    }
    repaint();
}
void SampleThumbnail::paintIfNoFileLoaded(juce::Graphics& g, Rectangle<int> area)
{
  g.setColour (juce::Colours::darkgrey);
  g.fillRect (area);
  g.setColour (juce::Colours::white);
  g.drawFittedText ("No File Loaded", area, juce::Justification::centred, 1);
}
void SampleThumbnail::paintIfFileLoaded(juce::Graphics& g, Rectangle<int> area)
{
  g.setColour (juce::Colours::white);
  g.fillRect (area);

  g.setColour (juce::Colours::red);                               // [8]
  th.drawChannels (g,                                      // [9]
                        area,
                        0.0,                                    // start time
                        th.getTotalLength(),             // end time
                        1.0f);                                  // vertical zoom
}