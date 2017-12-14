//
// Created by casper on 11.12.2017.
//

#ifndef PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_ROAD_H
#define PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_ROAD_H

#include <iostream>
#include <vector>
#include "Town.h"

using namespace std;
class Town;
class Road {

public:
    Town* begin;
    Town* end;
    int length = 0;
    bool processed = false;
    vector<int> thieves;

    Road (Town* begin_, Town* end_, int length_);
    Road (const Road& other);
    Road&operator=(const Road& other);
    ~Road();

};

#endif //PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_ROAD_H
