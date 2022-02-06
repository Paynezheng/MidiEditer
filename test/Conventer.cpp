//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Sun Jan  2 10:10:51 CST 2022
// Last Modified: Sun Jan  2 10:10:51 CST 2022
// Filename:      midiediter/test/Conventer.cpp
// Syntax:        C++11
// Code           UTF-8
// Usage:         interface
//


#include "MidiFile.h"
#include "MidiConventer.h"
#include "smflog.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
    if (argc != 3)
    {
        SMF_LOG_ERROR("--> param num error <--");
        SMF_LOG_ERROR("./Conventer input_midifile 1(C_F_Am_G)/2(Am_G_F_C)");
        return -1;
    }

    int param_chord_progression = atoi(argv[2]); // 先默认一个1625
    ChordProgression chord_progression;
    MidiConventer midi_conventer;
    if (param_chord_progression == 1625 || param_chord_progression == 1) {
        chord_progression = ChordProgression(EN_CHORD_PROGRESSIONS_TYPE__C_F_Am_G);    // 1625
        midi_conventer = MidiConventer(argv[1], chord_progression, 8);
    }
    else {
        chord_progression = ChordProgression(EN_CHORD_PROGRESSIONS_TYPE__Am_G_F_C);
        midi_conventer = MidiConventer(argv[1], chord_progression, 16);
    }
    int tracks = midi_conventer.getTrackCount();

    for (int track = 0; track < tracks; track++) {
        midi_conventer.QuantifyTrack(track);
        midi_conventer.CleanRecurNotes(track);
        midi_conventer.QualifyVol(track);
        midi_conventer.SetBPM(track, 100);

        // midi_conventer.ProlongNotes(track);
    }

    midi_conventer.Write2File(argv[1]);

}