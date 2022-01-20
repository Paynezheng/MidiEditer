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

void MidiNote::CutNote(MidiNote* origin_note, std::map<int, std::vector<MidiNote*>>& block_index, std::vector<MidiNote*>& result, int block_length)
{
    int cur_begin_tick  = origin_note->GetBeginTick();
    int cur_end_tick    = cur_begin_tick;
    int end_tick    = origin_note->GetEndTick();
    while(cur_end_tick < end_tick) {
        /**
         * @brief TODO: 把音裁剪后放进result
         * 
         */
        int block_id = cur_end_tick/block_length;
    }
}


} // end of namespace smf