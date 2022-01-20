//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Tue Jan 18 12:35:55 UTC 2022
// Last Modified: Tue Jan 18 12:35:55 UTC 2022
// Filename:      midiediter/src/MidiNote.cpp
// Syntax:        C++11
// Code           UTF-8
//

#include "MidiNote.h"
#include "MidiEvent.h"

namespace smf {

const MidiEvent&  MidiNote::GetBeginEvent()
{
    return m_begin_event;
}

const MidiEvent&  MidiNote::GetEndEvent()
{
    return m_end_event;
}


int MidiNote::GetBeginTick()
{
    return m_begin_tick;
}
int MidiNote::GetEndTick()
{
    return m_end_tick;
}

std::vector<MidiNote*> MidiNote::CutNote(MidiNote* origin_note, std::map<int, std::vector<MidiNote*>>& block_index, int block_length)
{

}


} // end of namespace smf