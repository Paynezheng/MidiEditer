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

#define SPECIAL_QUALIFY 0.6		// 中轴线量化为0.5, 0.6表示在前60%的位置上量化到左边
#define NORMAL_QUALIFY 0.5

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
	void 		QualifyVol(int track);
	void		SetBPM(int track, double bpm);
	void		Write2File(std::string file_url);

	int			getTrackCount();

public:
	static void PrintMidifile(MidiFile m_midifile);
	void 		PrintMidifile();

private:
	double 		QuantifyEvent(MidiEvent& midievent, int unit_size, double qualify_space, int direction = 0);	// 指定量化方向默认为0, 默认为靠近原则
	void		CuttingNote(MidiEvent& on, MidiEvent& off);
	bool		IsChordInterior(const MidiEvent& midievent);
	bool 		CheckNoteValid(const MidiEvent& on, const MidiEvent& off);
	double		GetBeat(int tick);



private:
	MidiFile  			m_midifile;
	ChordProgression	m_chord_progression;
	int m_duration = 0;			// 量化一个事件的最小单位
	int	m_track_count = 0;
};

} // end of namespace smf

