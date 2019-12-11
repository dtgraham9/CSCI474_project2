#pragma once
#include <vector>

class n_step_scan{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
public:
    n_step_scan(int,int,int);
};