#include "scan.h"
#include <cstdlib>

/*
Reserve the memory needed for the queue and set max disk tracks
*/
scan::scan(const int MAX_TRACKS, const int MAX_QUEUE, int starting_track){
    read_queue.reserve(MAX_QUEUE);
    this->MAX_TRACKS = MAX_TRACKS;
    this->MAX_QUEUE = MAX_QUEUE;
    current_track = starting_track;
    current_direction = IDLE;
}

bool scan::full(){
    return read_queue.size() == MAX_QUEUE;
}

/*
Check if the request queue has anything to read.
If it doesn't then the drive will be put into an IDLE state.
*/
bool scan::read_ready(){
    if(read_queue.size() > 0){
        return true;
    }
    else{
        current_direction = IDLE;
        return false; 
    }
}
/*
Assumptions: There is a track read request avialable in queue
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
Return the index of the track in read_queue
that is the closet to the current drive head position
and also update the direction the drive head will be
going in.
*/
int scan::handle_IDLE(){
    int diff_track = 0; //difference between current track and one in request queue
    int min_diff_track = MAX_TRACKS;
    int index_track = 0;
    direction new_direction = IDLE;
    for(int i = 0 ; i < read_queue.size(); ++i){
        diff_track = current_track - read_queue[i];
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
    for(int i = 0; i < read_queue.size(); ++i){
        diff_track = current_track - read_queue[i];

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
    for(int i = 0; i < read_queue.size(); ++i){
        diff_track = current_track - read_queue[i];

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