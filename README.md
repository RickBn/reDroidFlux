# RE_DROID_FLUX 1.1.0
![gui](https://drive.google.com/uc?export=view&id=1KiG4MFtoO0-c-5lmmAQcP_MLTnLMMCOC)
# Plugin description
reDroidFlux is an all-in-one MIDI controlled ring modulator and bit crusher. Modulation frequency can be changed manually or controlled via MIDI input. The bit crusher effect can be applied before or after the modulation. 

Supported channel layouts: mono-in/out and stereo-in/out.

The plugin is available in the following formats:

|       | VST3 | Standalone|
|-------|-------|-------|
|       |64 Bit |	64 Bit|
|Mac OS	| x | x	|
|Windows|	√	|	√ |

# How to install
Place the VST3 file in the correct folder:
Plugin type	Folder type	Windows Installation Directory
VST3	Shared	C:\Program Files\Common Files\VST3

# How to use
The GUI allows to control the parameters shown in the picture below:

![diag](https://drive.google.com/uc?export=view&id=1oajgG2xvdI7vIl1QjWv8AxbGYlRBVLQk)

 
With “Note-on hold” checked the oscillator rate will be the frequency of the last note-on received.
With “Note-on hold” un-checked, in case of a note-off received, the modulation will cease to have effect until the next note-on.

# Recommended presets!

|Name|	Deg. type	|Input gain|	Bit depth	|Subsamp. factor|	Post mod.|	Waveform	|Rate	|Smooth factor|	Mix|
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|Exterminate!	|Soft clipping	|30.0	|x	|×|	x	|Square|	32.00|	0.50|	1.00|
|Lo-fi rustle	|Quant. noise	|x	|6|	x|	x|	Sine	|740.00	|1.00	|0.30|
|Alien invasion|	Aliasing|	x|	x	|100|	√	|Triangular|	20000.00|	0.00|	1.00|
|Droid ambassador|	Aliasing|	x|	x	|3	|√	|Square|	88.00	|0.00	|0.80|
|Complete chaos|	Quant. noise|	x|4	|x|	√	|Square|	169.00	|0.00	|1.00|


# Disclaimer
This software has been developed by Riccardo Bona at the “Laboratorio di Informatica Musicale dell'Università degli Studi di Milano”. Beware that this is an exam project without commercial aims and is not to be intended as a polished product devoid of flaws. For this reason, any responsibility regarding any type of malfunctioning is declined. For further information visit the site: https://www.lim.di.unimi.it 

# Contacts
To report bugs or forward any comment write at:  riccardo.bona@studenti.unimi.it
