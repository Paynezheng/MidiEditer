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
#include <vector>

namespace smf {
enum EChordProgressions {
	EN_CHORD_PROGRESSIONS_TYPE__C_BLUES						= 0,			// 12小节蓝调
	EN_CHORD_PROGRESSIONS_TYPE__Dm7_G7_CM7_Am7 				= 1				// 2516
};

enum ENotes {
	EN_NOTE__C 				= 0,
	EN_NOTE__C_SHARP		= 1,
	EN_NOTE__D_FLAT			= 1,
	EN_NOTE__D 				= 2,
	EN_NOTE__D_SHARP		= 3,
	EN_NOTE__E_FLAT			= 3,
	EN_NOTE__E				= 4,
	EN_NOTE__F_FLAT			= 4,
	EN_NOTE__E_SHARP		= 5,
	EN_NOTE__F				= 5,
	EN_NOTE__F_SHARP		= 6,
	EN_NOTE__G_FLAT			= 6,
	EN_NOTE__G				= 7,
	EN_NOTE__G_SHARP		= 8,
	EN_NOTE__A_FLAT			= 8,
	EN_NOTE__A				= 9,
	EN_NOTE__A_SHARP		= 10,
	EN_NOTE__B_FLAT			= 10,
	EN_NOTE__B				= 11,
	EN_NOTE__C_FLAT			= 11,
	EN_NOTE__B_SHARP		= 12
};

enum EChordName {
	EN_CHORD_NAME__MAJOR				= 1, // 大三和弦
	EN_CHORD_NAME__MINOR				= 2, // 小三
	EN_CHORD_NAME__MAJOR_SEVENTH		= 3, // 大七
	EN_CHORD_NAME__MINOR_SEVENTH		= 4, // 小七
	EN_CHORD_NAME__SUS_SEVENTH			= 5  // 属七
};



class Chord {
public:
	Chord(int chord_base, int chord_name);
	bool 		IsChordInterior(int key);

	int 		m_chord_base = 0;			// 和弦根音
	int 		m_chord_name = 0;			// 和弦名
	std::vector<int>		m_notes;
};

class ChordProgression {
public:
	ChordProgression(int chord_progression_id);
	ChordProgression(int chord_progression_id, int modulation);						// TODO:提供转调
	void 		Init(std::vector<std::tuple<int, int>>& chords);					// TODO:提供一个自定义的和弦进行 
	void 		Reset();

	std::vector<Chord> 		m_chords;
};

class MidiConventer {
public:
	MidiConventer (MidiFile* midifile, ChordProgression* chord_progression, int duration);
	void		Reset();
	bool		Convent(int track, int bpm, int chords);									// all in one
	
	// 
	// 量化 
	bool		QuantifyTrack(int track, int duration);
	bool		QuantifyNote(MidiEvent* midievent, int duration, int direction);			// 向前/后 量化一个事件

	// 延音
	// 去掉和弦外音和重复音


private:
	MidiFile* 			m_midifile = nullptr;
	ChordProgression*	m_chord_progression	= nullptr;
	int 				m_duration;			// 量化一个事件的最小单位
};

} // end of namespace smf

