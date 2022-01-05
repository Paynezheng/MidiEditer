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

double MidiConventer::GetBeat(int tick) {
    return double(tick)/m_midifile->getTicksPerQuarterNote();
}

void MidiConventer::QuantifyTrack(int track, int duration) {
    std::cout << "\nQuantifyTrack " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    std::cout<<std::endl;
    for (int event=0; event< midi_events.size(); event++) {
        // TODO: 需要移动两个事件(on && off)
        // 一个note不能越过小节线
        // 一个note不能跨和弦
        if (midi_events[event].isNoteOn()) {
            QuantifyEvent(midi_events[event], 8, m_midifile->getTicksPerQuarterNote(), 0);
            MidiEvent* offevent = midi_events[event].getLinkedEvent();
            QuantifyEvent(*offevent, 8, m_midifile->getTicksPerQuarterNote(), 0);
        }
    }
    // m_midifile->sortTracks();
}

void MidiConventer::QuantifyEvent(MidiEvent& midievent, int unit_size, int tpq, int direction) {
    // TODO： 将事件移动到最近的节点上
    std::cout<< std::dec << GetBeat(midievent.tick);
    double left_beat = 0;
    double right_beat = 0;
    switch(unit_size) {
        case 4:
            left_beat = (int)GetBeat(midievent.tick);
            right_beat = left_beat + 1;
            break;
        case 8:
            left_beat = (int)(GetBeat(midievent.tick)/0.5) * 0.5;
            right_beat = left_beat + 0.5;
            break;
        case 16:
            left_beat = (int)(GetBeat(midievent.tick)/0.25) * 0.25;
            right_beat = left_beat + 0.25;
            break;
        default:
            return;
    }
    // 向左移
    if (direction == -1) {
        midievent.tick = int((left_beat - 4.0 / unit_size)*tpq);
        return;
    }
    int left_tick = int(left_beat*tpq);
    int right_tick = int(right_beat*tpq);
    if (midievent.tick - left_tick > right_tick - midievent.tick)
        midievent.tick = right_tick;
    else
        midievent.tick = left_tick;
    std::cout<< '\t' << GetBeat(midievent.tick) << std::endl;
}

bool MidiConventer::IsChordInterior(const MidiEvent& midievent)
{
    return m_chord_progression->IsChordInterior((int)GetBeat(midievent.tick), midievent.getKeyNumber());
}

void MidiConventer::CleanChordVoiceover(int track) {
    std::cout << "\nCleanChordVoiceover Track " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        if (midi_events[event].isNoteOn()) {
            if (midi_events[event].isNote() && !IsChordInterior(midi_events[event])) {
                midi_events[event].clear();
            }
        }
    }
    m_midifile->removeEmpties();
    // m_midifile->sortTracks();
}

void MidiConventer::CleanRecurNotes(int track) {
    std::cout << "\nCleanRecurNotes Track " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        // MidiEventList::eventcompare 保证了MidiEventList的时间序
        // 读on事件后，off事件出现前所有的onnote都删除
        if (midi_events[event].isNote()) {
            if (event-1 >= 0 && midi_events[event-1].isNote() && 
                midi_events[event-1].tick == midi_events[event].tick) {
                MidiEvent* offevent = midi_events[event].getLinkedEvent();
                midi_events[event].clear();
                if (offevent != nullptr) 
                    offevent->clear();
            }
        }
    }
    m_midifile->removeEmpties();
}
	
void MidiConventer::ProlongNotes(int track) {
    std::cout << "TicksPerQuarterNote(TPQ): " << m_midifile->getTicksPerQuarterNote() << std::endl;
    std::cout << "\nQuantifyTrack " << track << std::endl;
    MidiEventList& midi_events = (*m_midifile)[track];
    for (int event=0; event< midi_events.size(); event++) {
        if (midi_events[event].isNoteOn()) {
            MidiEvent* offevent = midi_events[event].getLinkedEvent();      // 应该这个就是这个音的结束事件...
            if (offevent != nullptr) {
                double tar_beat = (int)(GetBeat(midi_events[event].tick)/0.5) * 0.5;
            }
            // set off event tick
        }
    }
    m_midifile->removeEmpties();
}

void MidiConventer::PrintMidifile() {
    int tracks = m_midifile->getTrackCount();
    std::cout << "TicksPerQuarterNote(TPQ): " << m_midifile->getTicksPerQuarterNote() << std::endl;
    if (tracks > 1) std::cout << "TRACKS: " << tracks << std::endl;
    for (int track=0; track<tracks; track++) {
        std::cout << "\nTrack " << track << std::endl;
        std::cout << "Tick\tSeconds\tDur\tbeat\tMessage" << std::endl;
        const MidiEventList& midi_events = (*m_midifile)[track];
        for (int event=0; event< midi_events.size(); event++) {
            std::cout << std::dec << midi_events[event].tick;
            std::cout << '\t' << std::dec << midi_events[event].seconds;
            std::cout << '\t';
            if (midi_events[event].isNoteOn())
            std::cout << midi_events[event].getDurationInSeconds();
            std::cout << '\t';
            std::cout<< std::dec << GetBeat(midi_events[event].tick);
            std::cout << '\t' << std::hex;
            for (auto i=0; i<midi_events[event].size(); i++)
            std::cout << (int)midi_events[event][i] << ' ';
            // std::cout<< '\t';
            // std::cout<< std::dec << midi_events[event].getKeyNumber();   // 输出音符
            std::cout<< '\t';
            std::cout<< std::endl;
        }
        std::cout<<std::endl;
    }
}

bool MidiConventer::IsNoteValid(MidiEvent& on, MidiEvent& off) {

}

} // end namespace smf

