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
    double avg_num_track;
    int read_buff_size;
public:
    sstf(int, int, int);
    void read();
    void reset(std::string, int);
    bool full();
    std::string print_report();
private:
    
    bool read_ready();
};