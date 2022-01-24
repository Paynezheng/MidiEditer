//
// Programmer:    Payne Zheng <photosynthesi@outlook.com>
// Creation Date: Mon Dec 27 10:22:56 UTC 2021
// Last Modified: Mon Dec 27 10:22:56 UTC 2021
// Filename:      midiediter/test/MidiReader.cpp
// Syntax:        C++11
// Code           UTF-8
//


#include "MidiFile.h"
#include "smflog.h"
#include "Options.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
   SMF_LOG_TRACE("hello,world%d", 10086);
   SMF_LOG_WARN("hello,world%d", 10086);
   SMF_LOG_INFO("hello,world%d", 10086);
   SMF_LOG_DEBUG("hello,world%d", 10086);
   SMF_LOG_FATAL("hello,world%d", 10086);
   SMF_LOG_ERROR("hello,world%d", 10086);  
   // Options options;
   // options.process(argc, argv);
   // MidiFile midifile;
   // if (options.getArgCount() == 0) midifile.read(cin);
   // else midifile.read(options.getArg(1));
   // midifile.doTimeAnalysis();
   // midifile.linkNotePairs();

   // int tracks = midifile.getTrackCount();
   // cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
   // if (tracks > 1) cout << "TRACKS: " << tracks << endl;
   // for (int track=0; track<tracks; track++) {
   //    if (tracks > 1) cout << "\nTrack " << track << endl;
   //    cout << "Tick\tSeconds\tDur\tSeq\tMessage" << endl;
   //    for (int event=0; event<midifile[track].size(); event++) {
   //       cout << dec << midifile[track][event].tick;
   //       cout << '\t' << dec << midifile[track][event].seconds;
   //       cout << '\t';
   //       if (midifile[track][event].isNoteOn())
   //          cout << midifile[track][event].getDurationInSeconds();
   //       cout << '\t';
   //       cout<< midifile[track][event].seq;
   //       cout << '\t' << hex;
   //       for (auto i=0; i<midifile[track][event].size(); i++)
   //          cout << (int)midifile[track][event][i] << ' ';
   //       cout<< '\t';
   //       cout<< dec << midifile[track][event].getKeyNumber();   // 输出音符
   //       cout << endl;
   //    }
   // }

   return 0;
}