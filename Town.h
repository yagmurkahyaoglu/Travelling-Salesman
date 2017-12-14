//
// Created by casper on 10.12.2017.
//

#ifndef PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_TOWN_H
#define PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_TOWN_H

#include <iostream>
#include <vector>
#include "Road.h"
#define INF 501
using namespace std;

class Road;
class Town {

public:

    int id = 0;
    int dist = INF;
    int coinNum =0;
    Town* uplink = nullptr;
    vector<int> coins;
    vector<int> universeCoins;
    vector<Road*> edges;
    vector<Road*> paths;

    Town (int id_);
    Town (const Town& other);
    Town& operator=(const Town& other);
    ~Town();
};
#endif //PROJECT3_YAGMUR_KAHYAOGLU_2015400057_MASTER_TOWN_H
