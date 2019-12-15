#include <vector>
#include <cstdlib> 
#include <iostream>
#include <time.h>
#include <map>
#include <random>
#include <cmath>
#include <iomanip>
#include "fifo.h"



int rand_gen(int prev_track, int max_tracks){
    double left_interval = (double)(max_tracks-prev_track)/(max_tracks*2);
    double right_interval = (double)prev_track/(max_tracks*2); 
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::vector<double> i{0.0, (double)prev_track, (double)max_tracks};
    std::vector<double> w{left_interval, 1, right_interval}; 
    std::piecewise_linear_distribution<> d(i.begin(), i.end(), w.begin());
 
    // std::map<int, int> hist;
    // for(int n=0; n<5000; ++n) {
    //     //std::cout << (int)d(gen) << std::endl; 
    //     ++hist[d(gen)];
    // }
    // for(auto p : hist) {
    //     std::cout << std::setw(2) << std::setfill('0') << p.first << ' '
    //         << std::string(p.second,'*') << '\n';
    // }
    int random_wgt = (int) d(gen);
    if(0 <=random_wgt && random_wgt < max_tracks){
        return random_wgt;
    }
    throw "Random generator not working";
}


int main(int argc, char *argv[]){
    int num_reads =1000, max_tracks=200, rand_tracks = 1000, max_buffer = 50;
    //vars to keep track of number of successful reads for each scheduler
    int fifo_good_reads = 0, lifo_good_reads = 0, sstf_good_reads = 0, scan_good_reads = 0, n_step_good_reads = 0, cscan_good_reads = 0, fscan_good_reads = 0;
    //vars to set number of requests per scheduler
    int fifo_read_size = 25, lifo_read_size = 25, sstf_read_size = 25, scan_read_size = 25, n_step_read_size = 25, cscan_read_size = 25, fscan_read_size = 25; 
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
            track_queue_wgt.push_back(rand_gen(track_queue_wgt.back(),max_tracks));
        }
    }
    // checks if the fifo read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments fifo_good_reads
    
    fifo fifo_sch(max_tracks, max_buffer, 50);
    fifo_sch.reset("Random Test", 50);
    for(int i = 0; i < track_queue.size(); ){
        for(int j = i; j < i+25; ++j){
            if(fifo_sch.full()){
                i = j;
                break;
            }
            fifo_sch.add(track_queue[j]);
        }
        fifo_sch.read();
    }
    fifo_sch.print_report();
    
    
}