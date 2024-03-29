#include "scan.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/*
Reserve the memory needed for the queue and set max disk tracks
*/
scan::scan(const int MAX_TRACKS, const int MAX_BUFFER, int starting_track){
    read_buffer.reserve(MAX_BUFFER);
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_BUFFER = MAX_BUFFER;
    current_track = starting_track;
    current_direction = IDLE;
    num_tracks_traversed = 0;
    //Overwrite log file if present and create new then close
    scanfile.open("scan.log.txt", std::ofstream::out | std::ofstream::trunc);
    if(!scanfile){
      std::cout<<"Error in creating file.."<<endl;
    }
    scanfile.close();
    std::cout << "\nFile created successfully." << endl;
    read_buff_size =0;
}

bool scan::full(){
    return read_buffer.size() == MAX_BUFFER;
}

/*
Check if the request queue has anything to read.
If it doesn't then the drive will be put into an IDLE state.
*/
bool scan::read_ready(){
    if(read_buffer.size() > 0 && read_buff_size >0){
        return true;
    }
    else if(read_buffer.size()>0){
        read_buff_size = read_buffer.size();
        return true;
    }
    else{
        return false;
    }
}
/*
Assumptions: There is a track read request avialable in buffer

Post: Will return the index of the next read in the buffer
*/
int scan::next_read_index(){
    int index = 0;
    switch(current_direction){
        case IDLE:
            index = handle_IDLE();
            break;
        case INC:
            index = handle_INC();
            break;
        case DEC:
            index = handle_DEC();
            break;
    }
    return index;
}

/*
Return the index of the track in read_buffer
that is the closet to the current drive head position
and also update the direction the drive head will be
going in.
*/
int scan::handle_IDLE(){
    int diff_track = 0; //difference between current track and one in request queue
    int min_diff_track = MAX_TRACKS;
    int index_track = 0;
    direction new_direction = IDLE;
    for(int i = 0 ; i < read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];
        /*Drive head is currently on requested track.
        Return that track index.
        */
        if(diff_track == 0){
            current_direction = IDLE;
            return i;
        }
        //If the track isn't closer than the current one, end loop iteration
        else if(abs(diff_track) >= min_diff_track){
            continue;
        }
        //Going away from track 0
        else if(diff_track < 0){
            new_direction = INC;
            index_track = i;
            min_diff_track = abs(diff_track);
        }
        //Going towards track 0 
        else if(diff_track > 0){
            new_direction = DEC;
            index_track = i;
            min_diff_track = abs(diff_track);
        }
    }
    current_direction = new_direction;
    return index_track;
}

int scan::handle_INC(){
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
    bool reverse_direction = true;
    direction new_direction = IDLE;
    for(int i = 0; i < read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];

        if(diff_track == 0){
            current_direction = INC;
            return i;
        }
        //Going away from track 0
        else if(diff_track < 0 && abs(diff_track) < min_diff_track){
            reverse_direction = false;
            min_diff_track = abs(diff_track);
            index_track = i;
        }
        //Going towards track 0
        else if(diff_track > 0 && abs(diff_track) < opposite_min_diff_track){
            opposite_min_diff_track = abs(diff_track);
            opposite_index_track = i;
        }
    }
    //Check to see if there is any track request in the same direction
    if(reverse_direction){
        current_direction = DEC; 
        return opposite_index_track;
    }
    else{
        current_direction = INC;
        return index_track;
    }
}

int scan::handle_DEC(){
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
    bool reverse_direction = true;
    direction new_direction = IDLE;
    for(int i = 0; i < read_buff_size; ++i){
        diff_track = current_track - read_buffer[i];

        if(diff_track == 0){
            current_direction = INC;
            return i;
        }
        //Going away from track 0
        else if(diff_track < 0 && abs(diff_track) < opposite_min_diff_track){
            opposite_min_diff_track = abs(diff_track);
            opposite_index_track = i;
        }
        //Going towards track 0
        else if(diff_track > 0 && abs(diff_track) < min_diff_track){
            reverse_direction = false;
            min_diff_track = abs(diff_track);
            index_track = i;            
        }
    }
    //Check to see if there is any track request in the same direction
    if(reverse_direction){
        current_direction = INC; 
        return opposite_index_track;
    }
    else{
        current_direction = DEC;
        return index_track;
    }
}

/*
*/
void scan::read(){
    int read_index = 0;
    int requested_track = 0;
    int diff_tracks = 0;
    if(!read_ready()){
        return;
    }

    read_index = next_read_index();
    requested_track = read_buffer[read_index];
    diff_tracks = abs(requested_track - current_track);
    current_track = requested_track;
    //Reopen log file and write entry, then close
    //Implement logging of track request and travel

    //write into file
    scanfile.open("scan.log.txt",std::ios_base::app);
    scanfile<< requested_track << "\t\t\t" << diff_tracks << std::endl;
    scanfile.close();

    num_tracks_traversed += diff_tracks;

    read_buffer.erase(read_buffer.begin()+read_index);

    num_tracks_requested+=1;
    read_buff_size--;
}

/*
Assumption: There is space available in buffer
*/
void scan::add(int track){
    read_buffer.push_back(track);
}

void scan::add_tracks(std::vector<int> & tracks)
{
    for(int i = 0; i < tracks.size(); ++i){
        read_buffer.push_back(tracks[i]);
    }
}

int scan::space_left(){
    return MAX_BUFFER - read_buff_size;

}

std::string scan::print_report(){


avg_num_track = (float)num_tracks_traversed/num_tracks_requested;


//write into file
    scanfile.open("scan.log.txt",std::ios_base::app);
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

void scan::reset(std::string test_sim, int new_track){
    current_direction = IDLE;
    current_track = new_track;
    num_tracks_traversed = 0;  
    num_tracks_requested= 0;
    avg_num_track = 0;
    scanfile.open("scan.log.txt", std::ios_base::app);
    scanfile <<"\n#####################################\n" << test_sim << endl;
    scanfile << "Next\t\tNumber\nTrack\t\tof Tracks\nAccessed:\tTraversed:" << std::endl;
    scanfile.close();
}