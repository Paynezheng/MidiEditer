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
	MidiConventer (){}
	MidiConventer (MidiFile midifile, ChordProgression chord_progression, int duration);
	MidiConventer (std::string file_url, ChordProgression chord_progression, int duration);
	void		Reset();
	void		Clear();
	bool		Convent(int track, int bpm, int chords);

	void		QuantifyTrack(int track);
	void		CleanChordVoiceover(int track);
	void		CleanRecurNotes(int track);
	void		ProlongNotes(int track);
	void		Write2File(std::string);

public:
	static void PrintMidifile(MidiFile m_midifile);

private:
	double 		QuantifyEvent(MidiEvent& midievent, int unit_size, int direction);
	void		CuttingNote(MidiEvent& on, MidiEvent& off);
	bool		IsChordInterior(const MidiEvent& midievent);
	bool 		CheckNoteValid(const MidiEvent& on, const MidiEvent& off);
	double		GetBeat(int tick);



private:
	MidiFile  			m_midifile;
	ChordProgression	m_chord_progression;
	int m_duration = 0;			// 量化一个事件的最小单位
	int	m_track_num = 0;
};

} // end of namespace smf

