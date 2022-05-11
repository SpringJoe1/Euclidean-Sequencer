/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EuclideanSequencerAudioProcessorEditor::EuclideanSequencerAudioProcessorEditor(EuclideanSequencerAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{

	// 60 Hz
	//Timer::startTimer(60.0f);

	indexshiet = 0;


	for (int i = 0; i < NUM_TOTAL_ETAPAS; i++) {


		// on-off button builder
		onOffButtons.insert({ i, new juce::TextButton{"onOffButton"} });
		onOffButtons.at(i)->setButtonText("Off");
		setTextButtonParams(*onOffButtons.at(i), "ON_OFF_BUTTON" + to_string(i));

		onOffButtonAttachments.insert({ i, nullptr });
		onOffButtonAttachments.at(i).reset(new ButtonAttachment(audioProcessor.apvts, "ON_OFF_BUTTON" + to_string(i), (*onOffButtons.at(i))));

		// sliders builders
		stepsSliders.insert({ i, new juce::Slider()});
		setSliderParams(*stepsSliders.at(i));
		stepsSliderAttachments.insert({ i, nullptr});
		stepsSliderAttachments.at(i).reset(new SliderAttachment(audioProcessor.apvts, "STEPS" + to_string(i), (*stepsSliders.at(i))));
		
		eventsSliders.insert({ i, new juce::Slider() });
		setSliderParams(*eventsSliders.at(i));
		eventsSliderAttachments.insert({ i, nullptr });
		eventsSliderAttachments.at(i).reset(new SliderAttachment(audioProcessor.apvts, "EVENTS" + to_string(i), (*eventsSliders.at(i))));

		rotationSliders.insert({ i, new juce::Slider() });
		setSliderParams(*rotationSliders.at(i));
		rotationSliderAttachments.insert({ i, nullptr });
		rotationSliderAttachments.at(i).reset(new SliderAttachment(audioProcessor.apvts, "ROTATION" + to_string(i), (*rotationSliders.at(i))));

		velocitySliders.insert({ i, new juce::Slider() });
		setSliderParams(*velocitySliders.at(i));
		velocitySliderAttachments.insert({ i, nullptr });
		velocitySliderAttachments.at(i).reset(new SliderAttachment(audioProcessor.apvts, "VELOCITY" + to_string(i), (*velocitySliders.at(i))));

		gateSliders.insert({ i, new juce::Slider() });
		setSliderParams(*gateSliders.at(i));
		gateSliderAttachments.insert({ i, nullptr });
		gateSliderAttachments.at(i).reset(new SliderAttachment(audioProcessor.apvts, "GATE" + to_string(i), (*gateSliders.at(i))));

		// noteNomber combobox
		noteNumberComboBoxes.insert({ i, new juce::ComboBox()});
		setNoteNumberComboBoxParams(*noteNumberComboBoxes.at(i), "NOTE_NUMBER_COMBOBOX" + to_string(i));

		noteNumberComboBoxAttachments.insert({ i, nullptr });
		noteNumberComboBoxAttachments.at(i).reset(new ComboBoxAttachment(audioProcessor.apvts, "NOTE_NUMBER_COMBOBOX" + to_string(i), (*noteNumberComboBoxes.at(i))));


		// stepDuration combobox
		stepDurationComboBoxes.insert({ i, new juce::ComboBox("stepDurationCombobox")});
		setDurationComboBoxParams(*stepDurationComboBoxes.at(i), "STEP_DURATION_COMBOBOX" + to_string(i));

		stepDurationComboBoxAttachments.insert({ i, nullptr });
		stepDurationComboBoxAttachments.at(i).reset(new ComboBoxAttachment(audioProcessor.apvts, "STEP_DURATION_COMBOBOX" + to_string(i), (*stepDurationComboBoxes.at(i))));

		//channel combobox
		channelComboBoxes.insert({ i, new juce::ComboBox() });
		setChannelComboBoxParams(*channelComboBoxes.at(i), "CHANNEL_COMBOBOX" + to_string(i));

		channelComboBoxAttachments.insert({ i, nullptr });
		channelComboBoxAttachments.at(i).reset(new ComboBoxAttachment(audioProcessor.apvts, "CHANNEL_COMBOBOX" + to_string(i), (*channelComboBoxes.at(i))));

		// reverse direction button
		reverseButtons.insert({ i, new juce::TextButton{"reverseButton"} });
		reverseButtons.at(i)->setButtonText("Reverse\nOff");
		setTextButtonParams(*reverseButtons.at(i), "REVERSE_BUTTON" + to_string(i));

		reverseButtonAttachments.insert({ i, nullptr });
		reverseButtonAttachments.at(i).reset(new ButtonAttachment(audioProcessor.apvts, "REVERSE_BUTTON" + to_string(i), (*reverseButtons.at(i))));

		// ping-pong direction button
		pingPongButtons.insert({ i, new juce::TextButton{"pingPongButton"} });
		pingPongButtons.at(i)->setButtonText("Ping Pong\nOff");
		setTextButtonParams(*pingPongButtons.at(i), "PING_PONG_BUTTON" + to_string(i));

		pingPongButtonAttachments.insert({ i, nullptr });
		pingPongButtonAttachments.at(i).reset(new ButtonAttachment(audioProcessor.apvts, "PING_PONG_BUTTON" + to_string(i), (*pingPongButtons.at(i))));

		// triplets button
		tripletsButtons.insert({ i, new juce::TextButton{"tripletsButton"} });
		tripletsButtons.at(i)->setButtonText("Triplets\nOff");
		setTextButtonParams(*tripletsButtons.at(i), "TRIPLETS_BUTTON" + to_string(i));

		tripletsButtonAttachments.insert({ i, nullptr });
		tripletsButtonAttachments.at(i).reset(new ButtonAttachment(audioProcessor.apvts, "TRIPLETS_BUTTON" + to_string(i), (*tripletsButtons.at(i))));

		// dotted button
		dottedButtons.insert({ i, new juce::TextButton{"dottedButton"} });
		dottedButtons.at(i)->setButtonText("Dotted\nOff");
		setTextButtonParams(*dottedButtons.at(i), "DOTTED_BUTTON" + to_string(i));

		dottedButtonAttachments.insert({ i, nullptr });
		dottedButtonAttachments.at(i).reset(new ButtonAttachment(audioProcessor.apvts, "DOTTED_BUTTON" + to_string(i), (*dottedButtons.at(i))));

		if (!audioProcessor.getEuclideanRhythms().count(i)) {
			
			stepsSliders.at(i)->setEnabled(false);
			eventsSliders.at(i)->setEnabled(false);
			rotationSliders.at(i)->setEnabled(false);
			velocitySliders.at(i)->setEnabled(false);
			gateSliders.at(i)->setEnabled(false);
			noteNumberComboBoxes.at(i)->setEnabled(false);
			stepDurationComboBoxes.at(i)->setEnabled(false);
			channelComboBoxes.at(i)->setEnabled(false);
			reverseButtons.at(i)->setEnabled(false);
			pingPongButtons.at(i)->setEnabled(false);
			dottedButtons.at(i)->setEnabled(false);
			tripletsButtons.at(i)->setEnabled(false);
		}

	}
	
	// Re-Sync button
	syncButton = new juce::TextButton{ "syncButton" };
	syncButton->setButtonText("Re-Sync");
	setTextButtonParams(*syncButton, "SYNC_BUTTON4");

	// Save Preset button
	savePresetButton = new juce::TextButton{ "savePresetButton" };
	savePresetButton->setButtonText("Save Preset");
	setTextButtonParams(*savePresetButton, "SAVE_PRESET_BUTTON4");

	// Load Preset button
	loadPresetButton = new juce::TextButton{ "loadPresetButton" };
	loadPresetButton->setButtonText("Load Preset");
	setTextButtonParams(*loadPresetButton, "LOAD_PRESET_BUTTON4");

	// preset combobox
	presetComboBox = new juce::ComboBox{ "presetComboBox" };
	setPresetComboBoxParams(*presetComboBox, "PRESET_COMBOBOX4");

	setSize(1200, 600);
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.

}

EuclideanSequencerAudioProcessorEditor::~EuclideanSequencerAudioProcessorEditor()
{
	//stopTimer();
}

//==============================================================================

//void EuclideanSequencerAudioProcessorEditor::timerCallback() {
//	repaint();
//}

//==============================================================================

void EuclideanSequencerAudioProcessorEditor::paint(juce::Graphics& g)
{	
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.resetToDefaultState();
	g.fillAll(juce::Colours::black);


	// TODO
	/// fixear el pintado
	float innerCircle = 0.8f;
	for (int seqID = 0; seqID < NUM_TOTAL_ETAPAS; seqID++) {
		
		audioProcessor.my_mutex[seqID].lock();

		// si ese ritmo no existe pasa a la siguiente operación
		if (!audioProcessor.getEuclideanRhythms().count(seqID)) {
			audioProcessor.my_mutex[seqID].unlock();
			continue;
		}

		paintRhythm(g, seqID, innerCircle);
		innerCircle -= 0.05f;
		audioProcessor.my_mutex[seqID].unlock();

	}
		

	repaint();
}

void EuclideanSequencerAudioProcessorEditor::resized()
{

	int numOfComponents = 11;

	// bounds of the whole pluggin
	const auto bounds = getLocalBounds();
	// distance between components
	const auto padding = 10;
	// ancho del slider
	const auto componentWidth = (bounds.getWidth() - 400) / numOfComponents - padding;
	// alto del slider
	const auto componentHeight = bounds.getHeight() / (NUM_TOTAL_ETAPAS+1) - 2*padding;
	// donde empieza el primer componente eje X
	auto componentStartX = 400;
	// donde empieza el primer componente eje Y
	auto componentStartY = 0;


	for (int i = 0; i < NUM_TOTAL_ETAPAS; i++) {
		
		onOffButtons.at(i)->setBounds(componentStartX, componentStartY, componentWidth, componentHeight);
		channelComboBoxes.at(i)->setBounds(onOffButtons.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		stepsSliders.at(i)->setBounds(channelComboBoxes.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		eventsSliders.at(i)->setBounds(stepsSliders.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		rotationSliders.at(i)->setBounds(eventsSliders.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		velocitySliders.at(i)->setBounds(rotationSliders.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		gateSliders.at(i)->setBounds(velocitySliders.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		noteNumberComboBoxes.at(i)->setBounds(gateSliders.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		stepDurationComboBoxes.at(i)->setBounds(noteNumberComboBoxes.at(i)->getRight() + padding, componentStartY, componentWidth, componentHeight);
		
		reverseButtons.at(i)->setBounds(stepDurationComboBoxes.at(i)->getRight() + padding, componentStartY, componentWidth, (componentHeight/2));
		pingPongButtons.at(i)->setBounds(stepDurationComboBoxes.at(i)->getRight() + padding, (componentStartY + (componentHeight / 2)), componentWidth, (componentHeight / 2));

		dottedButtons.at(i)->setBounds(reverseButtons.at(i)->getRight() + padding, componentStartY, componentWidth, (componentHeight / 2));
		tripletsButtons.at(i)->setBounds(reverseButtons.at(i)->getRight() + padding, (componentStartY + (componentHeight / 2)), componentWidth, (componentHeight / 2));

		componentStartY += componentHeight + padding;
	}

	syncButton->setBounds(componentStartX, componentStartY, componentWidth, componentHeight);
	savePresetButton->setBounds(syncButton->getRight() + padding, componentStartY, componentWidth, componentHeight/2);
	loadPresetButton->setBounds(syncButton->getRight() + padding, componentStartY + (componentHeight/2), componentWidth, componentHeight / 2);
	presetComboBox->setBounds(savePresetButton->getRight() + padding, componentStartY, componentWidth, componentHeight);

}

//==============================================================================

void EuclideanSequencerAudioProcessorEditor::setTextButtonParams(juce::TextButton& textButton, string id) {
	
	if (id != "SYNC_BUTTON4" && id != "SAVE_PRESET_BUTTON4" && id != "LOAD_PRESET_BUTTON4")
		// en la UI el button se quedará pulsado
		textButton.setClickingTogglesState(true);

	textButton.setComponentID(id);
	addAndMakeVisible(textButton);
	textButton.addListener(this);
}

void EuclideanSequencerAudioProcessorEditor::setSliderParams(juce::Slider& slider) {
	//slider.setDoubleClickReturnValue
	//slider.setNumDecimalPlacesToDisplay
	slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}

void EuclideanSequencerAudioProcessorEditor::setNoteNumberComboBoxParams(juce::ComboBox& comboBox, string id) {

	comboBox.setComponentID(id);
	
	comboBox.addItem("C0", 24);
	comboBox.addItem("C#0", 25);
	comboBox.addItem("D0", 26);
	comboBox.addItem("D#0", 27);
	comboBox.addItem("E0", 28);
	comboBox.addItem("F0", 29);
	comboBox.addItem("F#0", 30);
	comboBox.addItem("G0", 31);
	comboBox.addItem("G#0", 32);
	comboBox.addItem("A0", 33);
	comboBox.addItem("A#0", 34);
	comboBox.addItem("B0", 35);
	
	comboBox.addItem("C1", 36);
	comboBox.addItem("C#1", 37);
	comboBox.addItem("D1", 38);
	comboBox.addItem("D#1", 39);
	comboBox.addItem("E1", 40);
	comboBox.addItem("F1", 41);
	comboBox.addItem("F#1", 42);
	comboBox.addItem("G1", 43);
	comboBox.addItem("G#1", 44);
	comboBox.addItem("A1", 45);
	comboBox.addItem("A#1", 46);
	comboBox.addItem("B1", 47);
	
	comboBox.addItem("C2", 48);
	comboBox.addItem("C#2", 49);
	comboBox.addItem("D2", 50);
	comboBox.addItem("D#2", 51);
	comboBox.addItem("E2", 52);
	comboBox.addItem("F2", 53);
	comboBox.addItem("F#2", 54);
	comboBox.addItem("G2", 55);
	comboBox.addItem("G#2", 56);
	comboBox.addItem("A2", 57);
	comboBox.addItem("A#2", 58);
	comboBox.addItem("B2", 59);
	
	comboBox.addItem("C3", 60);
	comboBox.addItem("C#3", 61);
	comboBox.addItem("D3", 62);
	comboBox.addItem("D#3", 63);
	comboBox.addItem("E3", 64);
	comboBox.addItem("F3", 65);
	comboBox.addItem("F#3", 66);
	comboBox.addItem("G3", 67);
	comboBox.addItem("G#3", 68);
	comboBox.addItem("A3", 69);
	comboBox.addItem("A#3", 70);
	comboBox.addItem("B3", 71);
	
	comboBox.addItem("C4", 72);
	comboBox.addItem("C#4", 73);
	comboBox.addItem("D4", 74);
	comboBox.addItem("D#4", 75);
	comboBox.addItem("E4", 76);
	comboBox.addItem("F4", 77);
	comboBox.addItem("F#4", 78);
	comboBox.addItem("G4", 79);
	comboBox.addItem("G#4", 80);
	comboBox.addItem("A4", 81);
	comboBox.addItem("A#4", 82);
	comboBox.addItem("B4", 83);
	
	comboBox.addItem("C5", 84);
	comboBox.addItem("C#5", 85);
	comboBox.addItem("D5", 86);
	comboBox.addItem("D#5", 87);
	comboBox.addItem("E5", 88);
	comboBox.addItem("F5", 89);
	comboBox.addItem("F#5", 90);
	comboBox.addItem("G5", 91);
	comboBox.addItem("G#5", 92);
	comboBox.addItem("A5", 93);
	comboBox.addItem("A#5", 94);
	comboBox.addItem("B5", 95);
	
	comboBox.addItem("C6", 96);
	comboBox.addItem("C#6", 97);
	comboBox.addItem("D6", 98);
	comboBox.addItem("D#6", 99);
	comboBox.addItem("E6", 100);
	comboBox.addItem("F6", 101);
	comboBox.addItem("F#6", 102);
	comboBox.addItem("G6", 103);
	comboBox.addItem("G#6", 104);
	comboBox.addItem("A6", 105);
	comboBox.addItem("A#6", 106);
	comboBox.addItem("B6", 107);
	
	comboBox.setSelectedId(72); //C4
	comboBox.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(comboBox);
	comboBox.addListener(this);
}

void EuclideanSequencerAudioProcessorEditor::setDurationComboBoxParams(juce::ComboBox& comboBox, string id) {

	comboBox.setComponentID(id);

	// we need the IDs so as we can not store floats,
	// we add the number x1000 so it is an int, and then we will divide again
	
	// 1 es redonda con 4 de duracion
	// 1/2 es blanca con 2 de duracion
	// 1/4 es negra con 1 de duracion
	// ...
	comboBox.addItem("1", 4 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/2", 2 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/4", 1 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/8", 0.5 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/16", 0.25 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/32", 0.125 * CONST_DURATION_TIME_CONV);
	comboBox.addItem("1/64", 0.062 * CONST_DURATION_TIME_CONV);

	comboBox.setSelectedId(1 * CONST_DURATION_TIME_CONV); // negras 
	comboBox.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(comboBox);
	comboBox.addListener(this);
}

void EuclideanSequencerAudioProcessorEditor::setPresetComboBoxParams(juce::ComboBox& comboBox, string id) {
	
	comboBox.setComponentID(id);

	comboBox.addItem(" - ", DEFAULT_PRESET_COMBOBOX);
	comboBox.addItem("Preset 1", 1);
	comboBox.addItem("Preset 2", 2);
	comboBox.addItem("Preset 3", 3);
	comboBox.addItem("Preset 4", 4);
	comboBox.addItem("Preset 5", 5);
	comboBox.addItem("Preset 6", 6);
	comboBox.addItem("Preset 7", 7);
	comboBox.addItem("Preset 8", 8);

	comboBox.setSelectedId(DEFAULT_PRESET_COMBOBOX);
	comboBox.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(comboBox);
	comboBox.addListener(this);
}

void EuclideanSequencerAudioProcessorEditor::setChannelComboBoxParams(juce::ComboBox& comboBox, string id) {

	comboBox.setComponentID(id);

	// we need the IDs so as we can not store floats,
	// we add the number x1000 so it is an int, and then we will divide again

	// canales midi
	comboBox.addItem("1", 1);
	comboBox.addItem("2", 2);
	comboBox.addItem("3", 3);
	comboBox.addItem("4", 4);
	comboBox.addItem("5", 5);
	comboBox.addItem("6", 6);
	comboBox.addItem("7", 7);
	comboBox.addItem("8", 8);
	comboBox.addItem("9", 9);
	comboBox.addItem("10", 10);
	comboBox.addItem("11", 11);
	comboBox.addItem("12", 12);
	comboBox.addItem("13", 13);
	comboBox.addItem("14", 14);
	comboBox.addItem("15", 15);
	comboBox.addItem("16", 16);

	comboBox.setSelectedId(1);
	comboBox.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(comboBox);
	comboBox.addListener(this);
}

void EuclideanSequencerAudioProcessorEditor::disableComponents(int id) {
	
	stepsSliders.at(id)->setEnabled(false);
	eventsSliders.at(id)->setEnabled(false);
	rotationSliders.at(id)->setEnabled(false);
	velocitySliders.at(id)->setEnabled(false);
	gateSliders.at(id)->setEnabled(false);
	noteNumberComboBoxes.at(id)->setEnabled(false);
	stepDurationComboBoxes.at(id)->setEnabled(false);
	channelComboBoxes.at(id)->setEnabled(false);
	reverseButtons.at(id)->setEnabled(false);
	pingPongButtons.at(id)->setEnabled(false);
	dottedButtons.at(id)->setEnabled(false);
	tripletsButtons.at(id)->setEnabled(false);
}

void EuclideanSequencerAudioProcessorEditor::enableComponents(int id) {

	stepsSliders.at(id)->setEnabled(true);
	eventsSliders.at(id)->setEnabled(true);
	rotationSliders.at(id)->setEnabled(true);
	velocitySliders.at(id)->setEnabled(true);
	gateSliders.at(id)->setEnabled(true);
	noteNumberComboBoxes.at(id)->setEnabled(true);
	stepDurationComboBoxes.at(id)->setEnabled(true);
	channelComboBoxes.at(id)->setEnabled(true);
	reverseButtons.at(id)->setEnabled(true);
	pingPongButtons.at(id)->setEnabled(true);
	dottedButtons.at(id)->setEnabled(true);
	tripletsButtons.at(id)->setEnabled(true);
}


//==============================================================================

// LISTENERS

void EuclideanSequencerAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) {

	DBG("!!!! COMBO BOX !!!");
	// string que almacena el ID del combobox + seqID
	juce::String componentID = comboBoxThatHasChanged->getComponentID();
	DBG("juce::String componentID " << componentID);
	// string que almacena el ID del combobox:
	// NOTE_NUMBER_COMBOBOX | NOTE_DURATION_COMBOBOX | STEP_DURATION_COMBOBOX
	juce::String componentIDWithoutID = componentID.dropLastCharacters(1);
	DBG("juce::String componentIDWithoutID " << componentIDWithoutID);
	
	// obtener seqID en formato Int: 0 | 1 | 2 | 3
	char componentIDLast = componentID.toStdString().back();
	DBG("char componentIDLast " << componentIDLast);
	int seqID = stoi(string(1, componentIDLast));
	DBG("int componentIDLastInt " << componentIDLast);

	// TODO -- necesario?

	if (!audioProcessor.getEuclideanRhythms().count(seqID)){
		return;
	}

	// si es el caso del comboboc de NOTE_NUMBER_COMBOBOX
	if (componentIDWithoutID == "NOTE_NUMBER_COMBOBOX")
		audioProcessor.setNewNoteNumber(comboBoxThatHasChanged->getSelectedId(), seqID);
	// Si es el caso del combobox de STEP_DURATION_COMBOBOX
	else if (componentIDWithoutID == "STEP_DURATION_COMBOBOX")
		audioProcessor.setNewStepFigure((float)comboBoxThatHasChanged->getSelectedId() / CONST_DURATION_TIME_CONV, seqID);
	else if (componentIDWithoutID == "CHANNEL_COMBOBOX")
		audioProcessor.setNewChannel((float)comboBoxThatHasChanged->getSelectedId(), seqID);

}

void EuclideanSequencerAudioProcessorEditor::buttonClicked(juce::Button* button) {
	
	DBG("!!!! BUTTON !!!");
	// string que almacena el ID del combobox + seqID
	juce::String componentID = button->getComponentID();
	DBG("juce::String componentID " << componentID);
	// string que almacena el ID del combobox:
	// NOTE_NUMBER_COMBOBOX | NOTE_DURATION_COMBOBOX | STEP_DURATION_COMBOBOX
	juce::String componentIDWithoutID = componentID.dropLastCharacters(1);
	DBG("juce::String componentIDWithoutID " << componentIDWithoutID);
	// obtener seqID en formato Int: 0 | 1 | 2 | 3
	char componentIDLast = componentID.toStdString().back();
	DBG("char componentIDLast " << componentIDLast);
	int seqID = stoi(string(1, componentIDLast));
	DBG("int componentIDLastInt " << componentIDLast);

	if (componentIDWithoutID == "SAVE_PRESET_BUTTON") {
		if (presetComboBox->getSelectedId() == DEFAULT_PRESET_COMBOBOX) {
			juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
				"Select Preset",
				"Select a preset in the combobox where you want to save it.",
				"Ok",
				nullptr,
				nullptr);
		}
		else
			audioProcessor.savePreset(presetComboBox->getSelectedId());
	}
	else if (componentIDWithoutID == "LOAD_PRESET_BUTTON") {
		if (presetComboBox->getSelectedId() == DEFAULT_PRESET_COMBOBOX) {
			juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
				"Select Preset",
				"Select a preset in the combobox to load it.",
				"Ok",
				nullptr,
				nullptr);
		}
		else
			audioProcessor.loadPreset(presetComboBox->getSelectedId());
	}
	else if (componentIDWithoutID == "ON_OFF_BUTTON") {

		if (button->getToggleState() == false && audioProcessor.getEuclideanRhythms().count(seqID)) {

			// change button text
			button->setButtonText("Off");
			// disable those components
			disableComponents(seqID);
			// delete rythm
			audioProcessor.deleteRythm(seqID);

		}
		else {

			if (audioProcessor.getEuclideanRhythms().count(seqID)) {
				return;
			}

			// change button text
			button->setButtonText("On");
			//enable those components
			enableComponents(seqID);

			// create rythm
			int steps = stepsSliders.at(seqID)->getValue();
			int events = eventsSliders.at(seqID)->getValue();
			int rotation = rotationSliders.at(seqID)->getValue();
			int velocity = velocitySliders.at(seqID)->getValue();
			int gate = gateSliders.at(seqID)->getValue();
			int noteNumber = noteNumberComboBoxes.at(seqID)->getSelectedId();
			float figureStep = (float)stepDurationComboBoxes.at(seqID)->getSelectedId() / CONST_DURATION_TIME_CONV;
			int channel = channelComboBoxes.at(seqID)->getSelectedId();
			bool direction = true;
			bool reverse = reverseButtons.at(seqID)->getToggleState();
			DBG("STATE REVERSE  "<< (int)reverse);
			bool pingPong = pingPongButtons.at(seqID)->getToggleState();
			bool dottedNotes = dottedButtons.at(seqID)->getToggleState();
			bool triplets = tripletsButtons.at(seqID)->getToggleState();

			audioProcessor.createRythm(seqID, steps, events, rotation, velocity, gate, noteNumber,
				figureStep, direction, reverse, pingPong, dottedNotes, triplets, channel);

		}
	}
	else if (componentIDWithoutID == "SYNC_BUTTON") {
		if(!audioProcessor.getEuclideanRhythms().empty())
			audioProcessor.synchronizeAll();
	}
	
	if (!audioProcessor.getEuclideanRhythms().count(seqID))
		return;

	
	if (componentIDWithoutID == "REVERSE_BUTTON") {
		

		if (button->getToggleState()) {

			// deseleccionamos el pingPongButton
			if (pingPongButtons.count(seqID))
				pingPongButtons.at(seqID)->setToggleState(false, true);

			// reverse the direction of the rythm
			button->setButtonText("Reverse\nOn");
			audioProcessor.setReverseDirection(seqID, true);

		}
		else{
			// set the right direction
			button->setButtonText("Reverse\nOff");
			//button->setToggleState(true, juce::NotificationType::dontSendNotification);
			audioProcessor.setReverseDirection(seqID, false);
		}
	}
	else if (componentIDWithoutID == "PING_PONG_BUTTON") {
		
		if (button->getToggleState()) {

			// deseleccionamos el reverseButton
			if(reverseButtons.count(seqID))
				reverseButtons.at(seqID)->setToggleState(false, true);

			button->setButtonText("Ping Pong\nOn");
			audioProcessor.setNewPingPong(seqID, true);
		}
		else {

			// set the right direction
			button->setButtonText("Ping Pong\nOff");
			audioProcessor.setNewPingPong(seqID, false);

		}
	}
	else if (componentIDWithoutID == "DOTTED_BUTTON") {
		
		if (button->getToggleState() == true) {

			// deseleccionamos el tripletsButton
			if(tripletsButtons.count(seqID))
				tripletsButtons.at(seqID)->setToggleState(false, true);

			button->setButtonText("Dotted\nOn");
			audioProcessor.setDottedNotes(seqID, true, ((float)stepDurationComboBoxes.at(seqID)->getSelectedId() / CONST_DURATION_TIME_CONV));
		}
		else {

			button->setButtonText("Dotted\nOff");
			audioProcessor.setDottedNotes(seqID, false, (float)stepDurationComboBoxes.at(seqID)->getSelectedId() / CONST_DURATION_TIME_CONV);

		}
	}
	else if (componentIDWithoutID == "TRIPLETS_BUTTON") {
		
		if (button->getToggleState() == true) {

			// deseleccionamos el dottedNotesButton
			if(dottedButtons.count(seqID))
				dottedButtons.at(seqID)->setToggleState(false, true);

			button->setButtonText("Triplets\nOn");
			audioProcessor.setTriplets(seqID, true, ((float)stepDurationComboBoxes.at(seqID)->getSelectedId() / CONST_DURATION_TIME_CONV));
		}
		else {
			button->setButtonText("Triplets\nOff");
			audioProcessor.setTriplets(seqID, false, (float)stepDurationComboBoxes.at(seqID)->getSelectedId() / CONST_DURATION_TIME_CONV);

		}
	}
	

}

//==============================================================================


void EuclideanSequencerAudioProcessorEditor::paintRhythm(juce::Graphics& g, int seqID, float innerCircleProp) {


	// dimensions
	float startX = 50 * seqID;
	float startY = 50 * seqID;
	float width = 100 * (NUM_TOTAL_ETAPAS - seqID);
	float height = 100 * (NUM_TOTAL_ETAPAS - seqID);

	// colour selection
	juce::Colour colourOn;
	switch (seqID)
	{
	case 0:
		colourOn = juce::Colours::lightcoral; //indianred
		break;
	case 1:
		colourOn = juce::Colours::lightsalmon; // lightpink
		break;
	case 2:
		colourOn = juce::Colours::lightgreen;
		break;
	case 3:
		colourOn = juce::Colours::lightskyblue; // lightskyblue
		break;
	default:
		break;
	}

	// numero de steps
	int numSteps = audioProcessor.getEuclideanRhythms().at(seqID)->get_steps();
	// anchura de cada step en radianes
	float stepSize = 2 * juce::MathConstants<float>::pi / numSteps;

	bool same = false;

	if (indexshiet != audioProcessor.getEuclideanRhythms().at(seqID)->getIndex())
		indexshiet = (indexshiet + 1) % audioProcessor.getEuclideanRhythms().at(seqID)->get_steps();

	// loop para pintar los steps
	for (int i = 0; i < numSteps; i++) {
		
		juce::Path pieSegments;
		float startRadians = stepSize * i;
		float endRadians = startRadians + (stepSize * 0.95f);


		// notas en On
		if (audioProcessor.getEuclideanRhythms().at(seqID)->get_euclideanRhythm().at(i) == 1) {
			pieSegments.addPieSegment(startX, startY, width, height, startRadians, endRadians, innerCircleProp);
			g.setColour(colourOn);
		}
		// notas en Off
		else {
			startRadians = stepSize * (i+0.25f);
			endRadians = startRadians + (stepSize*0.5f);
			pieSegments.addPieSegment(startX, startY, width, height, startRadians, endRadians, 0.95f);
			g.setColour(juce::Colours::darkgrey); //silver
		}
			

		// TODO
		// el problema esta al acceder al vector ! ! !! ! ! ! 
		// chequear funcion sleep(miliseconds) en funcion de la duracion de la nota
		
		// nota que está sonando
		if (indexshiet == i) {
			g.setColour(juce::Colours::white);
			auto millisec_since_epoch = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

			DBG("DRAW TIME " << millisec_since_epoch - 1652283000000);
		}
		

		g.fillPath(pieSegments);
		pieSegments.clear();

	}
	
}


