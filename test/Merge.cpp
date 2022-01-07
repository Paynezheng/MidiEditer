//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Fri Jan  7 06:33:55 UTC 2022
// Last Modified: Fri Jan  7 06:33:55 UTC 2022
// Filename:      midiediter/test/Merge.cpp
// Syntax:        C++11
// Code           UTF-8
// Usage:         interface
//


#include "MidiFile.h"
#include "MidiConventer.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
    cout<< "merge file to second file"<<endl;
    if (argc != 3)
    {
        cout<< "--> param num error <--"<<endl;
        cout<< "./Conventer input_midifile_chord input_midifile" <<endl;
        return -1;
    }
    MidiFile* chord = new MidiFile(argv[1]);
    MidiFile* input_user = new MidiFile(argv[2]);
    chord->doTimeAnalysis();
    input_user->doTimeAnalysis();
    chord->linkNotePairs();
    input_user->linkNotePairs();

    if (chord->getTicksPerQuarterNote() != input_user->getTicksPerQuarterNote()) {
        cout<< "file tpq not the same" <<endl;
        return -1;
    }
    int chord_tracks = chord->getTrackCount();
    int user_tracks = input_user->getTrackCount();

    input_user->addTracks(chord_tracks);
    for (int track = 0; track < chord_tracks; track++) {
        MidiEventList& event_list = (*chord)[track];
        for (int i=0; i<event_list.size(); i++) {
            if (event_list[i].isNoteOn())
                input_user->addNoteOn(track + user_tracks, event_list[i].tick, event_list[i].getChannel(), event_list[i].getKeyNumber(), event_list[i].getVelocity());
            else if (event_list[i].isNoteOff())
                input_user->addNoteOff(track + user_tracks, event_list[i].tick, event_list[i].getChannel(), event_list[i].getKeyNumber());
        }
    }
    input_user->sortTracks();
    input_user->write(argv[2]);

}