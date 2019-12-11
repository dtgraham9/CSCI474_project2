#include "cscan.h"
#include <vector>
#include <cstdlib>

cscan::cscan(int MAX_TRACKS, int MAX_QUEUE, int current_track; direction set_direction){
    this->MAX_QUEUE = MAX_QUEUE;
    this->MAX_TRACKS = MAX_TRACKS;
    read_queue.reserve(MAX_QUEUE);
    this->set_direction = set_direction;
    this->current_track = current_track;
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
    for(int i = 0; i < read_queue.size(); ++i){
        diff_track = current_track - read_queue[i];

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
        else if(diff_track > 0 && read_queue[i] < opposite_min_diff_track){
            opposite_min_diff_track = read_queue[i];
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
    for(int i = 0; i < read_queue.size(); ++i){
        diff_track = current_track - read_queue[i];

        if(diff_track == 0){
            return i;
        }
        //Going away from track 0
        else if(diff_track < 0 && (MAX_TRACKS - 1) - read_queue[i] < opposite_min_diff_track){
            opposite_min_diff_track = (MAX_TRACKS - 1) - read_queue[i];
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