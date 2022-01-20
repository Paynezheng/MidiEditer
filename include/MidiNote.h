//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Tue Jan 18 12:35:55 UTC 2022
// Last Modified: Tue Jan 18 12:35:55 UTC 2022
// Filename:      midiediter/include/MidiNote.h
// Syntax:        C++11
// Code           UTF-8
//


#pragma once
#include "MidiEvent.h"
#include <vector>
#include <map>

namespace smf {

class MidiNote{
public:
    MidiNote(): m_begin_tick(0), m_end_tick(0)
    {}

    MidiNote(MidiEvent begin_event, MidiEvent end_event)
    {
        m_begin_event   = begin_event; 
        m_end_event     = end_event;
        m_begin_tick    = begin_event.tick; 
        m_end_tick      = end_event.tick;
    }

public:
    const MidiEvent&  GetBeginEvent();
    const MidiEvent&  GetEndEvent();
    int         GetBeginTick();
    int         GetEndTick();

public:
    static void CutNote(MidiNote* origin_note, std::map<int, std::vector<MidiNote*>>& block_index, std::vector<MidiNote*>& result, int block_length);

private:
    MidiEvent   m_begin_event;
    MidiEvent   m_end_event;
    int         m_begin_tick;
    int         m_end_tick;
}

} // end of namespace smf