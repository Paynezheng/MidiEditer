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

namespace smf{
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
	EN_CHORD_NAME__SUS4_SEVENTH			= 5  // sus4
};

} // end of namespace smf