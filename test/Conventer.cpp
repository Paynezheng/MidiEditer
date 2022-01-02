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
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {
    if (argc != 4)
    {
        cout<< "--> param num error <--"<<endl;
        cout<< "./Conventer input_midifile_chord input_midifile 1/2" <<endl;
        return -1;
    }
    
}