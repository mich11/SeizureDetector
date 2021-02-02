# Multi-band Integrator Plugin

This Open Ephys plugin allows the user to mix, weight, and apply a rolling average to bandwidths of interest on a single channel.  Its output can be thought of as a real-time power signal for waveforms with complex but well-specified frequency components.  It can be paired with the crossing detector plugin to trigger events when the output power reaches a threshold to trigger events based on waveforms of interest.

It was developed to detect absence seizures in mice in real time based on their spectral properties as described in Sorokin et al, 2016. 

## For the latest version
The Open Ephys team has added the multi-band integrator to its collection of supported plugins! See their documentation to install and use with the latest version of Open Ephys (0.5.3 and later):
 https://open-ephys.github.io/gui-docs/User-Manual/Plugins/Multiband-Integrator.html

## Settings
Users can specify 
* input channel 
* rolling average window duration
* Up to 3 frequency bands
* Gain for each frequency band

## Example EEG data
The example data set contains mouse EEG recordings and annotations for seizure start/end times for plugin testing and future development. See ExampleData/ExampleDataNotes.txt for details

## Legacy Installation
This plugin and install procedure has only been built and tested on Windows.  It depends on the Dsp library and a subset of the Boost libraries, making it tricky to install. Installing the latest version of Open Ephys and its built-in plugin installer [here] ( https://open-ephys.github.io/gui-docs/User-Manual/Plugins/Multiband-Integrator.html) instead is highly recommended. To install for Open Ephys version 0.4.5, try the following:

* Copy `multi-band-integrator/Source/` to `plugin-GUI/Source/Plugins/MultiBandIntegrator`.

* Copy `multi-band-integrator/Builds/VisualStudio2013/MultiBandIntegrator` to `plugin-GUI/Builds/VisualStudio2019/Plugins/MultiBandIntegrator`.

* In Visual Studio 2019, open the `Plugins.sln` solution and add the MultiBandIntegrator project (`File -> Add -> Existing Project...` and select `Builds/VisualStudio2013/Plugins/MultiBandIntegrator/MultiBandIntegrator.vcxproj`)

* To get Boost to work:
  * Right click plugin project (MultiBandIntegrator)
  * Go to `Properties -> Configuration Properties -> C/C++ -> General`, click drop-down for Additional Include Directories and select `<Edit...>`
  * Add `\plugin-GUI\Source\Plugins\MultiBandIntegrator\boostAcc` to the upper window and click "ok" to add it as an additional include directory

* To get DspLib to work:
  * Right click plugin project (MultiBandIntegrator)
  * Go to `Build Dependencies -> Project Dependencies...` and check that DspLib has a check next to it
  * Right click plugin project 
  * Go to `Build Dependencies -> Project Order...` and check that MultiBandIntegrator is lower than DspLib in the build order
  * Right click plugin project
  * Go to `Properties -> Configuration Properties -> Linker -> Input`, click drop-down menu for Additional Dependencies and select `<Edit...>`
  * Add DspLib.Lib to upper window

* Build the plugin
