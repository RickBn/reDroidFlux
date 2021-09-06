#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiRingAudioProcessor::MidiRingAudioProcessor(): 
    AudioProcessor(BusesProperties()
        .withInput("Input",   juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        ),
    parameters(*this, nullptr, Identifier("Parameters"), createParametersLayout())
{
    parameters.addParameterListener(NAME_MIDI_ACTIVE, this);
    parameters.addParameterListener(NAME_POST_MOD, this);

    parameters.addParameterListener(NAME_DRYWET, &dryWet);

    parameters.addParameterListener(NAME_MIDI_HOLD, &midiHandler);

    parameters.addParameterListener(NAME_DEG_TYPE, &bitCrusher);
    parameters.addParameterListener(NAME_INPUT_GAIN, &bitCrusher);
    parameters.addParameterListener(NAME_BIT_DEPTH, &bitCrusher);
    parameters.addParameterListener(NAME_SUB_FACTOR, &bitCrusher);

    parameters.addParameterListener(NAME_RATE, &modSignal);
    parameters.addParameterListener(NAME_WAVEFORM, &modSignal);
    parameters.addParameterListener(NAME_FILTER_ACTIVE, &modSignal);
    parameters.addParameterListener(NAME_CUTOFF, &modSignal);

    parameters.addParameterListener(NAME_AMOUNT, &multiplier);

}

MidiRingAudioProcessor::~MidiRingAudioProcessor()
{
}

//==============================================================================
const juce::String MidiRingAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiRingAudioProcessor::acceptsMidi() const
{
    return true;
}

bool MidiRingAudioProcessor::producesMidi() const
{
    return false;
}

bool MidiRingAudioProcessor::isMidiEffect() const
{
    return false;
}

//==============================================================================
void MidiRingAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numOutputChannels = getTotalNumOutputChannels();

    dryWet.prepareToPlay(numOutputChannels, samplesPerBlock);

    bitCrusher.prepareToPlay(sampleRate);
    modSignal.prepareToPlay(sampleRate);
    midiHandler.prepareToPlay(sampleRate);
    multiplier.prepareToPlay(sampleRate);

    modulator.setSize(numOutputChannels, samplesPerBlock);

}

void MidiRingAudioProcessor::releaseResources()
{
    modulator.setSize(0, 0);
    dryWet.releaseResources();
}

bool MidiRingAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void MidiRingAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == NAME_MIDI_ACTIVE)
        midiActive = newValue;

    if (paramID == NAME_POST_MOD)
        postMod = newValue;

}

void MidiRingAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    const auto numSamples = buffer.getNumSamples();

    if (midiActive)
        midiHandler.processBlock(midiMessages, modSignal);

    modSignal.getNextAudioBlock(modulator, numSamples);

    dryWet.storeFrom(buffer);

    if (postMod) 
    {
        multiplier.processBlock(buffer, modulator);
        bitCrusher.processBlock(buffer, numSamples);
    }
    
    else 
    {
        bitCrusher.processBlock(buffer, numSamples);
        multiplier.processBlock(buffer, modulator);
    }

    dryWet.mergeTo(buffer);
}

//==============================================================================
bool MidiRingAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* MidiRingAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

//==============================================================================
void MidiRingAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MidiRingAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiRingAudioProcessor();
}
