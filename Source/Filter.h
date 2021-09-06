#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

#define MAX_F 20000.0f

class Filter : public AudioProcessorValueTreeState::Listener
{
public:
	Filter()
	{
		for (int i = 0; i < DEFAULT_NUM_FILTERS; ++i)
			iirFilters.add(new IIRFilter()); // Juce gestisce la distruzione
	}
	~Filter() {}

	void prepareToPlay(double sampleRate)
	{
		sr = sampleRate;

		for (int i = iirFilters.size(); --i >= 0;)
			iirFilters.getUnchecked(i)->reset();

		updateCoefficients();
	}

	void processBlock(AudioBuffer<float>& buffer, const int numSamples)
	{
		for (int ch = buffer.getNumChannels(); --ch >= 0;)
			iirFilters.getUnchecked(ch)->processSamples(buffer.getWritePointer(ch), numSamples);
	}

	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_CUTOFF)
			cutoff_factor = newValue;

		if (paramID == NAME_RATE)
			cutoff_freq = newValue;

		//if (paramID == NAME_Q)
		//	quality = newValue;

		updateCoefficients();
	}

private:
	void updateCoefficients()
	{
		float frequency = cutoff_freq + ((MAX_F - cutoff_freq) * cutoff_factor);
		const IIRCoefficients coefficients = IIRCoefficients::makeLowPass(sr,  frequency, quality);

		for (int i = iirFilters.size(); --i >= 0;)
			iirFilters.getUnchecked(i)->setCoefficients(coefficients);
	}

	double sr = 44100.0;

	float cutoff_factor = DEFAULT_CUTOFF;
	float cutoff_freq = MAX_F;
	float quality = DEFAULT_Q;

	OwnedArray<IIRFilter> iirFilters;
};