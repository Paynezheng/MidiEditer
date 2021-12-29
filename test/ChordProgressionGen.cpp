//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Tue Dec 28 10:12:18 UTC 2021
// Last Modified: Wed Dec 29 02:14:53 UTC 2021 Rename test/MidiConventer.cpp
// Filename:      midiediter/test/ChordProgressionGen.cpp
// Syntax:        C++11
// Code           UTF-8
// Usage:         生成指定和弦进行的单轨midi文件
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
        cout<< "./ChordProgressionGen midifile" <<endl;
        return -1;
    }
    MidiFile midifile;
    string filename = argv[1];
    cout<< filename << endl;
    
    int Notes[] =  {48, 50, 52, 53, 55, 57, 59};    // C D E F G A B

    int track   = 0;        // 默认0轨道
    int channel = 0;
    int instr   = 0;        // 默认为0
    midifile.addTimbre(track, 0, channel, instr);
    midifile.setTPQ(108);
    int tpq     = midifile.getTPQ();    // 没有设置的情况按照默认的bpm

    // tpq表示bpm，也用来表示相对时间戳(tick), delta tick == tpq时, 事件时长为1拍
    for (int i= 0; i < 7; i++) {
        int starttick = int(tpq * (i+1));                   // 固定音长
        int key       = Notes[i];                           // 取得音在C大调上
        int endtick   = starttick + int(tpq * (i+2));       // 固定音长
        midifile.addNoteOn(track, starttick, channel, key, 40);
        midifile.addNoteOff(track, endtick, channel, key);
    }
    midifile.sortTracks();  // Need to sort tracks since added events are
                            // appended to track in random tick order.
    midifile.write(filename);

    return 0;
}