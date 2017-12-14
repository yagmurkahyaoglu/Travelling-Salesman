//
// Created by casper on 11.12.2017.
//

#include "Road.h"

Road :: Road (Town* begin_, Town* end_, int length_) {
    this->begin = begin_;
    this->end = end_;
    this->length = length_;
    this->thieves = vector<int>(13);
}

Road ::Road(const Road &other) {
    this->processed = other.processed;
    this->begin = other.begin;
    this->end = other.end;
    this->length = other.length;
    this->thieves = other.thieves;

}

Road& Road ::operator=(const Road &other) {
    this->processed = other.processed;
    this->begin = other.begin;
    this->end = other.end;
    this->length = other.length;
    this->thieves = other.thieves;
}

Road ::~Road() {
    delete(this->begin);
    delete(this->end);
}