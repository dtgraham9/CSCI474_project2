#include "n_step_scan.h"

n_step_scan::n_step_scan(int MAX_TRACKS, int MAX_BUFFER, int current_track, 
    int SMALL_BUFFER, direction set_direction){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
}

int n_step_scan::space_left(){
    
}