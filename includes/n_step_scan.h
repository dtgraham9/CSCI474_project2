#pragma once
#include <vector>

class n_step_scan{
private:
    std::vector<int> read_queue;
    int MAX_TRACKS;
    int MAX_QUEUE;
    int current_track;
public:
    n_step_scan(int,int,int);
}