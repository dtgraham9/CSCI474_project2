#include "fifo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

fifo::fifo(int MAX_TRACKS, int MAX_BUFFER, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    //Overwrite log file if present and create new then close
    scanfile.open("fifo.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
}

void fifo::read(){
    int read_index = 0;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }

    requested_track = read_queue.front();
    read_queue.pop();
    diff_tracks = abs(requested_track - current_track);
    current_track = requested_track;

    //Reopen log file and write entry, then close
    //Implement logging of track request and travel
    
    //write into file
    scanfile.open("fifo.log.txt",std::ios_base::app);
    scanfile<<"Next Track Accessed: " << requested_track << "\n\tNumber of Tracks Traversed: " << diff_tracks;
    scanfile.close();
    
    num_tracks_traversed += diff_tracks;

    read_queue.pop();

    num_tracks_requested+=1;
    
}

void fifo::add(int track){
    read_queue.push(track);
}

void fifo::add_tracks(std::vector<int> & tracks){
    for (int i = 0; i < tracks.size(); ++i){
        read_queue.push(tracks[i]);
    }
}

int fifo::space_left(){
    return MAX_BUFFER - read_queue.size();
}

void fifo::print_report(){

std::cout << std::setprecision(2) << std::fixed;

avg_num_track = (float) num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("fifo.log.txt",std::ios_base::app);
    scanfile<<"________________________________________\nTotal Tracks Traversed: " << num_tracks_traversed << "\nAverage Seek Length: " << avg_num_track;
    scanfile.close();


}