#pragma once
#include <vector>

class fifo{
private:
    std::vector<int> read_buffer;
    int MAX_TRACKS;
    int MAX_BUFFER;
    int current_track;
    int next_track;
    int total;
    int element;
public:
    fifo(int, int, int);
private:
    int next_read_index();
};