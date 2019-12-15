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
    read_buff_size = 0;
}

bool sstf::full(){
    return MAX_BUFFER==read_buffer.size();
}

bool sstf::read_ready(){
    if(read_buffer.size() > 0 && read_buff_size > 0){
        return true;
    }
    else if(read_buffer.size() > 0){
        read_buff_size = read_buffer.size();
        return true;
    }
    else{
        return false;
    }
}

void sstf::read(){
    int read_index = -1;
    int requested_track = 0;
    int diff_tracks = 0;
    int diff_track = 0; //difference between current track and one in request queue
    int min_diff_track = MAX_TRACKS;
    int index_track = 0;
    if(!read_ready()){
        return;
    }
    for (int i = 0; i <read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];
        if(diff_track == 0){
            read_index = i;
            break;
        }
        else if(abs(diff_track) < min_diff_track){
            min_diff_track = diff_track;
            read_index = i;
        }
    }

    --read_buff_size;
    requested_track = read_buffer[read_index];
    diff_tracks = abs(requested_track - current_track);
    scanfile.open("nstep.log.txt",std::ios_base::app);
    scanfile<< requested_track << "\t" << diff_tracks;
    scanfile.close();

    num_tracks_traversed += diff_tracks;
    read_buffer.erase(read_buffer.begin() + read_index);
    num_tracks_requested += 1;

}



std::string sstf::print_report(){


avg_num_track = (double) num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("sstf.log.txt",std::ios_base::app);
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

void sstf::reset(std::string test_sim, int new_track){
    scanfile.open("sstf.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\n" << test_sim << endl;
    scanfile << "Next\t\tNumber\nTrack\t\tof Tracks\nAccessed:\tTraversed:" << std::endl;
    scanfile.close();
    num_tracks_traversed = 0;
    num_tracks_requested = 0;
    read_buffer.clear();
    read_buff_size =0;
}