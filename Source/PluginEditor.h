/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::Button::Listener
{
public:
    //==============================================================================
    PluginEditor (MidiRingAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MidiRingAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<ButtonAttachment> postModAttchment;
    std::unique_ptr<ButtonAttachment> midiActiveAttachment;
    std::unique_ptr<ButtonAttachment> midiHoldAttchment;
    std::unique_ptr<ButtonAttachment> filterActiveAttchment;

    std::unique_ptr<ButtonAttachment> softClipAttchment;
    std::unique_ptr<ButtonAttachment> quantNoiseAttachment;
    std::unique_ptr<ButtonAttachment> aliasingAttchment;

    std::unique_ptr<SliderAttachment> inputGainAttachment;
    std::unique_ptr<SliderAttachment> bitDepthAttachment;
    std::unique_ptr<SliderAttachment> subFactorAttachment;

    std::unique_ptr<ButtonAttachment> sineAttchment;
    std::unique_ptr<ButtonAttachment> sawtoothAttachment;
    std::unique_ptr<ButtonAttachment> triangularAttchment;
    std::unique_ptr<ButtonAttachment> squareAttchment;

    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> amountAttachment;
    std::unique_ptr<SliderAttachment> cutoffAttachment;

    std::unique_ptr<SliderAttachment> drywetAttchment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> bitCrusher_label;
    std::unique_ptr<juce::Label> ringMod_label;
    std::unique_ptr<juce::ToggleButton> postMod_toggle;
    std::unique_ptr<juce::Slider> inputGain_slider;
    std::unique_ptr<juce::ToggleButton> midiActive_toggle;
    std::unique_ptr<juce::ToggleButton> midiHold_toggle;
    std::unique_ptr<juce::Slider> rate_slider;
    std::unique_ptr<juce::TextButton> sine_button;
    std::unique_ptr<juce::GroupComponent> waveform_group;
    std::unique_ptr<juce::ToggleButton> filterActive_toggle;
    std::unique_ptr<juce::Slider> cutoff_slider;
    std::unique_ptr<juce::Slider> dryWet_slider;
    std::unique_ptr<juce::TextButton> saw_button;
    std::unique_ptr<juce::TextButton> triang_button;
    std::unique_ptr<juce::TextButton> square_button;
    std::unique_ptr<juce::Slider> amt_slider;
    std::unique_ptr<juce::TextButton> softClip_button;
    std::unique_ptr<juce::GroupComponent> degtype_group;
    std::unique_ptr<juce::TextButton> quantNoise_button;
    std::unique_ptr<juce::TextButton> alias_button;
    std::unique_ptr<juce::Label> inputGain_label;
    std::unique_ptr<juce::Label> amt_label;
    std::unique_ptr<juce::Label> cutoff_label;
    std::unique_ptr<juce::Label> rate_label;
    std::unique_ptr<juce::Label> drywet_label;
    std::unique_ptr<juce::Label> bitDepth_label;
    std::unique_ptr<juce::Label> subFactor_label;
    std::unique_ptr<juce::Slider> bitDepth_slider;
    std::unique_ptr<juce::Slider> subFactor_slider;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Path internalPath3;
    juce::Path internalPath4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

