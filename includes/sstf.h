#pragma once
#include <vector>

class sstf{
private:
    std::vector<int> read_queue;
    int MAX_QUEUE;
    int MAX_TRACKS;
    int current_track;
public:
    sstf(int, int, int);
}