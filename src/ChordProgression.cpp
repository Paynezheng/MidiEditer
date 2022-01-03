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

} // end namespace smf