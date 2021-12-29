//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed Dec 29 02:02:10 UTC 2021
// Last Modified: Wed Dec 29 02:02:10 UTC 2021
// Filename:      midiediter/src/MidiConventer.cpp
// Syntax:        C++11
// Code           UTF-8
//

#include "MidiConventer.h"
#include <stdlib.h>


namespace smf {

MidiConventer::MidiConventer(MidiFile* midifile, ChordProgression chord_progression, int duration)
    :m_midifile(midifile), m_chord_progression(chord_progression), m_duration(duration){

}

void MidiConventer::Reset(){
    m_midifile          = nullptr;
    m_duration          = 0;
    m_chord_progression.Reset();
}


} // end namespace smf

