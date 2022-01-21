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
#include <algorithm>

namespace smf
{

MidiEvent&  MidiNote::GetBeginEvent()
{
    return m_begin_event;
}

MidiEvent&  MidiNote::GetEndEvent()
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

// set

void MidiNote::CutNote(MidiNote* origin_note, std::map<int, std::vector<MidiNote*>>& block_index, std::vector<MidiNote*>& result, int block_length)
{
    MidiNote* new_note = new MidiNote();
    int cur_begin_tick  = origin_note->GetBeginTick();
    int cur_end_tick    = cur_begin_tick;
    int end_tick    = origin_note->GetEndTick();
    printf("pre_note: begin: %d, end: %d", cur_begin_tick, end_tick);
    while(cur_end_tick < end_tick)
    {
        int block_id = cur_end_tick/block_length;
        if (find(block_index[block_id].begin(), block_index[block_id].end(), origin_note) == block_index[block_id].end())
        {
            // 此block中不含此音
            if (cur_begin_tick != -1)
            {
                if (cur_end_tick - cur_begin_tick != 0)
                {
                    // new长度为的cur_end_tick - cur_begin_tick可用的音
                    result.push_back(CutOneNote(origin_note, cur_begin_tick, cur_end_tick));
                }
            }
            else
            {
                // 无当前音
            }
            cur_begin_tick = -1;
        }
        else
        {
            if (cur_begin_tick != -1)
            {
                // 继续当前音
            }
            else
            {
                cur_begin_tick = cur_end_tick;
            }
        }
        cur_end_tick += block_length;
    }
    if (cur_begin_tick != -1)
    {
        // new长度为的end_tick - cur_begin_tick可用的音
        result.push_back(CutOneNote(origin_note, cur_begin_tick, end_tick));
    }
    for (auto it : result)
    {
        printf("after_note: begin: %d, end: %d", it->GetBeginTick(), it->GetEndTick());
    }
}

MidiNote* MidiNote::CutOneNote(MidiNote* origin_note, int begin_tick, int end_tick)
{
    MidiEvent* begin_event  = new MidiEvent(origin_note->GetBeginEvent());
    MidiEvent* end_event    = new MidiEvent(origin_note->GetEndEvent());
    begin_event->linkEvent(end_event);
    MidiNote* new_note = new MidiNote(*begin_event, *end_event);
    return new_note;
}


} // end of namespace smf