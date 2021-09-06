#pragma once
#include <JuceHeader.h>

// MIDI
#define NAME_MIDI_HOLD            "midi_hold"
#define DEFAULT_MIDI_HOLD         true

#define NAME_MIDI_ACTIVE          "midi_listen"
#define DEFAULT_MIDI_ACTIVE       true

// Dry/Wet
#define NAME_DRYWET				  "drywet"
#define DEFAULT_DRYWET			  0.5f

// BitCrusher
#define NAME_POST_MOD             "pre_modulation"
#define DEFAULT_POST_MOD           0

#define NAME_DEG_TYPE             "degradation_type"
#define DEFAULT_DEG_TYPE          0

#define NAME_INPUT_GAIN           "input_gain"
#define DEFAULT_INPUT_GAIN         1.0f

#define NAME_BIT_DEPTH            "bit_depth"
#define DAFAULT_BIT_DEPTH         24

#define NAME_SUB_FACTOR           "subsamp_factor"
#define DEFAULT_SUB_FACTOR        1

// Oscillator
#define NAME_OSC_ACTIVE           "osc_active"
#define DEFAULT_OSC_ACTIVE        true

#define NAME_RATE	              "rate"
#define DEFAULT_RATE              500.0f   // Hz
#define RATE_SMOOTHING_TIME       0.05f // 50 msec

#define NAME_STEREO_FREQ          "stereo_freq"
#define DEFAULT_STEREO_FREQ       0.0f 

// Waveform
#define NAME_WAVEFORM             "waveform"
#define DEFAULT_WAVEFORM          0

// Modulation amount
#define NAME_AMOUNT               "amount"
#define DEFAULT_AMOUNT            1.0f

// Filter
#define DEFAULT_NUM_FILTERS       2

#define NAME_FILTER_ACTIVE        "filter_active"
#define DEFAULT_FILTER_ACTIVE     false

#define NAME_CUTOFF               "cutoff"
#define DEFAULT_CUTOFF            1.0f

#define NAME_Q                    "quality"
#define DEFAULT_Q                 0.86f

static AudioProcessorValueTreeState::ParameterLayout createParametersLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterBool>(NAME_MIDI_ACTIVE, "Midi active", DEFAULT_MIDI_ACTIVE));
    params.push_back(std::make_unique<AudioParameterBool>(NAME_MIDI_HOLD, "Midi hold", DEFAULT_MIDI_HOLD));

    params.push_back(std::make_unique<AudioParameterBool>(NAME_POST_MOD, "Post modulation", DEFAULT_POST_MOD));
    params.push_back(std::make_unique<AudioParameterChoice>(NAME_DEG_TYPE, "Deg. type", StringArray("Hard clipping", "Quantization noise", "Aliasing"), DEFAULT_DEG_TYPE));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_INPUT_GAIN, "Input gain", NormalisableRange<float>(1.0f, 60.0f, 0.1f), DEFAULT_INPUT_GAIN));
    params.push_back(std::make_unique<AudioParameterInt>(NAME_BIT_DEPTH, "Bit depth", 1, 24, DAFAULT_BIT_DEPTH));
    params.push_back(std::make_unique<AudioParameterInt>(NAME_SUB_FACTOR, "Subsampling factor", 1, 100, DEFAULT_SUB_FACTOR));

    params.push_back(std::make_unique<AudioParameterFloat>(NAME_DRYWET, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DRYWET));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_RATE, "Oscillator freq.", NormalisableRange<float>(0.1f, 20000.0f, 0.01f, 0.5f), DEFAULT_RATE));

    params.push_back(std::make_unique<AudioParameterFloat>(NAME_AMOUNT, "Mod. amount", NormalisableRange<float>(0.0f, 1.0f, 0.001f, 0.25f), DEFAULT_AMOUNT));
    params.push_back(std::make_unique<AudioParameterChoice>(NAME_WAVEFORM, "Mod. waveform", StringArray("Sine", "Sawtooth", "Triangular", "Square"), DEFAULT_WAVEFORM));

    params.push_back(std::make_unique<AudioParameterBool>(NAME_FILTER_ACTIVE, "Filter active", DEFAULT_FILTER_ACTIVE));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_CUTOFF, "Filter cutoff.", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 0.5f), DEFAULT_CUTOFF));

    return { params.begin(), params.end() };
}