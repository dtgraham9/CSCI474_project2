#pragma once
#include <vector>
#include "data_struct.h"

class cscan{
private:
    int MAX_BUFFER;
    int MAX_TRACKS;
    std::vector<int> read_buffer;
    direction set_direction;
    int current_track;  

public:
    cscan(int, int, int, direction);
    bool full();

private:
    int next_read_index();
    int handle_INC();
    int handle_DEC();
};