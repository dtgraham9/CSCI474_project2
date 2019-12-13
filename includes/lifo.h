#pragma once
#include <stack>
#include <iostream>
#include <fstream>

class lifo{
private:
    std::stack<int> read_stack;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int next_track;
    int num_tracks_traversed;
    std::ofstream scanfile;
    int num_tracks_requested;
    int avg_num_track;
    
public:
    lifo(int, int, int);
    bool full();
    void read();
    void add(int);
    void add_tracks(std::stack<int> &);
    int space_left(); 
    void print_report();
    
private:  
    bool read_ready();
};