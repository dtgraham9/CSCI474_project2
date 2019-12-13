#pragma once
#include <vector>
#include <string>
#include "data_struct.h"

class n_step_scan{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int num_tracks_traversed;
    int SMALL_BUFFER;
    int small_buffer_size;
    bool write_lock;
    int actual_size;
    int write_queue_size;
    int num_tracks_requested;
    direction current_direction;
public:
    n_step_scan(int,int,int, int, direction);
    int space_left();
    void read();
    void add(int);
    bool full();
    void reset(std::string, int);
private:
    void determine_write_length();
    int next_read_index();
    int handle_INC();
    int handle_DEC();
    int handle_IDLE();
    bool read_ready();
};