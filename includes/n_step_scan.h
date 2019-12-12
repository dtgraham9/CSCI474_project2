#pragma once
#include <vector>
#include "data_struct.h"

class n_step_scan{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int num_tracks_traversed;
    int SMALL_BUFFER;
public:
    n_step_scan(int,int,int, int, direction);
    int space_left();
};