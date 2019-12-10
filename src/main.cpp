#include <vector>
#include <cstdlib> 
#include <iostream>
#include <time.h>

int main(int argc, char *argv[]){
    int num_reads =1000, max_tracks=200;
    std::vector<int> track_queue;
    srand(time(0));

    for(int i = 0; i < num_reads; ++i){
        track_queue.push_back(rand() % max_tracks);
    }

    
}