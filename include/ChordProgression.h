//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Fri Dec 31 03:34:58 UTC 2021
// Last Modified: Fri Dec 31 03:34:58 UTC 2021
// Filename:      midiediter/include/ChordProgression.h
// Syntax:        C++11
// Code           UTF-8
//

#pragma once
#include <vector>
#include <map>
/**
 * @brief 1           1-3-5
4maj7   4-6-1-3
6m7     6 1 3 5
5sus4   5-1-2/5  5-7-2
 * 
 */
namespace smf{
enum ENoteDuration {
	EN_NOTE_DURATION__MUTE					= 0,
	EN_NOTE_DURATION__WHOLE					= 1,	// 全音符
	EN_NOTE_DURATION__HALF					= 2,	// 二分
	EN_NOTE_DURATION__QUARTER				= 3,	// 四分
	EN_NOTE_DURATION__QUAVER				= 4,	// 八分
	EN_NOTE_DURATION__SEMIQUAVER			= 5,	// 十六分
	EN_NOTE_DURATION__END					= 6
};

enum EChordProgressions {
	EN_CHORD_PROGRESSIONS_TYPE__C_BLUES						= 0,			// 12小节蓝调
	EN_CHORD_PROGRESSIONS_TYPE__CM7_Am7_Dm7_G7 				= 1,			// 1625
	EN_CHORD_PROGRESSIONS_TYPE__1_4M7_6m7_5sus4_5			= 2,			// 
	END														= 3 		
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
	EN_CHORD_NAME__EMPTY				= 0, // 空
	EN_CHORD_NAME__MAJOR				= 1, // 大三和弦
	EN_CHORD_NAME__MINOR				= 2, // 小三
	EN_CHORD_NAME__SUS4					= 3, // sus4	


	// SEVENTH CHORD
	EN_CHORD_NAME__MAJOR_SEVENTH		= 100, // 大七
	EN_CHORD_NAME__MINOR_SEVENTH		= 101, // 小七
	EN_CHORD_NAME__DOMINANT_SEVENTH		= 102, // dominant_seventh
	EN_CHORD_NAME__SUS4_SEVENTH			= 103,  // sus4_minor_7

	EN_CHORD_NAME__END					= 104
};


class Chord {
public:
	Chord();
	Chord(int chord_base, int chord_name);
	bool 		IsChordInterior(int key);

	int 		m_chord_base = 0;			// 和弦根音
	int 		m_chord_name = 0;			// 和弦名
	std::vector<int>		m_notes;
};

/**
 * @brief 和弦进行类, 后续如果有特别的需求可以新写一个和弦进行类来初始化MidiConventer
 * 			
 */
class ChordProgression {
public:
	ChordProgression(int chord_progression_id);
	ChordProgression(int chord_progression_id, int modulation);						// TODO:提供转调
	void 		Init(std::vector<std::tuple<int, int, int>>& chords);				// TODO:index-><chord_enum, chord_base, chord_duration>
	void 		Reset();
	bool		IsChordInterior(int beat, int key);
	bool		IsChordInterior(double beat, int key);
	int			GetChordSeq(double beat, int event_type);
	std::tuple<Chord, int, int>	GetChord(int seq);
// private:
	std::map<int, std::tuple<Chord, int>>		m_chords;		// 序号-><和弦, beats> 
	int			m_beats;	// 一共有几拍
};

} // end of namespace smf