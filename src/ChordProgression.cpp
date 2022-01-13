//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Fri Dec 31 03:34:58 UTC 2021
// Last Modified: Thu Jan  6 07:17:45 UTC 2022
// Filename:      midiediter/include/ChordProgression.cpp
// Syntax:        C++11
// Code           UTF-8
//

#include "ChordProgression.h"
#include <vector>

namespace smf {
Chord::Chord(int chord_base, int chord_name):m_chord_base(chord_base), m_chord_name(chord_name) {
    // FIXME: make it easier...
    int chord_interior_base = chord_base % 12;
    switch(m_chord_name){
        case EN_CHORD_NAME__MAJOR:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 4) % 12);     // 根音到三音中间间隔四个半音
            m_notes.push_back((chord_interior_base + 7) % 12);     // 根音到五音中间间隔7个半音
            break;
        case EN_CHORD_NAME__MINOR:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 3) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            break;
        case EN_CHORD_NAME__SUS4:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 5) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            break;
        case EN_CHORD_NAME__MAJOR_SEVENTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 4) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 11) % 12);
            break;
        case EN_CHORD_NAME__MINOR_SEVENTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 3) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 10) % 12);
            break;
        case EN_CHORD_NAME__DOMINANT_SEVENTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 4) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 10) % 12);
            break;
        case EN_CHORD_NAME__SUS4_SEVENTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 5) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 11) % 12);
        case EN_CHORD_NAME__DOMINANT_NINTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 4) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 10) % 12);
            m_notes.push_back((chord_interior_base + 14) % 12);
        default:
            return;
    }
}

bool Chord::IsChordInterior(int key) {
    const int key_base = key % 12;
    for (auto i: m_notes) {
        if(i == key_base)
            return true;
    }
    return false;
}

ChordProgression::ChordProgression(int chord_progression_id) {
    switch(chord_progression_id){
        case EN_CHORD_PROGRESSIONS_TYPE__C_BLUES:
        case EN_CHORD_PROGRESSIONS_TYPE__CM7_Am7_Dm7_G7:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR_SEVENTH), 4));
            m_chords.emplace(2, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            m_chords.emplace(3, std::make_tuple(Chord(EN_NOTE__D, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            m_chords.emplace(4, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__DOMINANT_SEVENTH), 4));
            m_beats = 16;
            break;
        case EN_CHORD_PROGRESSIONS_TYPE__1_4M7_6m7_5sus4_5:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(2, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__MAJOR_SEVENTH), 4));
            m_chords.emplace(3, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            m_chords.emplace(4, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__SUS4), 2));
            m_chords.emplace(5, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__MAJOR), 2));
            m_beats = 16;
        case EN_CHORD_PROGRESSIONS_TYPE__C_F_Am_G:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(2, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(3, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR), 4));
            m_chords.emplace(4, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__MAJOR), 4));
            m_beats = 16;
        case EN_CHORD_PROGRESSIONS_TYPE__Am_G_F9_F9:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR), 4));
            m_chords.emplace(2, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(3, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__DOMINANT_NINTH), 4));
            m_chords.emplace(4, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__DOMINANT_NINTH), 4));
            m_beats = 16;
        case EN_CHORD_PROGRESSIONS_TYPE__Am_G_F_C:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR), 4));
            m_chords.emplace(2, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(3, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(4, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR), 4));
            m_beats = 16;
        default:
            return;
    }
}

void ChordProgression::Init(std::vector<std::tuple<int, int, int>>& chords) {
    // TODO: 
}	

void ChordProgression::Reset() {
    m_chords.clear();
}

bool ChordProgression::IsChordInterior(int beat, int key) {
    int pos = beat%m_beats;
    int chord_begin_beat = 0;
    for (auto iter: m_chords) {
        if(chord_begin_beat + std::get<1>(iter.second) >= pos) {
            Chord& chord = std::get<0>(iter.second);
            return chord.IsChordInterior(key);
        }
        else {
            chord_begin_beat += std::get<1>(iter.second);
        }
    }
    return false;
}

/**
 * @brief 根据拍数&音名, 判断是否为和弦内音. 提供一个更细粒度的查询
 * @param beat 第几拍
 * @param key 音名
 * @return true 
 * @return false 
 */
bool ChordProgression::IsChordInterior(double beat, int key) {
    double pos = beat;
    while(pos > m_beats) {
        pos -= m_beats;
    }
    double chord_begin_beat = 0;
    for (auto iter: m_chords) {
        if(chord_begin_beat + std::get<1>(iter.second) >= pos) {
            Chord& chord = std::get<0>(iter.second);
            return chord.IsChordInterior(key);
        }
        else {
            chord_begin_beat += std::get<1>(iter.second);
        }
    }
    return false;
}

/**
 * @brief 获取当前和弦的序号，和弦的序号从1开始，并一次递增
 * @param beat 当前事件 第几拍
 * @param event_type 判断on/off属于哪个和弦时, 切换和弦的节点上on属于下一个和弦, off属于上一个和弦; midi开始节点(0时刻), 两种事件都属于第一个和弦. on->0|off->1 
 * @return int 
 */
int	ChordProgression::GetChordSeq(double beat, int event_type) {
    if (beat == 0) return 1;
    double  pos = beat;
    int     seq = 1;        // 用于表示和弦序号 .
    int     chord_num = m_chords.size();
    while(pos > m_beats) {
        pos -= m_beats;
        seq += chord_num;
    }
    double chord_begin_beat = 0;
    for (auto iter: m_chords) {
        if(chord_begin_beat + std::get<1>(iter.second) > pos) {
            return seq;
        }
        else if (chord_begin_beat + std::get<1>(iter.second) == pos)
        {
            return event_type == 0 ? (seq+1) : seq;
        }
        else {
            chord_begin_beat += std::get<1>(iter.second);
            seq += 1;
        }
    }
    return seq;
}

/**
 * @brief Get the Chord object
 * @param seq 
 * @return std::tuple<Chord, int, int> Chord, 和弦起始拍, 和弦长度
 */
std::tuple<Chord, int, int>	ChordProgression::GetChord(int seq) {
    int chord_num   = m_chords.size();
    int end_beat    = 0;
    int chord_len   = std::get<1>(m_chords[chord_num]);
    end_beat += m_beats * seq/chord_num;
    int i;
    for (i=1; i<=seq%chord_num; i++) {
        chord_len = std::get<1>(m_chords[i]);
        end_beat += chord_len;
    }
    return std::make_tuple(std::get<0>(m_chords[i-1]), end_beat-chord_len+1, chord_len);
}

} // end namespace smf