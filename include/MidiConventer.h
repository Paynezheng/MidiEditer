//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed Dec 29 02:02:10 UTC 2021
// Last Modified: Wed Dec 29 02:02:10 UTC 2021
// Filename:      midiediter/include/MidiConventer.h
// Syntax:        C++11
// Code           UTF-8
//

#pragma once
#include "MidiFile.h"
#include "MidiMessage.h"
#include <vector>

namespace smf {
enum EChordProgressions {
	EN_CHORD_PROGRESSIONS_TYPE__BLUES	= 0			// 12小节蓝调
};

enum ENotes {
	EN_NOTE__C1 			= 36,
	EN_NOTE__C1_SHARP		= 37,
	EN_NOTE__D1_FLAT		= 37,
	EN_NOTE__D1 			= 38,
	EN_NOTE__D1_SHARP		= 39,
	EN_NOTE__E1_FLAT		= 39,
	EN_NOTE__E1				= 40,
	EN_NOTE__F1_FLAT		= 40,
	EN_NOTE__E1_SHARP		= 41,
	EN_NOTE__F1				= 41,
	EN_NOTE__F1_SHARP		= 42,
	EN_NOTE__G1_FLAT		= 42,
	EN_NOTE__G1				= 43,
	EN_NOTE__G1_SHARP		= 44,
	EN_NOTE__A1_FLAT		= 44,
	EN_NOTE__A1				= 45,
	EN_NOTE__A1_SHARP		= 46,
	EN_NOTE__B1_FLAT		= 46,
	EN_NOTE__B1				= 47
};

enum EChordName {
	EN_CHORD_NAME__MAJOR				= 1, // 大三和弦
	EN_CHORD_NAME__MINOR				= 2, // 小三
	EN_CHORD_NAME__MAJOR_SEVENTH		= 3, // 大七
	EN_CHORD_NAME__MINOR_SEVENTH		= 4, // 小七
};



class Chord {
public:
	Chord(int chord_base, int chord_name);
	bool IsChordInterior(int key);
private:
	int 		m_chord_base = 0;			// 和弦根音
	int 		m_chord_name = 0;			// 和弦名
	std::vector<int> notes;
};

class ChordProgression {
public:
	void Reset();

	std::vector<Chord> 		m_chords;
private:

};

class MidiConventer {
public:
	MidiConventer (MidiFile* midifile, ChordProgression chord_progression, int duration);
	void		Reset();
	bool		Convent(int track, int bpm, int chords);									// all in one
	// TODO: 如何转调?

	// 量化 // 延音
	bool		QuantifyTrack(int track, int duration);
	bool		QuantifyNote(MidiEvent* midievent, int duration, int direction);			// 向前/后 量化一个事件

	// 去掉和弦外音和重复音


	int 				m_duration;			// 量化一个事件的最小单位
	ChordProgression	m_chord_progression;
private:
	MidiFile* m_midifile = nullptr;

};

} // end of namespace smf

