#pragma once
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
class fifo{
private:
    std::queue<int> read_queue;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int next_track;
    int num_tracks_traversed;
    std::ofstream scanfile;
    int num_tracks_requested;
    int avg_num_track;
    std::vector<int> hold_buffer;
    bool queue_locked;

public:
    fifo(int, int, int);
    bool full();
    void read();
    void add(int);
    void add_tracks(std::vector<int> &);
    int space_left(); 
    void print_report();
    void reset(std::string, int);
    bool read_ready();
};