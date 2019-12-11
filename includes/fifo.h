#pragma once
#include <vector>

class fifo{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
public:
    fifo(int, int, int);
};