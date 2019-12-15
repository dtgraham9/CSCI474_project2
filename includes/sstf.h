#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class sstf{
private:
    std::vector<int> read_buffer;
    int MAX_BUFFER;
    int MAX_TRACKS;
    int current_track;
    int num_tracks_traversed;
    int num_tracks_requested;
    std::ofstream scanfile;
    int avg_num_track;
public:
    sstf(int, int, int);
    void read();
    void reset(std::string, int);
private:
    void print_report();
};