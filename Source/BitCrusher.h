#pragma once

#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class BitCrusher : public AudioProcessorValueTreeState::Listener
{
public:
	BitCrusher() {};
	~BitCrusher() {};

	void prepareToPlay(double sampleRate)
	{
		sr = sampleRate;
	}

	void processBlock(AudioBuffer<float>& buffer, const int numSamples) {

		const auto numChannels = buffer.getNumChannels();

		for (int sample = 0; sample < numSamples; ++sample)
		{
			for (int ch = numChannels; --ch >= 0;)
			{
				const float sampleValue = getNextAudioSample(buffer.getSample(ch, sample));
				buffer.setSample(ch, sample, sampleValue);
			}
		}
	}

	float getNextAudioSample(float sample)
	{
		float sampleValue;

		switch (degradationType)
		{
		case 0:
			// Soft clipping
			sampleValue = tanh(sample * inputGain) / sqrt(inputGain);
			break;

		case 1:
			// Quantization noise
			sampleValue = roundToInt(sample * bits) / bits;
			break;

		case 2:			
		{
			// Aliasing
			subsamplingCounter++;
			subsampValue = (subsamplingCounter % subsamplingFactor) ? subsampValue : sample;
			sampleValue = subsampValue;
			break;
		}
		default:
			sampleValue = 0.0f;
		}

		return sampleValue;
	}

private:

	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_DEG_TYPE)
			degradationType = newValue;

		if (paramID == NAME_INPUT_GAIN)
			inputGain = newValue;

		if (paramID == NAME_BIT_DEPTH)
			bits = pow(2, newValue - 1);

		if (paramID == NAME_SUB_FACTOR)
			subsamplingFactor = newValue;
	}
	
	int degradationType = DEFAULT_DEG_TYPE;

	float inputGain = DEFAULT_INPUT_GAIN;

	double bits = pow(2, DAFAULT_BIT_DEPTH - 1);

	int subsamplingFactor = DEFAULT_SUB_FACTOR;

	double sr = 44100.0;

	unsigned int subsamplingCounter = 0;
	float subsampValue = 0.0f;

};