# Multi-band Integrator Plugin
This Open-Ephys plugin allows the user to mix, weight, and apply a rolling average to bandwidths of interest on a single channel.  Its output can be thought of as a real-time power signal for waveforms with complex but well-specified frequency components.  It can be paired with the crossing detector plugin to trigger events when the output power reaches a threshold to trigger events based on waveforms of interest.

It was originally developed to detect absence-like seizures in mice in real time based on their spectral properties as described in Sorokin et al, 2016. 

## Settings
Users can specify 
* input channel 
* rolling average window duration
* Up to 3 frequency bands
* Gain for each frequency band

## Installation
This plugin has only been built and tested on Windows so far.  It depends on the Dsp library and a subset of the Boost libraries for those interested in building for Linux or OSX. 
* Copy `multi-band-integrator/Source/' to `plugin-GUI/Source/Plugins/MultiBandIntegrator`.

* Copy `multi-band-integrator/Builds/VisualStudio2013/MultiBandIntegrator` to `plugin-GUI/Builds/VisualStudio2013/Plugins/MultiBandIntegrator`.

* In Visual Studio, open the `Plugins.sln` solution and add the MultiBandIntegrator project (`File->Add->Existing Project...` and select `Builds/VisualStudio2013/Plugins/MultiBandIntegrator/MultiBandIntegrator.vcxproj`). Then build the plugin.
