#include "n_step_scan.h"

n_step_scan::n_step_scan(int MAX_TRACKS, int MAX_QUEUE, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_QUEUE = MAX_QUEUE;
    this->current_track = current_track;
    read_queue.reserve(MAX_QUEUE);
}