#pragma once
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    std::vector<int> hold_buffer;
    
public:
    lifo(int, int, int);
    bool full();
    void read();
    void add(int);
    int space_left(); 
    void print_report();
    void reset(std::string, int);
    
private:  
    bool read_ready();
};