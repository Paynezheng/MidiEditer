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
#include <getopt.h>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

    string  filename;
    double  bpm = 0;
    int     chord = 0;
    bool    timing_qualify = false;
    bool    rm_notes = false;
    bool    vol_qualify = false;

    char    param;

    while ((param = getopt(argc, argv, "f:b:c:trv")) != EOF)
    {
        switch (param)
        {
            case 'f':
                filename = optarg;
                break;
            case 'b':
                bpm = atof(optarg);
                break;
            case 'c':
                chord = atoi(optarg);
                break;
            case 't':
                timing_qualify = true;
                break;
            case 'r':
                rm_notes = true;
                break;
            case 'v':
                vol_qualify = true;
                break;
            default:
                break;
        }
    }


    // if (argc != 3)
    // {
    //     SMF_LOG_ERROR("--> param num error <--");
    //     SMF_LOG_ERROR("./Conventer input_midifile 1(C_F_Am_G)/2(Am_G_F_C)");
    //     return -1;
    // }


    ChordProgression chord_progression;
    MidiConventer midi_conventer;
    if (chord == 1625 || chord == 1) {
        chord_progression = ChordProgression(EN_CHORD_PROGRESSIONS_TYPE__C_F_Am_G);
        midi_conventer = MidiConventer(filename, chord_progression, 8);
    }
    else if (chord == 2)
    {
        chord_progression = ChordProgression(EN_CHORD_PROGRESSIONS_TYPE__Am_G_F_C);
        midi_conventer = MidiConventer(filename, chord_progression, 16);
    }
    else
    {
        SMF_LOG_ERROR("Unknown chord");
    }


    int tracks = midi_conventer.getTrackCount();

    for (int track = 0; track < tracks; track++) {
        if (timing_qualify)
        {
            midi_conventer.QuantifyTrack(track);    // 量化
        }
        if (rm_notes)
        {
            midi_conventer.CleanRecurNotes(track);  // 去重
        }
        if (vol_qualify)
        {
            midi_conventer.QualifyVol(track);       // 力度量化
        }
        if (bpm != 0)
        {
            midi_conventer.SetBPM(track, bpm);      // 设置bpm
        }
        // midi_conventer.ProlongNotes(track);
    }

    midi_conventer.Write2File(filename);

}