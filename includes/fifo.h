#pragma once
#include <vector>

class fifo{
private:
    std::vector<int> read_queue;
    int MAX_TRACKS;
    int MAX_QUEUE;
    int current_track;
public:
    fifo(int, int, int);
}