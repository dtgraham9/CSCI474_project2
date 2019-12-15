#pragma once
#include <vector>
#include "data_struct.h"
#include <iostream>
#include <fstream>
#include <string>
class fscan{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int write_queue_size;
    direction current_direction;
    int num_tracks_traversed;
    int num_tracks_requested;
    std::ofstream scanfile;
    double avg_num_track;
    
public:
    fscan(int, int, int, direction);
    void read();
    void add(int);
    void reset(std::string, int);
    std::string print_report();

private:
    int handle_DEC();
    int handle_INC();
    int handle_IDLE();
    int next_read_index();
    bool read_ready();
    
};