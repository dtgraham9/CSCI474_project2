#include "fifo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

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
    num_tracks_traversed = 0;
    num_tracks_requested = 0;
    avg_num_track = 0;
    hold_buffer.reserve(MAX_BUFFER);
    queue_locked = false;
}

bool fifo::full(){
    int max_size = 0;
    if(!read_queue.empty()){
        max_size = MAX_BUFFER - read_queue.size();
        return max_size == hold_buffer.size();
    }
    else{
        return MAX_BUFFER == hold_buffer.size();
    }
}

bool fifo::read_ready(){
    if(!read_queue.empty()){
        return true;
    }
    else if(hold_buffer.size() == 0){
        return false;
    }
    else{
        for(int i = 0; i < hold_buffer.size(); ++i){
            read_queue.push(hold_buffer[i]);
        }
        hold_buffer.clear();
        return true;
    }
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
    scanfile<< requested_track << "\t\t\t" << diff_tracks <<std::endl;
    scanfile.close();
    
    num_tracks_traversed += diff_tracks;

    num_tracks_requested+=1;
    
}

void fifo::add(int track){
    hold_buffer.push_back(track);
}

void fifo::add_tracks(std::vector<int> & tracks){
    for (int i = 0; i < tracks.size(); ++i){
        read_queue.push(tracks[i]);
    }
}

int fifo::space_left(){
    return MAX_BUFFER - read_queue.size();
}

std::string fifo::print_report(){


avg_num_track = (double) num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("fifo.log.txt",std::ios_base::app);
    scanfile <<"________________________________________\nTotal Tracks Traversed: ";
    scanfile << num_tracks_traversed << "\nAverage Seek Length: " << std::setprecision(5) << avg_num_track;
    scanfile.close();
    std::ostringstream streamObj;
//Add double to stream
    streamObj << std::fixed;
 
    // Set precision to 2 digits
    streamObj << std::setprecision(5);
    
    //Add double to stream
    streamObj << avg_num_track;
    return "Total Tracks Traversed: " + std::to_string(num_tracks_traversed) + "\nAverage Seek Length: " + streamObj.str();

}

void fifo::reset(std::string test_sim, int new_track){
    current_track = new_track;
    scanfile.open("fifo.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\n" << test_sim << endl;
    scanfile << "Next\t\tNumber\nTrack\t\tof Tracks\nAccessed:\tTraversed:" << std::endl;
    scanfile.close();
    num_tracks_traversed= 0;
    num_tracks_requested = 0;
    avg_num_track = 0; 
    hold_buffer.clear();

}