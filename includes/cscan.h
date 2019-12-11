#pragma once
#include <vector>
#include "data_struct.h"

class cscan{
private:
    int MAX_QUEUE;
    int MAX_TRACKS;
    std::vector<int> read_queue;
    direction set_direction;
    int current_track;  

public:
    cscan(int, int, direction);
    bool full();

private:
    int next_read_index();
    int handle_INC();
    int handle_DEC();
}