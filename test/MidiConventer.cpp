//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Tue Dec 28 10:12:18 UTC 2021
// Last Modified: Tue Dec 28 10:12:18 UTC 2021
// Filename:      midiediter/test/MidiConventer.cpp
// Syntax:        C++11
// Code           UTF-8
//


#include "MidiFile.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
    if (argc != 2)
    {
        cout<< "--> param num error <--"<<endl;
        cout<< "./MidiConventer midifile" <<endl;
        return -1;
    }
    MidiFile midifile;
    string filename = argv[1];
    cout<< filename << endl;
    
    int Notes[] =  {48, 50, 52, 53, 55, 57, 59};

    int track   = 0;        // 默认0轨道
    int channel = 0;
    int instr   = 0;        // 默认为0
    midifile.addTimbre(track, 0, channel, instr);
    midifile.setTPQ(108);
    int tpq     = midifile.getTPQ();    // 没有设置的情况按照默认的bpm
    // 7个音
    for (int i= 0; i < 7; i++) {
        int starttick = int(10 * (i+1) / 4.0 * tpq);            // 固定音长
        int key       = Notes[i];                               // 取得音在C大调上
        int endtick   = starttick + int(1 / 4.0 * tpq);         // 固定音长
        midifile.addNoteOn(track, starttick, channel, key, 40);
        midifile.addNoteOff(track, endtick, channel, key);
    }
    midifile.sortTracks();  // Need to sort tracks since added events are
                            // appended to track in random tick order.
    midifile.write(filename);

    return 0;
}