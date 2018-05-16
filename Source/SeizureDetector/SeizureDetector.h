/*
------------------------------------------------------------------

This file is part of a plugin for the Open Ephys GUI
Copyright (C) 2017 Translational NeuroEngineering Laboratory, MGH

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SEIZURE_DETECTOR_H_INCLUDED
#define SEIZURE_DETECTOR_H_INCLUDED

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <ProcessorHeaders.h>
#include <algorithm> // max
#include "Dsp/Dsp.h" // filtering
#include "boostAcc/boost/accumulators/accumulators.hpp"
#include "boostAcc/boost/accumulators/statistics.hpp"
#include "boostAcc/boost/accumulators/statistics/rolling_mean.hpp"

namespace ba = boost::accumulators;
namespace bt = ba::tag;
typedef ba::accumulator_set < double, ba::stats < bt::rolling_mean > > deltaAcc;

/*
 * The crossing detector plugin is designed to read in one continuous channel c, and generate events on one events channel
 * when c crosses a certain value. There are various parameters to tweak this basic functionality, including:
 *  - whether to listen for crosses with a positive or negative slope, or either
 *  - how strictly to filter transient level changes, by adjusting the required number and percent of past and future samples to be above/below the threshold
 *  - the duration of the generated event
 *  - the minimum time to wait between events ("timeout")
 *
 * All ontinuous signals pass through unchanged, so multiple CrossingDetectors can be
 * chained together in order to operate on more than one channel.
 *
 * @see GenericProcessor
 */

// parameter indices
enum
{
	pInputChan,
	pRollDur,
	pAlphaLow,
	pAlphaHigh,
	pAlphaGain,
	pBetaLow,
	pBetaHigh,
	pBetaGain,
	pDeltaLow,
	pDeltaHigh,
	pDeltaGain
};

class SeizureDetector : public GenericProcessor
{
    friend class SeizureDetectorEditor;

public:
    SeizureDetector();
    ~SeizureDetector();
    
    bool hasEditor() const { return true; }
    AudioProcessorEditor* createEditor() override;

    void createEventChannels() override;

	//void updateSettings() override;

	//void createConfigurationObjects() override;

	void setFilterParameters();

	void setRollingWindowParameters();

    void process(AudioSampleBuffer& continuousBuffer) override;

    void setParameter(int parameterIndex, float newValue) override;

    bool disable() override;

private:
	// -----seizure detection filters---------
	
	OwnedArray<Dsp::Filter> filters;
	
	AudioSampleBuffer scratchBuffer;
	AudioSampleBuffer rollBuffer;

	float rollDur;

	float alphaLow;
	float alphaHigh;
	float alphaGain;
	
	float betaLow;
	float betaHigh;
	float betaGain;
	int betaChan;

	float deltaLow;
	float deltaHigh;
	float deltaGain;
	int deltaChan;

    int inputChan;


    EventChannel* eventChannelPtr;
    MetaDataDescriptorArray eventMetaDataDescriptors;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SeizureDetector);
};

#endif // CROSSING_DETECTOR_H_INCLUDED
