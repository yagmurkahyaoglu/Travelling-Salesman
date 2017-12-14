//
// Created by casper on 10.12.2017.
//
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <functional>
#include <queue>
#include <cmath>
#include "Town.h"
#include "Road.h"

using namespace std;
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

bool Compare(Town *T1,Town *T2){
    return T1->dist > T2->dist;
}



int main(int argc, char* argv[]) {

// below reads the input file
    if (argc != 3) {
        cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
        return 1;
    }



    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> words;
    split1(line, words);
    int n = stoi(words[0]); //number of towns
    int m = stoi(words[1]); //number of roads
    int p = stoi(words[2]); //number of thief groups
    int k = stoi(words[3]); //number of jewelers
    vector<Town*> towns(n);
    for(int i=0; i<n; i++){
        towns[i] = new Town(i+1);
    }
    for(int i=0; i<k; i++){
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        int h = stoi(words[0]);
        int q = stoi(words[1]);
        towns[h-1]->coinNum += q;
        for (int j=0; j<q; j++){
            int c = stoi(words[2+j]);
            towns[h-1]->coins[c-1] = c;
        }
    }
    for(int i=0; i<m; i++){
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        int v = stoi(words[0]);
        int w = stoi(words[1]);
        int t = stoi(words[2]);
        int s = stoi(words[3]);
        Road* R1 = new Road(towns[v-1], towns[w-1],t);
        Road* R2 = new Road(towns[w-1], towns[v-1],t);
        for(int j=0; j<s; j++){
            int thief = stoi(words[4+j]);
            R1->thieves[thief-1] = thief;
            R2->thieves[thief-1] = thief;
        }
        towns[v-1]->edges.push_back(R1);
        towns[w-1]->edges.push_back(R2);
    }
    vector<vector<Town*>> graphs;
    int g;
    g = (int) pow(2, p);
    for(int i=0; i<g; i++){
        graphs.push_back(towns);
    }
    queue<Town*> myTowns;
    myTowns.push(graphs[0][0]);
    vector<int> myCoins(13);
    vector<Road*> myRoads;

    if(p >= 1) {
        Town *current = myTowns.front();
        myTowns.pop();
        int count = 0;
        while (current->id <n) {

            if(count != 0) {
                if (!myTowns.empty()){
                    current = myTowns.front();
                    myTowns.pop();
                } else {
                    break;
                }
            }
            //cout << current->id << endl;

            count++;
            for(int i=0; i<myCoins.size(); i++){
                myCoins[i] = current->universeCoins[i];

            }

            for (int i = 0; i < current->edges.size(); i++) {
                if (!current->edges[i]->processed) {
                    int counter = 0;
                    for (int j = 0; j < current->edges[i]->thieves.size(); j++) {
                        if (current->edges[i]->thieves[j] != 0 && myCoins[j] != current->edges[i]->thieves[j]) {
                            counter++;
                        }
                    }
                    if (counter == 0) {
                        if (current->edges[i]->end->coinNum > 0) {
                            for (int j = 0; j < current->edges[i]->end->coins.size(); j++) {
                                //myCoins[current->edges[i]->end->coins[j] - 1] = current->edges[i]->end->coins[j];
                                if (myCoins[j] == 0) {
                                    myCoins[current->edges[i]->end->coins[j] - 1] = current->edges[i]->end->coins[j];
                                }
                            }
                            int destination = 0;
                            for (int j = 0; j < myCoins.size(); j++) {
                                if (myCoins[j] != 0) {
                                    destination += (int) pow(2, myCoins[j] - 1);
                                }
                            }
                            for (int j = 0; j < myCoins.size(); j++) {
                                if (myCoins[j] != 0) {
                                    current->edges[i]->end->universeCoins[j] = myCoins[j];
                                }
                            }
                            current->edges[i]->processed = true;
                            myTowns.push(graphs[destination][current->edges[i]->end->id - 1]);
                            //cout << current->id << "1pushed " << current->edges[i]->end->id << endl;
                            //Road* newer = new Road(current, graphs[destination][current->id - 1], current->edges[i]->length);
                            //Road* newer;
                            Road* newer =new Road(new Town(0), new Town(0), 0);

                            newer->begin = current;
                            newer->end = graphs[destination][current->edges[i]->end->id - 1];
                            newer->length = current->edges[i]->length;
                            myRoads.push_back(newer);
                            current->paths.push_back(newer);
                        } else {
                            current->edges[i]->processed = true;
                            myTowns.push((current->edges[i]->end));
                            //cout << current->id << "2pushed " << current->edges[i]->end->id << endl;
                            //Road* newer = new Road(current, current->edges[i]->end, current->edges[i]->length);
                            Road* newer =new Road(new Town(0), new Town(0), 0);
                            newer->begin = current;
                            newer->end = current->edges[i]->end;
                            newer->length = current->edges[i]->length;
                            myRoads.push_back(newer);
                            current->paths.push_back( newer);
                        }
                    }
                }
            }
            //if (!myTowns.empty()) {
            //    current = myTowns.front();
            //    myTowns.pop();
            //}
        }
    }

    priority_queue<Town*, vector<Town*>, function<bool(Town*, Town*)>> pq(Compare);

    graphs[0][0]->dist = 0;
    pq.push(graphs[0][0]);
    string result="";
    int test=0;
    Town* T;
    while(!pq.empty()){
        T = pq.top();
        pq.pop();
        //result += to_string(T->id);

        if(T->id == n){
            Town* curr = T;
            result = to_string(curr->id) + " " + result;
            while(curr->uplink != nullptr){
                result = to_string(curr->uplink->id) + " " + result;
                curr = curr->uplink;
            }
            test++;
            break;
        }
        for(int i=0; i<T->paths.size(); i++){
            int weight = T->paths[i]->length;
            //cout <<T->id<<" "<<T->paths[i]->end->id<<" "<<T->paths[i]->end->dist<< endl;
            if(T->paths[i]->end->dist > T->dist + weight){
                T->paths[i]->end->dist = T->dist + weight;
                T->paths[i]->end->uplink = T;
                pq.push(T->paths[i]->end);
            }
        }
    }

    if(test == 0){
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }


    freopen(argv[2], "w", stdout);
    if(test == 0){
        printf("-1");
    } else {
        printf("%s",result.c_str());
    }
    fclose(stdout);


    return 0;
};

