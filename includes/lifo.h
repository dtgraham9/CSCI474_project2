#pragma once
#include <vector>

class lifo{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
public:
    lifo(int, int, int);
};