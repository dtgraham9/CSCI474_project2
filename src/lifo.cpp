#include "lifo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

lifo::lifo(int MAX_TRACKS, int MAX_BUFFER, int current_track){
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    this->current_track = current_track;
    //Overwrite log file if present and create new then close
    scanfile.open("lifo.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
    num_tracks_traversed = 0;
    num_tracks_requested = 0;
    avg_num_track = 0;
    hold_buffer.reserve(MAX_BUFFER);
}

bool lifo::full(){
    int max_size = 0;
    if(!read_stack.empty()){
        max_size = MAX_BUFFER - read_stack.size();
        return max_size == hold_buffer.size();
    }
    else{
        return MAX_BUFFER == hold_buffer.size();
    }
}

bool lifo::read_ready(){
    if(!read_stack.empty()){
        return true;
    }
    else if(hold_buffer.size() == 0){
        return false;
    }
    else{
        for(int i = 0; i < hold_buffer.size(); ++i){
            read_stack.push(hold_buffer[i]);
        }
        hold_buffer.clear();
        return true;
    }
}

void lifo::read(){
    int read_index = 0;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }

    requested_track = read_stack.top();
    read_stack.pop();
    diff_tracks = abs(requested_track - current_track);
    current_track = requested_track;

    //Reopen log file and write entry, then close
    //Implement logging of track request and travel
    
    //write into file
    scanfile.open("lifo.log.txt",std::ios_base::app);
    scanfile<< requested_track << "\t" << diff_tracks;
    scanfile.close();
    
    num_tracks_traversed += diff_tracks;

    read_stack.pop();

    num_tracks_requested+=1;
    
}

void lifo::add(int track){
    read_stack.push(track);
}

int lifo::space_left(){
    return MAX_BUFFER - read_stack.size();
}

std::string lifo::print_report(){


avg_num_track = (double) num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("lifo.log.txt",std::ios_base::app);
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

void lifo::reset(std::string test_sim, int new_track){
    scanfile.open("lifo.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\n" << test_sim << endl;
    scanfile << "Next\t\tNumber\nTrack\t\tof Tracks\nAccessed:\tTraversed:" << std::endl;
    scanfile.close();
    num_tracks_traversed = 0;
    num_tracks_requested = 0;
    avg_num_track = 0;
    current_track = new_track;
    hold_buffer.clear();
}