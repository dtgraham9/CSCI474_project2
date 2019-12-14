#pragma once
#include <vector>
#include "data_struct.h"
#include <fstream>
#include <string>
/*Implements the SCAN disk management method.
SCAN will take a queue and move only in one direction until reaches edge.
SCAN can recieve new requests while dealing with queue.  
*/
class scan{
private:
    int MAX_BUFFER;
    int MAX_TRACKS;
    std::vector<int> read_buffer;
    direction current_direction;
    int current_track;  
    int num_tracks_traversed;  
    std::fstream scanfile;
    int num_tracks_requested;
    int avg_num_track;

public:
    scan(int, int, int);
    bool full();
    void add(int);
    void add_tracks(std::vector<int> &);
    int space_left();
    void read();
    void print_report();
    void reset(std::string, int);

private:
    int next_read_index();
    int handle_IDLE();
    int handle_INC();
    int handle_DEC();
    bool read_ready();
    
};