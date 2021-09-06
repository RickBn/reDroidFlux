#pragma once

#include <JuceHeader.h>
#include "Parameters.h"
#include "DryWet.h"
#include "BitCrusher.h"
#include "Oscillator.h"
#include "MidiHandler.h"
#include "Multiplier.h"

//==============================================================================
/**
*/
class MidiRingAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    MidiRingAudioProcessor();
    ~MidiRingAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override { return 0.0; };

    //==============================================================================
    int getNumPrograms() override { return 1; };
    int getCurrentProgram() override { return 0; };
    void setCurrentProgram(int index) override {};
    const juce::String getProgramName(int index) override { return {}; };
    void changeProgramName(int index, const juce::String& newName) override {};

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    void parameterChanged(const String& paramID, float newValue) override;

    AudioProcessorValueTreeState parameters;

    bool midiActive = DEFAULT_MIDI_ACTIVE;
    bool postMod = DEFAULT_POST_MOD;

    DryWet dryWet;
    BitCrusher bitCrusher;
    Oscillator modSignal;
    AudioBuffer<float> modulator;
    MidiHandler midiHandler;
    Multiplier multiplier;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiRingAudioProcessor)
};
