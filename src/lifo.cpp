#include "lifo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

lifo::lifo(int MAX_TRACKS, int MAX_BUFFER, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    read_buffer.reserve(MAX_BUFFER);
    //Overwrite log file if present and create new then close
    scanfile.open("lifo.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
}

//code here




void lifo::read(){
    int read_index = 0;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }

    read_index = next_read_index();
    requested_track = read_buffer[read_index];
    diff_tracks = abs(requested_track - current_track);

    //Reopen log file and write entry, then close
    //Implement logging of track request and travel
    
    //write into file
    scanfile.open("lifo.log.txt",std::ios_base::app);
    scanfile<<"Next Track Accessed: " << requested_track << "\n\tNumber of Tracks Traversed: " << diff_tracks;
    scanfile.close();
    
    num_tracks_traversed += diff_tracks;

    read_buffer.erase(read_buffer.begin() + read_index);

    num_tracks_requested+=1;
    
}

void lifo::add(int track){
    read_buffer.push_back(track);
}

void lifo::add_tracks(std::vector<int> & tracks){
    for (int i = 0; i < tracks.size(); ++i){
        read_buffer.push_back(tracks[i]);
    }
}

int lifo::space_left(){
    return MAX_BUFFER - read_buffer.size();
}

void lifo::print_report(){

std::cout << std::setprecision(2) << std::fixed;

avg_num_track = (float)num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("lifo.log.txt",std::ios_base::app);
    scanfile<<"________________________________________\nTotal Tracks Traversed: " << num_tracks_traversed << "\nAverage Seek Length: " << avg_num_track;
    scanfile.close();


}