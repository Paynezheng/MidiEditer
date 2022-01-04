//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed Dec 29 02:02:10 UTC 2021
// Last Modified: Wed Dec 29 09:37:18 UTC 2021 
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

	void		QuantifyTrack(int track, int duration);
	void		CleanChordVoiceover(int track);
	void		CleanRecurNotes(int track);
	void		ProlongNotes(int track);
	void 		PrintMidifile();

private:
	void 		QuantifyEvent(MidiEvent& midievent, int unit_size, int tpq, int direction);
	bool		IsChordInterior(const MidiEvent& midievent);
	double		GetBeat(int tick, int tpq);


private:
	MidiFile* 			m_midifile = nullptr;
	ChordProgression*	m_chord_progression	= nullptr;
	int 				m_duration;			// 量化一个事件的最小单位
};

} // end of namespace smf

