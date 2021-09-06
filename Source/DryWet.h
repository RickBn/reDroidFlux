#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class DryWet : public AudioProcessorValueTreeState::Listener
{
public:
	DryWet()
	{
		updateInternalState(DEFAULT_DRYWET);
	};
	~DryWet() {};

	void prepareToPlay(const int numOutputChannels, const int maxSamplesPerBlock)
	{
		drySignal.setSize(numOutputChannels, maxSamplesPerBlock);
	}

	void releaseResources()
	{
		drySignal.setSize(0, 0);
	}

	void storeFrom(const AudioBuffer<float>& inputSignal)
	{
		const auto numSamples = inputSignal.getNumSamples();
		const auto numInputChannels = inputSignal.getNumChannels();

		for (int ch = numInputChannels; --ch >= 0;) {
			const auto sourceCh = jmin(ch, numInputChannels - 1); //In case of mono in, stereo out
			drySignal.copyFrom(ch, 0, inputSignal, sourceCh, 0, numSamples);
		}
	}

	void mergeTo(AudioBuffer<float>& outputSignal)
	{
		const auto numSamples = outputSignal.getNumSamples();

		if (needSmoothing)
		{
			outputSignal.applyGainRamp(0, numSamples, oldWetGain, wetGain);

			for (int ch = outputSignal.getNumChannels(); --ch >= 0;) {
				outputSignal.addFromWithRamp(ch, 0, drySignal.getReadPointer(ch), numSamples, oldDryGain, dryGain);
			}

			needSmoothing = false;
		}

		else
		{
			outputSignal.applyGain(0, numSamples, wetGain);

			for (int ch = outputSignal.getNumChannels(); --ch >= 0;)
				outputSignal.addFrom(ch, 0, drySignal, ch, 0, numSamples, dryGain);
		}
	}

private:
	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_DRYWET)
			updateInternalState(newValue);
	}

	void updateInternalState(float newValue)
	{
		oldDryGain = dryGain;
		oldWetGain = wetGain;

		dryGain = sqrt(1.0f - newValue);
		wetGain = sqrt(newValue);

		needSmoothing = true;
	}

	AudioBuffer<float> drySignal;

	float dryGain = 0.0f;
	float wetGain = 0.0f;
	float oldDryGain, oldWetGain = 0.0f;
	bool  needSmoothing = true;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};