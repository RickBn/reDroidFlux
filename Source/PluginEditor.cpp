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

//[Headers] You can add your own extra header files here...
#include "Parameters.h"
#include "PluginProcessor.h"
#include "DryWet.h"
#include "BitCrusher.h"
#include "Oscillator.h"
#include "MidiHandler.h"
#include "Multiplier.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (MidiRingAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    bitCrusher_label.reset (new juce::Label ("BitCrusher",
                                             TRANS("BitCrusher\n")));
    addAndMakeVisible (bitCrusher_label.get());
    bitCrusher_label->setFont (juce::Font ("Unispace", 22.40f, juce::Font::plain));
    bitCrusher_label->setJustificationType (juce::Justification::centred);
    bitCrusher_label->setEditable (false, false, false);
    bitCrusher_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    bitCrusher_label->setColour (juce::Label::outlineColourId, juce::Colour (0x00b469ce));
    bitCrusher_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    bitCrusher_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    bitCrusher_label->setBounds (56, 8, 128, 40);

    ringMod_label.reset (new juce::Label ("RingMod",
                                          TRANS("Ring Modulator\n")));
    addAndMakeVisible (ringMod_label.get());
    ringMod_label->setFont (juce::Font ("Unispace", 22.40f, juce::Font::plain));
    ringMod_label->setJustificationType (juce::Justification::centred);
    ringMod_label->setEditable (false, false, false);
    ringMod_label->setColour (juce::Label::textColourId, juce::Colour (0xffb989d8));
    ringMod_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    ringMod_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    ringMod_label->setBounds (344, 8, 176, 40);

    postMod_toggle.reset (new juce::ToggleButton ("PostModulation"));
    addAndMakeVisible (postMod_toggle.get());
    postMod_toggle->setButtonText (TRANS("Post modulation"));
    postMod_toggle->setColour (juce::ToggleButton::textColourId, juce::Colour (0xffeea3ff));

    postMod_toggle->setBounds (56, 368, 144, 24);

    inputGain_slider.reset (new juce::Slider ("InputGain"));
    addAndMakeVisible (inputGain_slider.get());
    inputGain_slider->setRange (0, 10, 0);
    inputGain_slider->setSliderStyle (juce::Slider::Rotary);
    inputGain_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    inputGain_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    inputGain_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    inputGain_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    inputGain_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    inputGain_slider->setBounds (72, 256, 96, 96);

    midiActive_toggle.reset (new juce::ToggleButton ("MidiActive"));
    addAndMakeVisible (midiActive_toggle.get());
    midiActive_toggle->setButtonText (TRANS("Midi-in active"));
    midiActive_toggle->addListener (this);
    midiActive_toggle->setColour (juce::ToggleButton::textColourId, juce::Colour (0xffeea3ff));

    midiActive_toggle->setBounds (296, 80, 120, 24);

    midiHold_toggle.reset (new juce::ToggleButton ("MidiHold"));
    addAndMakeVisible (midiHold_toggle.get());
    midiHold_toggle->setButtonText (TRANS("Note-on hold"));
    midiHold_toggle->setColour (juce::ToggleButton::textColourId, juce::Colour (0xffeea3ff));

    midiHold_toggle->setBounds (296, 112, 112, 24);

    rate_slider.reset (new juce::Slider ("OscRate"));
    addAndMakeVisible (rate_slider.get());
    rate_slider->setExplicitFocusOrder (1);
    rate_slider->setRange (0, 10, 0);
    rate_slider->setSliderStyle (juce::Slider::Rotary);
    rate_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    rate_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    rate_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    rate_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    rate_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    rate_slider->setBounds (304, 144, 96, 96);

    sine_button.reset (new juce::TextButton ("Sine"));
    addAndMakeVisible (sine_button.get());
    sine_button->setRadioGroupId (2);
    sine_button->addListener (this);
    sine_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    sine_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xffcc73d7));

    sine_button->setBounds (472, 88, 112, 24);

    waveform_group.reset (new juce::GroupComponent ("Waveform",
                                                    TRANS("Waveform")));
    addAndMakeVisible (waveform_group.get());
    waveform_group->setExplicitFocusOrder (1);
    waveform_group->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff00ffd7));
    waveform_group->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffc4a5e9));

    waveform_group->setBounds (464, 64, 128, 152);

    filterActive_toggle.reset (new juce::ToggleButton ("FilterActive"));
    addAndMakeVisible (filterActive_toggle.get());
    filterActive_toggle->setButtonText (TRANS("Waveform smoothing"));
    filterActive_toggle->addListener (this);
    filterActive_toggle->setColour (juce::ToggleButton::textColourId, juce::Colour (0xffe49be3));

    filterActive_toggle->setBounds (272, 368, 160, 24);

    cutoff_slider.reset (new juce::Slider ("Cutoff"));
    addAndMakeVisible (cutoff_slider.get());
    cutoff_slider->setRange (0, 10, 0);
    cutoff_slider->setSliderStyle (juce::Slider::Rotary);
    cutoff_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    cutoff_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    cutoff_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    cutoff_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    cutoff_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    cutoff_slider->setBounds (480, 288, 96, 96);

    dryWet_slider.reset (new juce::Slider ("DryWet"));
    addAndMakeVisible (dryWet_slider.get());
    dryWet_slider->setRange (0, 10, 0);
    dryWet_slider->setSliderStyle (juce::Slider::LinearVertical);
    dryWet_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    dryWet_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    dryWet_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    dryWet_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    dryWet_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    dryWet_slider->setBounds (624, 80, 72, 304);

    saw_button.reset (new juce::TextButton ("Sawtooth"));
    addAndMakeVisible (saw_button.get());
    saw_button->setRadioGroupId (2);
    saw_button->addListener (this);
    saw_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    saw_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xffcc73d7));

    saw_button->setBounds (472, 120, 112, 24);

    triang_button.reset (new juce::TextButton ("Triangular"));
    addAndMakeVisible (triang_button.get());
    triang_button->setRadioGroupId (2);
    triang_button->addListener (this);
    triang_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    triang_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xffcc73d7));

    triang_button->setBounds (472, 152, 112, 24);

    square_button.reset (new juce::TextButton ("Square"));
    addAndMakeVisible (square_button.get());
    square_button->setRadioGroupId (2);
    square_button->addListener (this);
    square_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    square_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xffcc73d7));

    square_button->setBounds (472, 184, 112, 24);

    amt_slider.reset (new juce::Slider ("OscAmt"));
    addAndMakeVisible (amt_slider.get());
    amt_slider->setRange (0, 10, 0);
    amt_slider->setSliderStyle (juce::Slider::Rotary);
    amt_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    amt_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    amt_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    amt_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    amt_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    amt_slider->setBounds (304, 256, 96, 96);

    hardClip_button.reset (new juce::TextButton ("HardClipping"));
    addAndMakeVisible (hardClip_button.get());
    hardClip_button->setButtonText (TRANS("Hard clipping"));
    hardClip_button->setRadioGroupId (1);
    hardClip_button->addListener (this);
    hardClip_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    hardClip_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xfff8bbff));

    hardClip_button->setBounds (56, 80, 128, 24);

    degtype_group.reset (new juce::GroupComponent ("DegType",
                                                   TRANS("Degradation type")));
    addAndMakeVisible (degtype_group.get());
    degtype_group->setExplicitFocusOrder (1);
    degtype_group->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff00eebf));
    degtype_group->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffc4a5e9));

    degtype_group->setBounds (48, 64, 144, 112);

    quantNoise_button.reset (new juce::TextButton ("QuantizationNoise"));
    addAndMakeVisible (quantNoise_button.get());
    quantNoise_button->setButtonText (TRANS("Quantization noise"));
    quantNoise_button->setRadioGroupId (1);
    quantNoise_button->addListener (this);
    quantNoise_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    quantNoise_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xfff6c5fc));

    quantNoise_button->setBounds (56, 112, 128, 24);

    alias_button.reset (new juce::TextButton ("Aliasing"));
    addAndMakeVisible (alias_button.get());
    alias_button->setRadioGroupId (1);
    alias_button->addListener (this);
    alias_button->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff4a0c3c));
    alias_button->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xfffbd7ff));

    alias_button->setBounds (56, 144, 128, 24);

    inputGain_label.reset (new juce::Label ("ig_lab",
                                            TRANS("Input gain")));
    addAndMakeVisible (inputGain_label.get());
    inputGain_label->setExplicitFocusOrder (1);
    inputGain_label->setFont (juce::Font ("Unispace", 12.30f, juce::Font::plain));
    inputGain_label->setJustificationType (juce::Justification::centredTop);
    inputGain_label->setEditable (false, false, false);
    inputGain_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    inputGain_label->setColour (juce::Label::outlineColourId, juce::Colour (0x0022e2ad));
    inputGain_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    inputGain_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    inputGain_label->setBounds (64, 248, 112, 16);

    amt_label.reset (new juce::Label ("amt_lab",
                                      TRANS("Mod. amount")));
    addAndMakeVisible (amt_label.get());
    amt_label->setExplicitFocusOrder (1);
    amt_label->setFont (juce::Font ("Unispace", 12.30f, juce::Font::plain));
    amt_label->setJustificationType (juce::Justification::centred);
    amt_label->setEditable (false, false, false);
    amt_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    amt_label->setColour (juce::Label::outlineColourId, juce::Colour (0x001ceebc));
    amt_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    amt_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    amt_label->setBounds (304, 248, 96, 16);

    cutoff_label.reset (new juce::Label ("cut_lab",
                                         TRANS("Smooth factor")));
    addAndMakeVisible (cutoff_label.get());
    cutoff_label->setFont (juce::Font ("Unispace", 14.80f, juce::Font::plain));
    cutoff_label->setJustificationType (juce::Justification::centred);
    cutoff_label->setEditable (false, false, false);
    cutoff_label->setColour (juce::Label::textColourId, juce::Colour (0xffb989d8));
    cutoff_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    cutoff_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    cutoff_label->setBounds (472, 264, 112, 32);

    rate_label.reset (new juce::Label ("rate_lab",
                                       TRANS("Rate")));
    addAndMakeVisible (rate_label.get());
    rate_label->setExplicitFocusOrder (2);
    rate_label->setFont (juce::Font ("Unispace", 12.30f, juce::Font::plain));
    rate_label->setJustificationType (juce::Justification::centred);
    rate_label->setEditable (false, false, false);
    rate_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    rate_label->setColour (juce::Label::outlineColourId, juce::Colour (0x001ceebc));
    rate_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    rate_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    rate_label->setBounds (304, 136, 96, 16);

    drywet_label.reset (new juce::Label ("dw_lab",
                                         TRANS("Mix")));
    addAndMakeVisible (drywet_label.get());
    drywet_label->setFont (juce::Font ("Unispace", 22.40f, juce::Font::plain));
    drywet_label->setJustificationType (juce::Justification::centred);
    drywet_label->setEditable (false, false, false);
    drywet_label->setColour (juce::Label::textColourId, juce::Colour (0xffb989d8));
    drywet_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    drywet_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    drywet_label->setBounds (624, 8, 72, 40);

    bitDepth_label.reset (new juce::Label ("bd_lab",
                                           TRANS("Bit Depth")));
    addAndMakeVisible (bitDepth_label.get());
    bitDepth_label->setFont (juce::Font ("Unispace", 12.30f, juce::Font::plain));
    bitDepth_label->setJustificationType (juce::Justification::centredTop);
    bitDepth_label->setEditable (false, false, false);
    bitDepth_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    bitDepth_label->setColour (juce::Label::outlineColourId, juce::Colour (0x0022e2ad));
    bitDepth_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    bitDepth_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    bitDepth_label->setBounds (64, 248, 112, 16);

    subFactor_label.reset (new juce::Label ("sf_lab",
                                            TRANS("Subsampling factor")));
    addAndMakeVisible (subFactor_label.get());
    subFactor_label->setExplicitFocusOrder (1);
    subFactor_label->setFont (juce::Font ("Unispace", 12.30f, juce::Font::plain));
    subFactor_label->setJustificationType (juce::Justification::centredTop);
    subFactor_label->setEditable (false, false, false);
    subFactor_label->setColour (juce::Label::textColourId, juce::Colour (0xffc9a4e1));
    subFactor_label->setColour (juce::Label::outlineColourId, juce::Colour (0x0022e2ad));
    subFactor_label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    subFactor_label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    subFactor_label->setBounds (48, 248, 144, 16);

    bitDepth_slider.reset (new juce::Slider ("BitDepth"));
    addAndMakeVisible (bitDepth_slider.get());
    bitDepth_slider->setRange (0, 10, 0);
    bitDepth_slider->setSliderStyle (juce::Slider::Rotary);
    bitDepth_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    bitDepth_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    bitDepth_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    bitDepth_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    bitDepth_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    bitDepth_slider->setBounds (72, 256, 96, 96);

    subFactor_slider.reset (new juce::Slider ("SubFactor"));
    addAndMakeVisible (subFactor_slider.get());
    subFactor_slider->setRange (0, 10, 0);
    subFactor_slider->setSliderStyle (juce::Slider::Rotary);
    subFactor_slider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    subFactor_slider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffff66d9));
    subFactor_slider->setColour (juce::Slider::trackColourId, juce::Colour (0xffdda3f7));
    subFactor_slider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xffbd76d7));
    subFactor_slider->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff3e1146));

    subFactor_slider->setBounds (72, 256, 96, 96);

    internalPath1.startNewSubPath (528.0f, 232.0f);
    internalPath1.lineTo (610.0f, 394.0f);
    internalPath1.lineTo (446.0f, 394.0f);
    internalPath1.closeSubPath();

    internalPath2.startNewSubPath (289.0f, 76.0f);
    internalPath2.lineTo (418.0f, 76.0f);
    internalPath2.lineTo (418.0f, 354.0f);
    internalPath2.lineTo (289.0f, 354.0f);
    internalPath2.closeSubPath();

    internalPath3.startNewSubPath (62.0f, 246.0f);
    internalPath3.lineTo (178.0f, 246.0f);
    internalPath3.lineTo (178.0f, 356.0f);
    internalPath3.lineTo (62.0f, 356.0f);
    internalPath3.closeSubPath();

    internalPath4.startNewSubPath (416.0f, 246.0f);
    internalPath4.lineTo (288.0f, 246.0f);
    internalPath4.closeSubPath();


    //[UserPreSize]
    bitDepth_label->setVisible(false);
    bitDepth_slider->setVisible(false);

    subFactor_label->setVisible(false);
    subFactor_slider->setVisible(false);

    cutoff_slider->setEnabled(false);

    postModAttchment.reset(new ButtonAttachment(valueTreeState, NAME_POST_MOD, *postMod_toggle));
    midiActiveAttachment.reset(new ButtonAttachment(valueTreeState, NAME_MIDI_ACTIVE, *midiActive_toggle));
    midiHoldAttchment.reset(new ButtonAttachment(valueTreeState, NAME_MIDI_HOLD, *midiHold_toggle));
    filterActiveAttchment.reset(new ButtonAttachment(valueTreeState, NAME_FILTER_ACTIVE, *filterActive_toggle));

    inputGainAttachment.reset(new SliderAttachment(valueTreeState, NAME_INPUT_GAIN, *inputGain_slider));
    bitDepthAttachment.reset(new SliderAttachment(valueTreeState, NAME_BIT_DEPTH, *bitDepth_slider));
    subFactorAttachment.reset(new SliderAttachment(valueTreeState, NAME_SUB_FACTOR, *subFactor_slider));

    rateAttachment.reset(new SliderAttachment(valueTreeState, NAME_RATE, *rate_slider));
    amountAttachment.reset(new SliderAttachment(valueTreeState, NAME_AMOUNT, *amt_slider));
    cutoffAttachment.reset(new SliderAttachment(valueTreeState, NAME_CUTOFF, *cutoff_slider));

    drywetAttchment.reset(new SliderAttachment(valueTreeState, NAME_DRYWET, *dryWet_slider));
    //[/UserPreSize]

    setSize (700, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    postModAttchment = nullptr;
    midiActiveAttachment = nullptr;
    midiHoldAttchment = nullptr;
    filterActiveAttchment = nullptr;

    hardClipAttchment = nullptr;
    quantNoiseAttachment = nullptr;
    aliasingAttchment = nullptr;

    inputGainAttachment = nullptr;
    bitDepthAttachment = nullptr;
    subFactorAttachment = nullptr;

    sineAttchment = nullptr;
    sawtoothAttachment = nullptr;
    triangularAttchment = nullptr;
    squareAttchment = nullptr;

    rateAttachment = nullptr;
    amountAttachment = nullptr;
    cutoffAttachment = nullptr;

    drywetAttchment = nullptr;
    //[/Destructor_pre]

    bitCrusher_label = nullptr;
    ringMod_label = nullptr;
    postMod_toggle = nullptr;
    inputGain_slider = nullptr;
    midiActive_toggle = nullptr;
    midiHold_toggle = nullptr;
    rate_slider = nullptr;
    sine_button = nullptr;
    waveform_group = nullptr;
    filterActive_toggle = nullptr;
    cutoff_slider = nullptr;
    dryWet_slider = nullptr;
    saw_button = nullptr;
    triang_button = nullptr;
    square_button = nullptr;
    amt_slider = nullptr;
    hardClip_button = nullptr;
    degtype_group = nullptr;
    quantNoise_button = nullptr;
    alias_button = nullptr;
    inputGain_label = nullptr;
    amt_label = nullptr;
    cutoff_label = nullptr;
    rate_label = nullptr;
    drywet_label = nullptr;
    bitDepth_label = nullptr;
    subFactor_label = nullptr;
    bitDepth_slider = nullptr;
    subFactor_slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::black);

    {
        int x = 243, y = -2, width = 2, height = 402;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 619, y = -2, width = 2, height = 402;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 698, y = 0, width = 4, height = 402;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 0, width = 2, height = 402;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 0, width = 704, height = 2;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = -5, y = 398, width = 704, height = 2;
        juce::Colour fillColour = juce::Colour (0xffd59aff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        float x = 0, y = 0;
        juce::Colour strokeColour = juce::Colour (0x582aa584);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.strokePath (internalPath1, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        juce::Colour strokeColour = juce::Colour (0x582aa584);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.strokePath (internalPath2, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        juce::Colour strokeColour = juce::Colour (0x582aa584);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.strokePath (internalPath3, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        juce::Colour strokeColour = juce::Colour (0x582aa584);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.strokePath (internalPath4, juce::PathStrokeType (5.000f), juce::AffineTransform::translation(x, y));
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == midiActive_toggle.get())
    {
        //[UserButtonCode_midiActive_toggle] -- add your button handler code here..
        if (buttonThatWasClicked->getToggleState())
        {
            rate_label->setVisible(false);
            rate_slider->setVisible(false);
            midiHold_toggle->setVisible(true);
        }

        else
        {
            rate_label->setVisible(true);
            rate_slider->setVisible(true);
            midiHold_toggle->setVisible(false);
        }
        //[/UserButtonCode_midiActive_toggle]
    }
    else if (buttonThatWasClicked == sine_button.get())
    {
        //[UserButtonCode_sine_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_WAVEFORM)->setValueNotifyingHost(0.0f);
        //[/UserButtonCode_sine_button]
    }
    else if (buttonThatWasClicked == filterActive_toggle.get())
    {
        //[UserButtonCode_filterActive_toggle] -- add your button handler code here..
        if (buttonThatWasClicked->getToggleState())
        {
            cutoff_slider->setEnabled(true);
        }

        else
        {
            cutoff_slider->setEnabled(false);
        }
        //[/UserButtonCode_filterActive_toggle]
    }
    else if (buttonThatWasClicked == saw_button.get())
    {
        //[UserButtonCode_saw_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_WAVEFORM)->setValueNotifyingHost(0.25f);
        //[/UserButtonCode_saw_button]
    }
    else if (buttonThatWasClicked == triang_button.get())
    {
        //[UserButtonCode_triang_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_WAVEFORM)->setValueNotifyingHost(0.5f);
        //[/UserButtonCode_triang_button]
    }
    else if (buttonThatWasClicked == square_button.get())
    {
        //[UserButtonCode_square_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_WAVEFORM)->setValueNotifyingHost(1.0f);
        //[/UserButtonCode_square_button]
    }
    else if (buttonThatWasClicked == hardClip_button.get())
    {
        //[UserButtonCode_hardClip_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_DEG_TYPE)->setValueNotifyingHost(0.0f);

        inputGain_label->setVisible(true);
        inputGain_slider->setVisible(true);

        bitDepth_label->setVisible(false);
        bitDepth_slider->setVisible(false);

        subFactor_label->setVisible(false);
        subFactor_slider->setVisible(false);

        //[/UserButtonCode_hardClip_button]
    }
    else if (buttonThatWasClicked == quantNoise_button.get())
    {
        //[UserButtonCode_quantNoise_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_DEG_TYPE)->setValueNotifyingHost(0.5f);

        inputGain_label->setVisible(false);
        inputGain_slider->setVisible(false);

        bitDepth_label->setVisible(true);
        bitDepth_slider->setVisible(true);

        subFactor_label->setVisible(false);
        subFactor_slider->setVisible(false);
        //[/UserButtonCode_quantNoise_button]
    }
    else if (buttonThatWasClicked == alias_button.get())
    {
        //[UserButtonCode_alias_button] -- add your button handler code here..
        valueTreeState.getParameter(NAME_DEG_TYPE)->setValueNotifyingHost(1.0f);

        inputGain_label->setVisible(false);
        inputGain_slider->setVisible(false);

        bitDepth_label->setVisible(false);
        bitDepth_slider->setVisible(false);

        subFactor_label->setVisible(true);
        subFactor_slider->setVisible(true);
        //[/UserButtonCode_alias_button]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="MidiRingAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor (&amp;p), audioProcessor (p), valueTreeState(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="700" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="243 -2 2 402" fill="solid: ffd59aff" hasStroke="0"/>
    <RECT pos="619 -2 2 402" fill="solid: ffd59aff" hasStroke="0"/>
    <RECT pos="698 0 4 402" fill="solid: ffd59aff" hasStroke="0"/>
    <RECT pos="0 0 2 402" fill="solid: ffd59aff" hasStroke="0"/>
    <RECT pos="0 0 704 2" fill="solid: ffd59aff" hasStroke="0"/>
    <RECT pos="-5 398 704 2" fill="solid: ffd59aff" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: 6aa52a" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: 582aa584" nonZeroWinding="1">s 528 232 l 610 394 l 446 394 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 6aa52a" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: 582aa584" nonZeroWinding="1">s 289 76 l 418 76 l 418 354 l 289 354 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 6aa52a" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: 582aa584" nonZeroWinding="1">s 62 246 l 178 246 l 178 356 l 62 356 x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 6aa52a" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: 582aa584" nonZeroWinding="1">s 416 246 l 288 246 x</PATH>
  </BACKGROUND>
  <LABEL name="BitCrusher" id="7c52afd46d0cc47" memberName="bitCrusher_label"
         virtualName="" explicitFocusOrder="0" pos="56 8 128 40" textCol="ffc9a4e1"
         outlineCol="b469ce" edTextCol="ff000000" edBkgCol="0" labelText="BitCrusher&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="22.4" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="RingMod" id="512f86cf414d8a40" memberName="ringMod_label"
         virtualName="" explicitFocusOrder="0" pos="344 8 176 40" textCol="ffb989d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Ring Modulator&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="22.4" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <TOGGLEBUTTON name="PostModulation" id="379ee275954699c3" memberName="postMod_toggle"
                virtualName="" explicitFocusOrder="0" pos="56 368 144 24" txtcol="ffeea3ff"
                buttonText="Post modulation" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="0"/>
  <SLIDER name="InputGain" id="ea925d84de2e83ad" memberName="inputGain_slider"
          virtualName="" explicitFocusOrder="0" pos="72 256 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TOGGLEBUTTON name="MidiActive" id="d5b2e93a108d1629" memberName="midiActive_toggle"
                virtualName="" explicitFocusOrder="0" pos="296 80 120 24" txtcol="ffeea3ff"
                buttonText="Midi-in active" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="MidiHold" id="50436c0d1a29ee1e" memberName="midiHold_toggle"
                virtualName="" explicitFocusOrder="0" pos="296 112 112 24" txtcol="ffeea3ff"
                buttonText="Note-on hold" connectedEdges="0" needsCallback="0"
                radioGroupId="0" state="0"/>
  <SLIDER name="OscRate" id="2814a7426d8848a1" memberName="rate_slider"
          virtualName="" explicitFocusOrder="1" pos="304 144 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TEXTBUTTON name="Sine" id="61c1adde40a5606c" memberName="sine_button" virtualName=""
              explicitFocusOrder="0" pos="472 88 112 24" bgColOff="ff4a0c3c"
              bgColOn="ffcc73d7" buttonText="Sine" connectedEdges="0" needsCallback="1"
              radioGroupId="2"/>
  <GROUPCOMPONENT name="Waveform" id="b6f04560095c5ffb" memberName="waveform_group"
                  virtualName="" explicitFocusOrder="1" pos="464 64 128 152" outlinecol="ff00ffd7"
                  textcol="ffc4a5e9" title="Waveform"/>
  <TOGGLEBUTTON name="FilterActive" id="bf0a9c41a2a97b33" memberName="filterActive_toggle"
                virtualName="" explicitFocusOrder="0" pos="272 368 160 24" txtcol="ffe49be3"
                buttonText="Waveform smoothing" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="Cutoff" id="36429cc049e6176" memberName="cutoff_slider"
          virtualName="" explicitFocusOrder="0" pos="480 288 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="DryWet" id="4e514295e9fa355e" memberName="dryWet_slider"
          virtualName="" explicitFocusOrder="0" pos="624 80 72 304" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TEXTBUTTON name="Sawtooth" id="282f73fdea2cded3" memberName="saw_button"
              virtualName="" explicitFocusOrder="0" pos="472 120 112 24" bgColOff="ff4a0c3c"
              bgColOn="ffcc73d7" buttonText="Sawtooth" connectedEdges="0" needsCallback="1"
              radioGroupId="2"/>
  <TEXTBUTTON name="Triangular" id="95ddec71b986e380" memberName="triang_button"
              virtualName="" explicitFocusOrder="0" pos="472 152 112 24" bgColOff="ff4a0c3c"
              bgColOn="ffcc73d7" buttonText="Triangular" connectedEdges="0"
              needsCallback="1" radioGroupId="2"/>
  <TEXTBUTTON name="Square" id="a1bfdad6fb4d36d0" memberName="square_button"
              virtualName="" explicitFocusOrder="0" pos="472 184 112 24" bgColOff="ff4a0c3c"
              bgColOn="ffcc73d7" buttonText="Square" connectedEdges="0" needsCallback="1"
              radioGroupId="2"/>
  <SLIDER name="OscAmt" id="2edcd86120db0868" memberName="amt_slider" virtualName=""
          explicitFocusOrder="0" pos="304 256 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TEXTBUTTON name="HardClipping" id="da4a8c44e1035d07" memberName="hardClip_button"
              virtualName="" explicitFocusOrder="0" pos="56 80 128 24" bgColOff="ff4a0c3c"
              bgColOn="fff8bbff" buttonText="Hard clipping" connectedEdges="0"
              needsCallback="1" radioGroupId="1"/>
  <GROUPCOMPONENT name="DegType" id="fc421bc790fe9c93" memberName="degtype_group"
                  virtualName="" explicitFocusOrder="1" pos="48 64 144 112" outlinecol="ff00eebf"
                  textcol="ffc4a5e9" title="Degradation type"/>
  <TEXTBUTTON name="QuantizationNoise" id="1f548ba38dd31110" memberName="quantNoise_button"
              virtualName="" explicitFocusOrder="0" pos="56 112 128 24" bgColOff="ff4a0c3c"
              bgColOn="fff6c5fc" buttonText="Quantization noise" connectedEdges="0"
              needsCallback="1" radioGroupId="1"/>
  <TEXTBUTTON name="Aliasing" id="52182daa59fc2df9" memberName="alias_button"
              virtualName="" explicitFocusOrder="0" pos="56 144 128 24" bgColOff="ff4a0c3c"
              bgColOn="fffbd7ff" buttonText="Aliasing" connectedEdges="0" needsCallback="1"
              radioGroupId="1"/>
  <LABEL name="ig_lab" id="7311607608c9ec91" memberName="inputGain_label"
         virtualName="" explicitFocusOrder="1" pos="64 248 112 16" textCol="ffc9a4e1"
         outlineCol="22e2ad" edTextCol="ff000000" edBkgCol="0" labelText="Input gain"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="12.3" kerning="0.0" bold="0" italic="0"
         justification="12"/>
  <LABEL name="amt_lab" id="139280a8178660f9" memberName="amt_label" virtualName=""
         explicitFocusOrder="1" pos="304 248 96 16" textCol="ffc9a4e1"
         outlineCol="1ceebc" edTextCol="ff000000" edBkgCol="0" labelText="Mod. amount"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="12.3" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="cut_lab" id="bdf8329f87615790" memberName="cutoff_label"
         virtualName="" explicitFocusOrder="0" pos="472 264 112 32" textCol="ffb989d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Smooth factor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Unispace"
         fontsize="14.8" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="rate_lab" id="5d9d9d9df7bf86fe" memberName="rate_label"
         virtualName="" explicitFocusOrder="2" pos="304 136 96 16" textCol="ffc9a4e1"
         outlineCol="1ceebc" edTextCol="ff000000" edBkgCol="0" labelText="Rate"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="12.3" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="dw_lab" id="4e0e99d25ba09fd8" memberName="drywet_label"
         virtualName="" explicitFocusOrder="0" pos="624 8 72 40" textCol="ffb989d8"
         edTextCol="ff000000" edBkgCol="0" labelText="Mix" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Unispace"
         fontsize="22.4" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="bd_lab" id="759b8119ffc81c32" memberName="bitDepth_label"
         virtualName="" explicitFocusOrder="0" pos="64 248 112 16" textCol="ffc9a4e1"
         outlineCol="22e2ad" edTextCol="ff000000" edBkgCol="0" labelText="Bit Depth"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="12.3" kerning="0.0" bold="0" italic="0"
         justification="12"/>
  <LABEL name="sf_lab" id="baac07b45a024a7d" memberName="subFactor_label"
         virtualName="" explicitFocusOrder="1" pos="48 248 144 16" textCol="ffc9a4e1"
         outlineCol="22e2ad" edTextCol="ff000000" edBkgCol="0" labelText="Subsampling factor"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Unispace" fontsize="12.3" kerning="0.0" bold="0" italic="0"
         justification="12"/>
  <SLIDER name="BitDepth" id="bb93db1112c1d22f" memberName="bitDepth_slider"
          virtualName="" explicitFocusOrder="0" pos="72 256 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="SubFactor" id="27dfaa99a0c53a54" memberName="subFactor_slider"
          virtualName="" explicitFocusOrder="0" pos="72 256 96 96" thumbcol="ffff66d9"
          trackcol="ffdda3f7" rotarysliderfill="ffbd76d7" rotaryslideroutline="ff3e1146"
          min="0.0" max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

