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




class Chord {
public:
	Chord(int chord_base, int chord_name);
	bool 		IsChordInterior(int key);

	int 		m_chord_base = 0;			// 和弦根音
	int 		m_chord_name = 0;			// 和弦名
	std::vector<int>		m_notes;
};

/**
 * @brief 和弦进行类, 后续如果有特别的需求可以新写一个和弦进行类来初始化MidiConventer
 */
class ChordProgression {
public:
	ChordProgression(int chord_progression_id);
	ChordProgression(int chord_progression_id, int modulation);						// TODO:提供转调
	void 		Init(std::vector<std::tuple<int, int>>& chords);					// TODO:提供一个自定义的和弦进行 
	void 		Reset();
	bool		IsChordInterior(int beat, int key);

	std::map<int, std::tuple<Chord, int>>		m_chords;		// 序号-><和弦, beats> 
	std::vector<std::tuple<Chord, int>> 		m_chords;		// 第几拍->和弦
	int			m_beats;	// 一共有几拍
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

