#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class Multiplier : public AudioProcessorValueTreeState::Listener
{
public:
	Multiplier()
	{
		modulationAmount.setCurrentAndTargetValue(DEFAULT_AMOUNT);
	};
	~Multiplier() {};

	void prepareToPlay(double sampleRate)
	{
		modulationAmount.reset(sampleRate, RATE_SMOOTHING_TIME);
	}


	void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& modulator)
	{
		const auto numSamples = buffer.getNumSamples();
		const auto numChannels = buffer.getNumChannels();
		const auto numModChannels = modulator.getNumChannels();

		applyAmountGain(modulator, numModChannels, numSamples);


		for (int ch = numChannels; --ch >= 0;) //(int ch = 0; ch < numChannels; ++ch)
		{
			const auto modCh = jmin(ch, numModChannels - 1);
			FloatVectorOperations::multiply(buffer.getWritePointer(ch), modulator.getReadPointer(modCh), numSamples);
		}
	}

	void applyAmountGain(AudioBuffer<float>& modulator, int numModChannels, int numSamples)
	{
		for (int ch = numModChannels; --ch >= 0;)
		{
			auto* modData = modulator.getWritePointer(ch);
			modulationAmount.applyGain(modData, numSamples);
		}
	}
private:

	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_AMOUNT)
			modulationAmount.setCurrentAndTargetValue(newValue);
	}

	SmoothedValue<float, ValueSmoothingTypes::Linear> modulationAmount;
};