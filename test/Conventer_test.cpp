//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Wed Dec 29 13:07:57 UTC 2021
// Last Modified: Wed Dec 29 13:07:57 UTC 2021
// Filename:      midiediter/test/Conventer_test.cpp
// Syntax:        C++11
// Code           UTF-8
// Usage:         测试代码
//


#include "MidiFile.h"
#include "MidiConventer.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
    Chord chord_test(EN_NOTE__C, EN_CHORD_NAME__MAJOR_SEVENTH);
    cout<< chord_test.IsChordInterior(EN_NOTE__C + 36) << endl;
    cout<< chord_test.IsChordInterior(EN_NOTE__C_SHARP + 48) << endl;

    ChordProgression* chord_progression_test = new ChordProgression(EN_CHORD_PROGRESSIONS_TYPE__1_4M7_6m7_5sus4_5);
    cout<< "index" << "\t" << "chord" << "\t\t" << "duration" << endl;
    for (auto it:chord_progression_test->m_chords) {
        cout<< it.first << "\t";
        for (auto i: get<0>(it.second).m_notes)
        {
            cout<< i << " ";
        }
        cout<< "\t" << get<1>(it.second) << endl;
    }

    if (argc != 2)
    {
        cout<< "--> param num error <--"<<endl;
        cout<< "./Conventer_test midifile" <<endl;
        return -1;
    }
    MidiFile* midifile = new MidiFile();
    midifile->read(argv[1]);
    midifile->doTimeAnalysis();
    midifile->linkNotePairs();

    int tracks = midifile->getTrackCount();
    if (tracks == 1) {
        MidiConventer* midi_conventer = new MidiConventer(midifile, chord_progression_test, 1);
        midi_conventer->QuantifyTrack(0, 1);
    }
    return 0;
}