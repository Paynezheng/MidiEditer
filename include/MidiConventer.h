//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed Dec 29 02:02:10 UTC 2021
// Last Modified: Thu Jan  6 07:17:45 UTC 2022
// Filename:      midiediter/include/MidiConventer.h
// Syntax:        C++11
// Code           UTF-8
//

#pragma once
#include "MidiFile.h"
#include "MidiMessage.h"
#include "ChordProgression.h"
#include <vector>
#include <map>

namespace smf {

class MidiConventer {
public:
	MidiConventer (MidiFile* midifile, ChordProgression* chord_progression, int duration);
	void		Reset();
	bool		Convent(int track, int bpm, int chords);

	void		QuantifyTrack(int track);
	void		CleanChordVoiceover(int track);
	void		CleanRecurNotes(int track);
	void		ProlongNotes(int track);
	void 		PrintMidifile();

private:
	double 		QuantifyEvent(MidiEvent& midievent, int unit_size, int direction);
	void		CuttingNote(MidiEvent& on, MidiEvent& off);
	bool		IsChordInterior(const MidiEvent& midievent);
	bool 		CheckNoteValid(const MidiEvent& on, const MidiEvent& off);
	double		GetBeat(int tick);



private:
	MidiFile* 			m_midifile = nullptr;
	ChordProgression*	m_chord_progression	= nullptr;
	int 				m_duration;			// 量化一个事件的最小单位
};

} // end of namespace smf

