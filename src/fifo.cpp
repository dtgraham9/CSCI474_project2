#include "fifo.h"

fifo::fifo(int MAX_TRACKS, int MAX_BUFFER, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
    total = 0;
    element = 0;
}
int fifo::next_read_index(){
    for(int i = 0; i < read_buffer.size(); ++i){
        int next_track = read_buffer.front();
        read_buffer.pop_front();
        //seek.push_back(abs(current_track-next_track));
        current_track=next_track;
        total += abs(current_track-next_track);
        elements++;
    }
    Cout << total/elements << endl;
}
