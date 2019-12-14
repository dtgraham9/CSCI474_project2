#include <vector>
#include <cstdlib> 
#include <iostream>
#include <time.h>

int rand_gen(int prev_track, int edge, int max_tracks){
    int weight = 100000;
    std::vector<int> weight_rand;
    weight_rand.reserve(max_tracks);
    weight_rand[prev_track] = weight *.1;
    for(int i = 0; i < prev_track; ++i){

    }

    for(int i = prev_track+1; i<max_tracks; ++i){

    }

    return 0;
}


int main(int argc, char *argv[]){
    int num_reads =1000, max_tracks=200, rand_tracks = 1000;
    std::vector<int> track_queue;
    srand(time(0));

    for(int i = 0; i < num_reads; ++i){
        track_queue.push_back(rand() % max_tracks);
    }

    std::vector<int> track_queue_wgt;
    track_queue_wgt.push_back(rand() % max_tracks);
    int hold_rand = 0;
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt.push_back(track_queue_wgt.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt.push_back(0);
            }
            else{
                track_queue_wgt.push_back(max_tracks-1);
            }
        }
        else{
            if(rand() % 1 == 0){
                track_queue_wgt.push_back(rand_gen(track_queue_wgt.back(), 0, max_tracks));
            }
            else{
                track_queue_wgt.push_back(rand_gen(track_queue_wgt.back(), max_tracks, max_tracks-1));
            }
        }

    }
}