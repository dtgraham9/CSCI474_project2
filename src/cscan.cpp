#include "cscan.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

cscan::cscan(int MAX_TRACKS, int MAX_BUFFER, int current_track, direction set_direction){
    this->MAX_BUFFER = MAX_BUFFER;
    this->MAX_TRACKS = MAX_TRACKS;
    read_buffer.reserve(MAX_BUFFER);
    this->set_direction = set_direction;
    this->current_track = current_track;
    num_tracks_requested = 0;
    num_tracks_traversed = 0;
    avg_num_track = 0;
    //Overwrite log file if present and create new then close
    scanfile.open("cscan.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
    read_buff_size = 0;
}

bool cscan::full(){
    return MAX_BUFFER == read_buffer.size();
}

int cscan::next_read_index(){
    int index =0;
    switch(set_direction){
        case INC:
            index = handle_INC();
            break;
        case DEC:
            index = handle_DEC();
            break;
    }
    return index;
}

int cscan::handle_INC(){
    int index = 0;
    int diff_track = 0;
    int min_diff_track = MAX_TRACKS;
    int index_track = 0;
    //Track for the possibilty that the drive head may have to switch directions
    int opposite_index_track = 0;
    int opposite_min_diff_track = MAX_TRACKS;
    /*
    If never changed to false, it means there were no more
    track requests farther away in the increasing direction
    */
    bool reset_drive_head = true;
    for(int i = 0; i < read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];

        if(diff_track == 0){
            return i;
        }
        //Going away from track 0
        else if(diff_track < 0 && abs(diff_track) < min_diff_track){
            reset_drive_head = false;
            min_diff_track = abs(diff_track);
            index_track = i;
        }
        //Closet track request to track 0
        else if(diff_track > 0 && read_buffer[i] < opposite_min_diff_track){
            opposite_min_diff_track = read_buffer[i];
            opposite_index_track = i;
        }
    }
    //Check to see if there is any track request in the same direction
    if(reset_drive_head){
        return opposite_index_track;
    }
    else{
        return index_track;
    }

}

int cscan::handle_DEC(){
    int index = 0;
    int diff_track = 0;
    int min_diff_track = MAX_TRACKS;
    int index_track = 0;
    //Track for the possibilty that the drive head may have to switch directions
    int opposite_index_track = 0;
    int opposite_min_diff_track = MAX_TRACKS;
    /*
    If never changed to false, it means there were no more
    track requests farther away in the increasing direction
    */
    bool reset_drive_head = true;
    for(int i = 0; i < read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];

        if(diff_track == 0){
            return i;
        }
        //Going away from track 0
        else if(diff_track < 0 && (MAX_TRACKS - 1) - read_buffer[i] < opposite_min_diff_track){
            opposite_min_diff_track = (MAX_TRACKS - 1) - read_buffer[i];
            opposite_index_track = i;
        }
        //Closet track request to track 0
        else if(diff_track > 0 && abs(diff_track) < min_diff_track){
            reset_drive_head = false;
            min_diff_track = abs(diff_track);
            index_track = i;
        }
    }
    //Check to see if there is any track request in the same direction
    if(reset_drive_head){
        return opposite_index_track;
    }
    else{
        return index_track;
    }
}

bool cscan::read_ready(){
    if(read_buffer.size()>0 && read_buff_size > 0){
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

void cscan::read(){
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
    scanfile.open("cscan.log.txt",std::ios_base::app);
    scanfile<< requested_track << "\t" << diff_tracks;
    scanfile.close();
    
    num_tracks_traversed += diff_tracks;

    read_buffer.erase(read_buffer.begin() + read_index);

    num_tracks_requested+=1;
    read_buff_size--;
    
}

void cscan::add(int track){
    read_buffer.push_back(track);
}

void cscan::add_tracks(std::vector<int> & tracks){
    for (int i = 0; i < tracks.size(); ++i){
        read_buffer.push_back(tracks[i]);
    }
}

int cscan::space_left(){
    return MAX_BUFFER - read_buffer.size();
}

std::string cscan::print_report(){


avg_num_track = (double)num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("cscan.log.txt",std::ios_base::app);
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

void cscan::reset(std::string test_sim, int new_track){
    scanfile.open("cscan.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\n" << test_sim << endl;
    scanfile << "Next\t\tNumber\nTrack\t\tof Tracks\nAccessed:\tTraversed:" << std::endl;
    scanfile.close();
    num_tracks_requested = 0;
    num_tracks_traversed = 0;
    avg_num_track = 0;
    current_track = new_track;
    read_buff_size = 0;
    read_buffer.clear();
}