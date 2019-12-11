#pragma once
#include <vector>

class lifo{
private:
    std::vector<int> read_queue;
    int MAX_TRACKS;
    int MAX_QUEUE;
    int current_track;
public:
    lifo(int, int, int);
}