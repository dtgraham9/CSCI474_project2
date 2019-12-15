#include "sstf.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

sstf::sstf(int MAX_BUFFER, int MAX_TRACKS, int current_track){
    this->MAX_BUFFER = MAX_BUFFER;
    this->MAX_TRACKS = MAX_TRACKS;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
    //Overwrite log file if present and create new then close
    scanfile.open("sstf.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
}


//i just copied as template, needs changing
/*
void sstf::read(){
    int read_index;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }

    read_index = next_read_index();
    requested_track = read_buffer[read_index];
    diff_tracks = abs(requested_track - current_track);

    //logging
    //Reopen log file and write entry, then close
    //Implement logging of track request and travel
    
    //write into file
    scanfile.open("sstf.log.txt",std::ios_base::app);
    scanfile<< requested_track << "\t" << diff_tracks;
    scanfile.close();

    num_tracks_traversed += diff_tracks;
    read_buffer.erase(read_buffer.begin() + read_index);
    num_tracks_requested += 1;
}*/


void sstf::print_report(){

std::cout << std::setprecision(2) << std::fixed;

avg_num_track = (float) num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("sstf.log.txt",std::ios_base::app);
    scanfile<<"________________________________________\nTotal Tracks Traversed: " << num_tracks_traversed << "\nAverage Seek Length: " << avg_num_track;
    scanfile.close();


}

void sstf::reset(std::string test_sim, int new_track){
    scanfile.open("sstf.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\nNext Track Accessed: \tNumber of Tracks Traversed: " << test_sim << "\n" << std::endl;
    scanfile.close();
    num_tracks_traversed = 0;
    num_tracks_requested = 0;
}