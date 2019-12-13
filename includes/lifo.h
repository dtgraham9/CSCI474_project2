#pragma once
#include <vector>
#include <fstream>

class lifo{
private:
    std::vector<int> read_buffer;
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
    void add_tracks(std::vector<int> &);
    int space_left(); 
    void print_report();
    
private:
    int next_read_index();    
    bool read_ready();
};