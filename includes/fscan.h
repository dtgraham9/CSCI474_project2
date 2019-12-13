#pragma once
#include <vector>

class fscan{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    std::vector<int> spare_buffer;
public:
    fscan(int, int, int, int);
};