#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "Oscillator.h"

class MidiHandler : public AudioProcessorValueTreeState::Listener
{
public:
	MidiHandler() {};
	~MidiHandler() {};

	void prepareToPlay(double sampleRate)
	{
		sr = sampleRate;
	}

	void processBlock(juce::MidiBuffer& midiMessages, Oscillator& osc) {
		int timeStamp;
		MidiMessage m;

		for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, timeStamp); )
		{

			float modFreq = -1.0f;

			if (m.isNoteOn() || m.isPitchWheel())
			{
				osc.parameterChanged(NAME_OSC_ACTIVE, true);

				modFreq = MidiMessage::getMidiNoteInHertz(m.getNoteNumber());

				if (modFreq < sr * 0.5)
					osc.parameterChanged(NAME_RATE, modFreq);
			}

			else if (!midiHold)
				osc.parameterChanged(NAME_OSC_ACTIVE, false);
		}
	}

private:
	void parameterChanged(const String& paramID, float newValue)
	{
		if (paramID == NAME_MIDI_HOLD)
			midiHold = newValue > 0.5f;
	}

	double sr = 44100.0;
	bool midiHold = true;
};
