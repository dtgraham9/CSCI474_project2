#pragma once
#include <vector>

class fscan{
private:
    std::vector<int> read_queue;
    int MAX_TRACKS;
    int MAX_QUEUE;
    int current_track;
public:
    fscan(int, int, int);
}