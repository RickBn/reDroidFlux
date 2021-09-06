#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "Filter.h"

class Oscillator : public AudioProcessorValueTreeState::Listener
{
public:
	Oscillator()
	{
		frequency.setCurrentAndTargetValue(DEFAULT_RATE);
	}
	~Oscillator() {};

	void prepareToPlay(double sampleRate)
	{
		sr = sampleRate;
		frequency.reset(sr, RATE_SMOOTHING_TIME);

		lowPass.prepareToPlay(sampleRate);
	}

	void getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples)
	{
		const auto numChannels = buffer.getNumChannels();
		auto** bufferData = buffer.getArrayOfWritePointers();

		for (int sample = 0; sample < numSamples; ++sample)
		{
			const float sampleValue = oscActive ? getNextAudioSample() : 0;

			for (int ch = numChannels; --ch >= 0;)
			{
				bufferData[ch][sample] = sampleValue;
			}
		}

		if (filterActive)
			lowPass.processBlock(buffer, numSamples);
	}

	float getNextAudioSample()
	{
		float sampleValue;

		switch (waveform)
		{
		case 0:
			// Sinusoide
			sampleValue = sin(2.0f * float_Pi * normalizedPhaseValue);
			break;

		case 1:
			// Sawtooth
			sampleValue = 2.0f * normalizedPhaseValue - 1.0f;
			break;

		case 2:
			// Triangolare
			sampleValue = 4.0f * abs(normalizedPhaseValue - 0.5f) - 1.0f;
			break;

		case 3:
			// Square
			sampleValue = (normalizedPhaseValue >= 0.5) - (normalizedPhaseValue < 0.5);
			break;

		default:
			sampleValue = 0.0f;
		}

		const float phaseIncrement = frequency.getNextValue() / sr;

		normalizedPhaseValue += phaseIncrement;
		normalizedPhaseValue -= static_cast<int>(normalizedPhaseValue);

		return sampleValue;
	}

	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_RATE) {
			frequency.setTargetValue(newValue);
			lowPass.parameterChanged(paramID, newValue);
		}

		if (paramID == NAME_WAVEFORM) 
			waveform = newValue;

		if (paramID == NAME_STEREO_FREQ)
			stereoFreq = newValue;

		if (paramID == NAME_OSC_ACTIVE)
			oscActive = newValue > 0.5f;

		if (paramID == NAME_FILTER_ACTIVE)
			filterActive = newValue > 0.5f;

		if (paramID == NAME_CUTOFF)
			lowPass.parameterChanged(paramID, newValue);
	}

protected:

	double sr = 44100.0;
	float normalizedPhaseValue = 0.0f;

	int waveform = DEFAULT_WAVEFORM;
	float stereoFreq = DEFAULT_STEREO_FREQ;

	bool oscActive = DEFAULT_OSC_ACTIVE;

	SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequency;

	Filter lowPass;
	bool filterActive = DEFAULT_FILTER_ACTIVE;

};