//
// Created by casper on 11.12.2017.
//
#include "Town.h"

Town :: Town (int id_){
    this->id = id_;
    this->coins = vector<int>(13);
    this->universeCoins = vector<int>(13);
    this->edges = vector<Road*>();
    this->paths = vector<Road*>();

}

Town :: Town(const Town &other) {
    this->id =other.id;
    this->dist = other.dist;
    this->uplink = other.uplink;
    this->coinNum = other.coinNum;
    this->coins = other.coins;
    this->universeCoins = other.universeCoins;
    this->edges = other.edges;
    this->paths = other.paths;
}

Town& Town ::operator=(const Town &other) {
    this->id =other.id;
    this->uplink = other.uplink;
    this->dist = other.dist;
    this->coinNum = other.coinNum;
    this->coins = other.coins;
    this->universeCoins = other.universeCoins;
    this->edges = other.edges;
    this->paths = other.paths;
}

Town ::~Town() {
    delete(this->uplink);

}
