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

#ifndef SEIZURE_DETECTOR_EDITOR_H_INCLUDED
#define SEIZURE_DETECTOR_EDITOR_H_INCLUDED

#include <VisualizerEditorHeaders.h>
#include <VisualizerWindowHeaders.h>
#include <string>
#include <climits>
#include <cfloat>
#include <algorithm>

/*
Editor (in signal chain) contains:
- Input channel selector
- Ouptput event channel selector
- Direction ("rising" and "falling") buttons
- Threshold control (and indicator when threshold randomization is on)
- Event timeout control

Canvas/visualizer contains:
- Threshold randomization toggle, minimum and maximum thresh boxes
- Slope (jump size across threshold) limiting toggle and max jump box
- Voting settings (pre/post event span and strictness)
- Event duration control

@see GenericEditor
*/

class SeizureDetectorCanvas;

class SeizureDetectorEditor 
    : public VisualizerEditor
    , public ComboBox::Listener
    , public Label::Listener
{
public:
    SeizureDetectorEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors = false);
    ~SeizureDetectorEditor();
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void labelTextChanged(Label* labelThatHasChanged) override;

    // overrides GenericEditor
    void buttonEvent(Button* button) override;

    void updateSettings() override;

    // disable input channel selection during acquisition so that events work correctly
    void startAcquisition() override;
    void stopAcquisition() override;

    Visualizer* createNewCanvas() override;

    Component* getOptionsPanel();

    void saveCustomParameters(XmlElement* xml) override;
    void loadCustomParameters(XmlElement* xml) override;

private:
    typedef juce::Rectangle<int> Rectangle;

    // Basic UI element creation methods. Always register "this" (the editor) as the listener,
    // but may specify a different Component in which to actually display the element.
    Label* createEditable(const String& name, const String& initialValue,
        const String& tooltip, Rectangle bounds);
    Label* createLabel(const String& name, const String& text, Rectangle bounds);

    // Utilities for parsing entered values
    static bool updateIntLabel(Label* label, int min, int max, int defaultValue, int* out);
    static bool updateFloatLabel(Label* label, float min, float max, float defaultValue, float* out);

    // top row (channels)
    ScopedPointer<Label> inputLabel;
    ScopedPointer<ComboBox> inputBox;
    ScopedPointer<Label> outputLabel;
    ScopedPointer<ComboBox> outputBox;

    // middle row (threshold)
    ScopedPointer<UtilityButton> risingButton;
    ScopedPointer<UtilityButton> fallingButton;
    ScopedPointer<Label> acrossLabel;
    ScopedPointer<Label> thresholdEditable;

    // bottom row (timeout)
    ScopedPointer<Label> timeoutLabel;
    ScopedPointer<Label> timeoutEditable;
    ScopedPointer<Label> timeoutUnitLabel;

    // --- Canvas elements are managed by editor but invisible until visualizer is opened ----
    SeizureDetectorCanvas* canvas;
    ScopedPointer<Component> optionsPanel;

    ScopedPointer<Label> optionsPanelTitle;
    
    // threshold randomization
    ScopedPointer<ToggleButton> randomizeButton;
    ScopedPointer<Label> minThreshLabel;
    ScopedPointer<Label> minThreshEditable;
    ScopedPointer<Label> maxThreshLabel;
    ScopedPointer<Label> maxThreshEditable;

    // jump limiting
    ScopedPointer<ToggleButton> limitButton;
    ScopedPointer<Label> limitLabel;
    ScopedPointer<Label> limitEditable;

    // sample voting
    ScopedPointer<Label> votingHeader;
    
    ScopedPointer<Label> pastStrictLabel;
    ScopedPointer<Label> pastPctEditable;
    ScopedPointer<Label> pastPctLabel;
    ScopedPointer<Label> pastSpanEditable;
    ScopedPointer<Label> pastSpanLabel;

    ScopedPointer<Label> futureStrictLabel;
    ScopedPointer<Label> futurePctEditable;
    ScopedPointer<Label> futurePctLabel;
    ScopedPointer<Label> futureSpanLabel;
    ScopedPointer<Label> futureSpanEditable;

    ScopedPointer<Label> votingFooter;

    // event duration
    ScopedPointer<Label> durLabel;
    ScopedPointer<Label> durationEditable;
    ScopedPointer<Label> durUnitLabel;

	// frequency band gains
	ScopedPointer<Label> gainLabel;

	ScopedPointer<Label> alphaLabel;
	ScopedPointer<Label> alphaEditable;

	ScopedPointer<Label> betaLabel;
	ScopedPointer<Label> betaEditable;

	ScopedPointer<Label> deltaLabel;
	ScopedPointer<Label> deltaEditable;
};

// Visualizer window containing additional settings

class SeizureDetectorCanvas : public Visualizer
{
public:
    SeizureDetectorCanvas(GenericProcessor* n);
    ~SeizureDetectorCanvas();
    void refreshState() override;
    void update() override;
    void refresh() override;
    void beginAnimation() override;
    void endAnimation() override;
    void setParameter(int, float) override;
    void setParameter(int, int, int, float) override;

    void paint(Graphics& g) override;
    void resized() override;

    GenericProcessor* processor;
    SeizureDetectorEditor* editor;
private:
    ScopedPointer<Viewport> viewport;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SeizureDetectorCanvas);
};

#endif // SEIZURE_DETECTOR_EDITOR_H_INCLUDED
