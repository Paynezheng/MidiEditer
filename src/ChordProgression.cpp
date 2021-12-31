#include "ChordProgression.h"
#include <vector>

namespace smf {
Chord::Chord(int chord_base, int chord_name):m_chord_base(chord_base), m_chord_name(chord_name) {
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
        case EN_CHORD_NAME__SUS4_SEVENTH:
            m_notes.push_back(chord_interior_base);
            m_notes.push_back((chord_interior_base + 5) % 12);
            m_notes.push_back((chord_interior_base + 7) % 12);
            m_notes.push_back((chord_interior_base + 10) % 12);
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
        case EN_CHORD_PROGRESSIONS_TYPE__Dm7_G7_CM7_Am7:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__D, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__SUS4_SEVENTH), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR_SEVENTH), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            break;
        case EN_CHORD_PROGRESSIONS_TYPE__1_4M7_6m7_5sus4_5:
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__C, EN_CHORD_NAME__MAJOR), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__F, EN_CHORD_NAME__MAJOR_SEVENTH), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__A, EN_CHORD_NAME__MINOR_SEVENTH), 4));
            m_chords.emplace(1, std::make_tuple(Chord(EN_NOTE__G, EN_CHORD_NAME__MINOR_SEVENTH), 2));
        default:
            return;
    }
}

void ChordProgression::Init(std::vector<std::tuple<int, int>>& chords) {
    // TODO
}	

void ChordProgression::Reset() {
    m_chords.clear();
}

} // end namespace smf