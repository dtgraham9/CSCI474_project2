#include "fifo.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
ofstream scanfile;
fifo::fifo(int MAX_TRACKS, int MAX_BUFFER, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
    //Overwrite log file if present and create new then close
    scanfile.open("fifo.log.txt", std::ofstream::out | std::ofstream::trunc);
    scanfile.close();
}

bool fifo::full(){
    return read_buffer.size() == MAX_BUFFER;
}

/*
Check if the request queue has anything to read.
If it doesn't then the drive will be put into an IDLE state.
*/
bool fifo::read_ready(){
    if(read_buffer.size() > 0){
        return true;
    }
    else{
        return false; 
    }
}

void fifo::read(){
    int read_index = 0;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }
}

