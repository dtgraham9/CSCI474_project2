#include <vector>
#include <cstdlib> 
#include <iostream>
#include <time.h>
#include <map>
#include <random>
#include <cmath>
#include <iomanip>
#include "fifo.h"
#include "lifo.h"
#include "sstf.h"
#include "scan.h"
#include "cscan.h"
#include "n_step_scan.h"
#include "fscan.h"



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

void fifo_sim(fifo & fifo_sch, std::vector<int> & fifo_rand, std::string test_name, int start_track, int add_size){
    fifo_sch.reset(test_name, start_track);
    for(int i = 0; i < fifo_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(fifo_sch.full()){
                i = j;
                break;
            }
            fifo_sch.add(fifo_rand[j]);
        }
        fifo_sch.read();
    }
    std::string report = fifo_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}


int main(int argc, char *argv[]){
    int num_reads =1000, max_tracks=200, rand_tracks = 1000, max_buffer = 50;
    //vars to keep track of number of successful reads for each scheduler
    int fifo_good_reads = 0, lifo_good_reads = 0, sstf_good_reads = 0, scan_good_reads = 0, n_step_good_reads = 0, cscan_good_reads = 0, fscan_good_reads = 0;
    //vars to set number of requests per scheduler
    int add_size = 25; 
    //var for starting track
    int start_track = 50;
    std::vector<int> track_queue1, track_queue2, track_queue3, track_queue4, track_queue5;

    srand(time(0));

    for(int i = 0; i < num_reads; ++i){
        track_queue1.push_back(rand() % max_tracks);
        track_queue2.push_back(rand() % max_tracks);
        track_queue3.push_back(rand() % max_tracks);
        track_queue4.push_back(rand() % max_tracks);
        track_queue5.push_back(rand() % max_tracks);
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
    //FIFO Tests
    // reads in fifo_read_size entries from the track_queue:
    // Track 0 tests
    fifo fifo_sch(max_tracks, max_buffer, start_track);
    fifo_sim(fifo_sch, track_queue1, "FIFO Random Test 1 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue2, "FIFO Random Test 2 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue3, "FIFO Random Test 3 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue4, "FIFO Random Test 4 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue5, "FIFO Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    fifo_sim(fifo_sch, track_queue1, "FIFO Random Test 1 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue2, "FIFO Random Test 2 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue3, "FIFO Random Test 3 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue4, "FIFO Random Test 4 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue5, "FIFO Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    fifo_sim(fifo_sch, track_queue1, "FIFO Random Test 1 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue2, "FIFO Random Test 2 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue3, "FIFO Random Test 3 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue4, "FIFO Random Test 4 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue5, "FIFO Random Test 5 @ 199", 199, add_size);
    // checks if the lifo read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments lifo_good_reads
    
    // lifo lifo_sch(max_tracks, max_buffer, start_track);
    // lifo_sch.reset("Random Test", start_track);
    // for(int i = 0; i < track_queue.size(); ){
    //     for(int j = i; j < i+lifo_read_size; ++j){
    //         if(lifo_sch.full()){
    //             i = j;
    //             break;
    //         }
    //         lifo_sch.add(track_queue[j]);
    //     }
    //     lifo_sch.read();
    // }
    // lifo_sch.print_report();
    
    // checks if the lifo read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments sstf_good_reads
    /*
    sstf sstf_sch(max_tracks, max_buffer, start_track);
    sstf_sch.reset("Random Test", start_track);
    for(int i = 0; i < track_queue.size(); ){
        for(int j = i; j < i+sstf_read_size; ++j){
            if(sstf_sch.full()){
                i = j;
                break;
            }
            sstf_sch.add(track_queue[j]);
        }
        sstf_sch.read();
    }
    sstf_sch.print_report();
    */

   // checks if the lifo read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments sstf_good_reads
    /*
    scan scan_sch(max_tracks, max_buffer, start_track);
    scan_sch.reset("Random Test", start_track);
    for(int i = 0; i < track_queue.size(); ){
        for(int j = i; j < i+sstf_read_size; ++j){
            if(scan_sch.full()){
                i = j;
                break;
            }
            scan_sch.add(track_queue[j]);
        }
        scan_sch.read();
    }
    scan_sch.print_report();
    */
}