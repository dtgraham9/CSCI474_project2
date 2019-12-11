#include "sstf.h"

sstf::sstf(int MAX_BUFFER, int MAX_TRACKS, int current_track){
    this->MAX_BUFFER = MAX_BUFFER;
    this->MAX_TRACKS = MAX_TRACKS;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
}