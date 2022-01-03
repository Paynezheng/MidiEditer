//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed std::dec 29 02:02:10 UTC 2021
// Last Modified: Wed std::dec 29 09:37:18 UTC 2021
// Filename:      midiediter/src/MidiConventer.cpp
// Syntax:        C++11
// Code           UTF-8
//

#include "MidiConventer.h"
#include <stdlib.h>
#include <iostream>


namespace smf {

MidiConventer::MidiConventer(MidiFile* midifile, ChordProgression* chord_progression, int duration)
    :m_midifile(midifile), m_chord_progression(chord_progression), m_duration(duration) {
}

void MidiConventer::Reset() {
    m_midifile          = nullptr;
    m_duration          = 0;
    m_chord_progression = nullptr;
}

double MidiConventer::GetBeat(int tick, int tpq) {
    return double(tick)/tpq;
}

void MidiConventer::QuantifyTrack(int track, int duration) {
    std::cout << "TicksPerQuarterNote(TPQ): " << m_midifile->getTicksPerQuarterNote() << std::endl;
    std::cout << "\nQuantifyTrack " << track << std::endl;
    std::cout << "Tick\tSeconds\tDur\tMessage\t\tbeat" << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        std::cout << std::dec << midi_events[event].tick;
        std::cout << '\t' << std::dec << midi_events[event].seconds;
        std::cout << '\t';
        if (midi_events[event].isNoteOn())
        std::cout << midi_events[event].getDurationInSeconds();
        std::cout << '\t' << std::hex;
        for (auto i=0; i<midi_events[event].size(); i++)
        std::cout << (int)midi_events[event][i] << ' ';
        // std::cout<< '\t';
        // std::cout<< std::dec << midi_events[event].getKeyNumber();   // 输出音符
        std::cout<< '\t';
        std::cout<< std::dec << GetBeat(midi_events[event].tick, m_midifile->getTicksPerQuarterNote());
        std::cout<< std::endl;

        // me->makeNoteOn(aChannel, key, vel);
	    // me->tick = aTick;
    }
    std::cout<<std::endl;
    for (int event=0; event< midi_events.size(); event++) {
        if (midi_events[event].isNoteOn()) {
            QuantifyEvent(midi_events[event], 8, m_midifile->getTicksPerQuarterNote(), 0);
        }
    }
    // m_midifile->sortTracks();
}

void MidiConventer::QuantifyEvent(MidiEvent& midievent, int unit_size, int tpq, int direction) {
    std::cout<< std::dec << GetBeat(midievent.tick, tpq);
    double tar_beat = 0;
    switch(unit_size) {
        case 4:
            tar_beat = (int)GetBeat(midievent.tick, tpq);
            midievent.tick = int(tar_beat*tpq);
            break;
        case 8:
            tar_beat = (int)(GetBeat(midievent.tick, tpq)/0.5) * 0.5;
            midievent.tick = int(tar_beat*tpq);
            break;
        case 16:
            tar_beat = (int)(GetBeat(midievent.tick, tpq)/0.25) * 0.25;
            midievent.tick = int(tar_beat*tpq);
        default:
            return;
    }
    std::cout<< '\t' << GetBeat(midievent.tick, tpq) << std::endl;
}

bool MidiConventer::IsChordInterior(const MidiEvent& midievent)
{
    return m_chord_progression->IsChordInterior((int)GetBeat(midievent.tick, m_midifile->getTicksPerQuarterNote()), midievent.getKeyNumber());
}

void MidiConventer::CleanChordVoiceover(int track) {
    std::cout << "TicksPerQuarterNote(TPQ): " << m_midifile->getTicksPerQuarterNote() << std::endl;
    std::cout << "\nQuantifyTrack " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        if (midi_events[event].isNoteOn()) {
            // int key = midi_events[event].getKeyNumber();
            // if (key%12 < 7)
            // {
            //     midi_events[event].clear();
            // }
            if (!IsChordInterior(midi_events[event]))
            {
                midi_events[event].clear();
            }
        }
    }
    m_midifile->removeEmpties();
    // m_midifile->sortTracks();
}

void MidiConventer::CleanRecurNotes(int track) {
    std::cout << "TicksPerQuarterNote(TPQ): " << m_midifile->getTicksPerQuarterNote() << std::endl;
    std::cout << "\nQuantifyTrack " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        if (midi_events[event].isNoteOn()) {
            // int key = midi_events[event].getKeyNumber();
            // if (key%12 < 7)
            // {
            //     midi_events[event].clear();
            // }
            if (!IsChordInterior(midi_events[event]))
            {
                midi_events[event].clear();
            }
        }
    }
    // TODO: Delete Recur Notes
}
	
void MidiConventer::ProlongNotes(int track) {
    // TODO: Prolong Notes
}

} // end namespace smf

