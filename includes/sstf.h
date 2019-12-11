#pragma once
#include <vector>

class sstf{
private:
    std::vector<int> read_buffer;
    int MAX_BUFFER;
    int MAX_TRACKS;
    int current_track;
public:
    sstf(int, int, int);
};