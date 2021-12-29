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
    cout<< chord_test.IsChordInterior(48) << endl;
    cout<< chord_test.IsChordInterior(49) << endl;
    return 0;
}