#pragma once
#include <vector>
#include "data_struct.h"

class cscan{
private:
    int MAX_BUFFER;
    int MAX_TRACKS;
    std::vector<int> read_buffer;
    direction set_direction;
    int current_track;  
    int num_tracks_traversed;

public:
    cscan(int, int, int, direction);
    bool full();
    void read();
    void add(int);
    void add_tracks(std::vector<int> &);
    int space_left();

private:
    int next_read_index();
    int handle_INC();
    int handle_DEC();
    bool read_ready();
};