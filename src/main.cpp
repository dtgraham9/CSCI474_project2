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
#include "data_struct.h"


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

void lifo_sim(lifo & lifo_sch, std::vector<int> & lifo_rand, std::string test_name, int start_track, int add_size){
    lifo_sch.reset(test_name, start_track);
    for(int i = 0; i < lifo_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(lifo_sch.full()){
                i = j;
                break;
            }
            lifo_sch.add(lifo_rand[j]);
        }
        lifo_sch.read();
    }
    std::string report = lifo_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

void sstf_sim(sstf & sstf_sch, std::vector<int> & sstf_rand, std::string test_name, int start_track, int add_size){
    sstf_sch.reset(test_name, start_track);
    for(int i = 0; i < sstf_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(sstf_sch.full()){
                i = j;
                break;
            }
            sstf_sch.add(sstf_rand[j]);
        }
        sstf_sch.read();
    }
    std::string report = sstf_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

void scan_sim(scan & scan_sch, std::vector<int> & scan_rand, std::string test_name, int start_track, int add_size){
    scan_sch.reset(test_name, start_track);
    for(int i = 0; i < scan_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(scan_sch.full()){
                i = j;
                break;
            }
            scan_sch.add(scan_rand[j]);
        }
        scan_sch.read();
    }
    std::string report = scan_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

void n_step_sim(n_step_scan & n_step_sch, std::vector<int> & n_step_rand, std::string test_name, int start_track, int add_size){
    n_step_sch.reset(test_name, start_track);
    for(int i = 0; i < n_step_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(n_step_sch.full()){
                i = j;
                break;
            }
            n_step_sch.add(n_step_rand[j]);
        }
        n_step_sch.read();
    }
    std::string report = n_step_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

void cscan_sim(cscan & cscan_sch, std::vector<int> & cscan_rand, std::string test_name, int start_track, int add_size, direction new_direction){
    cscan_sch.reset(test_name, start_track);
    for(int i = 0; i < cscan_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(cscan_sch.full()){
                i = j;
                break;
            }
            cscan_sch.add(cscan_rand[j]);
        }
        cscan_sch.read();
    }
    std::string report = cscan_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

void fscan_sim(fscan & fscan_sch, std::vector<int> & fscan_rand, std::string test_name, int start_track, int add_size){
    fscan_sch.reset(test_name, start_track);
    for(int i = 0; i < fscan_rand.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(fscan_sch.full()){
                i = j;
                break;
            }
            fscan_sch.add(fscan_rand[j]);
        }
        fscan_sch.read();
    }
    std::string report = fscan_sch.print_report();
    std::cout << test_name << "\n" << report << std::endl;
}

int main(int argc, char *argv[]){
    if(argc < 7){
        //error
        std::cout << "Usage: ./disk_scheduler <number_of_random_requests> <number_of_weighted_random_requests> <max_track_count> <max_buffer_size> <small_buffer_size> <queue_add_size>" << std::endl;
        std::cout << "number_of_random_requests: used in random number generation of request data" << std::endl;
        std::cout << "number_of_weighted_random_requests: used in weighted random number generation of request data" << std::endl;
        std::cout << "max_track_count: max number of tracks to be simulated on disk" << std::endl;
        std::cout << "max_buffer_size: max number of requests to be tested" << std::endl;
        std::cout << "small_buffer_size: must be smaller than max buffer" << std::endl;
        std::cout << "queue_add_size: number of requests passed to an algorithm at a time" << std::endl;
        exit(argc); 
    }
    int num_reads = atoi(argv[2]), max_tracks = atoi(argv[3]), rand_tracks = atoi(argv[1]), max_buffer = atoi(argv[4]), small_buffer = atoi(argv[5]);
    //vars to keep track of number of successful reads for each scheduler
    int fifo_good_reads = 0, lifo_good_reads = 0, sstf_good_reads = 0, scan_good_reads = 0, n_step_good_reads = 0, cscan_good_reads = 0, fscan_good_reads = 0;
    //vars to set number of requests per scheduler
    int add_size = atoi(argv[6]); 
    //var for starting track
    int start_track = 50;
    std::vector<int> track_queue1, track_queue2, track_queue3, track_queue4, track_queue5;
    std::vector<int> standard = {55,58,39,18,90,160,150,38,184};


    srand(time(0));

    for(int i = 0; i < num_reads; ++i){
        track_queue1.push_back(rand() % max_tracks);
        track_queue2.push_back(rand() % max_tracks);
        track_queue3.push_back(rand() % max_tracks);
        track_queue4.push_back(rand() % max_tracks);
        track_queue5.push_back(rand() % max_tracks);
    }

    std::vector<int> track_queue_wgt1;
    std::vector<int> track_queue_wgt2;
    std::vector<int> track_queue_wgt3;
    std::vector<int> track_queue_wgt4;
    std::vector<int> track_queue_wgt5;
    track_queue_wgt1.push_back(rand() % max_tracks);
    int hold_rand = 0;
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt1.push_back(track_queue_wgt1.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt1.push_back(0);
            }
            else{
                track_queue_wgt1.push_back(max_tracks-1);
            }
        }
        else{
            track_queue_wgt1.push_back(rand_gen(track_queue_wgt1.back(),max_tracks));
        }
    }
    track_queue_wgt2.push_back(rand() % max_tracks);
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt2.push_back(track_queue_wgt2.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt2.push_back(0);
            }
            else{
                track_queue_wgt2.push_back(max_tracks-1);
            }
        }
        else{
            track_queue_wgt2.push_back(rand_gen(track_queue_wgt2.back(),max_tracks));
        }
    }
    track_queue_wgt3.push_back(rand() % max_tracks);
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt1.push_back(track_queue_wgt3.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt1.push_back(0);
            }
            else{
                track_queue_wgt1.push_back(max_tracks-1);
            }
        }
        else{
            track_queue_wgt1.push_back(rand_gen(track_queue_wgt1.back(),max_tracks));
        }
    }
    track_queue_wgt4.push_back(rand() % max_tracks);
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt4.push_back(track_queue_wgt4.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt4.push_back(0);
            }
            else{
                track_queue_wgt4.push_back(max_tracks-1);
            }
        }
        else{
            track_queue_wgt4.push_back(rand_gen(track_queue_wgt4.back(),max_tracks));
        }
    }
    track_queue_wgt5.push_back(rand() % max_tracks);
    for(int i = 1; i < rand_tracks; ++i){
        hold_rand = (rand() % 100) +1; 
        if(hold_rand <= 10 && hold_rand >= 1){
            track_queue_wgt5.push_back(track_queue_wgt5.back());
            continue;
        }
        else if(hold_rand == 100){
            if((rand()% 1) == 0){
                track_queue_wgt5.push_back(0);
            }
            else{
                track_queue_wgt5.push_back(max_tracks-1);
            }
        }
        else{
            track_queue_wgt5.push_back(rand_gen(track_queue_wgt5.back(),max_tracks));
        }
    }
    // FIFO Tests
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
    //-------------------
    //Weighted FIFO Tests
    //-------------------
    // Track 0 tests
    fifo_sim(fifo_sch, track_queue_wgt1, "FIFO Weighted Random Test 1 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue_wgt2, "FIFO Weighted Random Test 2 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue_wgt3, "FIFO Weighted Random Test 3 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue_wgt4, "FIFO Weighted Random Test 4 @ 0", 0, add_size);
    fifo_sim(fifo_sch, track_queue_wgt5, "FIFO Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    fifo_sim(fifo_sch, track_queue_wgt1, "FIFO Weighted Random Test 1 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue_wgt2, "FIFO Weighted Random Test 2 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue_wgt3, "FIFO Weighted Random Test 3 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue_wgt4, "FIFO Weighted Random Test 4 @ 100", 100, add_size);
    fifo_sim(fifo_sch, track_queue_wgt5, "FIFO Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    fifo_sim(fifo_sch, track_queue_wgt1, "FIFO Weighted Random Test 1 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue_wgt2, "FIFO Weighted Random Test 2 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue_wgt3, "FIFO Weighted Random Test 3 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue_wgt4, "FIFO Weighted Random Test 4 @ 199", 199, add_size);
    fifo_sim(fifo_sch, track_queue_wgt5, "FIFO Weighted Random Test 5 @ 199", 199, add_size);
    // Standard FIFO Test
    fifo_sch.reset("FIFO Standard Test", 100);
    for(int i = 0; i < standard.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(fifo_sch.full()){
                i = j;
                break;
            }
            fifo_sch.add(standard[j]);
        }
        fifo_sch.read();
    }
    std::string report = fifo_sch.print_report();
    std::cout << "FIFO Standard Test" << "\n" << report << std::endl;

    // checks if the lifo read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments lifo_good_reads
    // LIFO Tests
    // reads in lifo_read_size entries from the track_queue:
    // Track 0 tests
    lifo lifo_sch(max_tracks, max_buffer, start_track);
    lifo_sim(lifo_sch, track_queue1, "LIFO Random Test 1 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue2, "LIFO Random Test 2 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue3, "LIFO Random Test 3 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue4, "LIFO Random Test 4 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue5, "LIFO Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    lifo_sim(lifo_sch, track_queue1, "LIFO Random Test 1 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue2, "LIFO Random Test 2 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue3, "LIFO Random Test 3 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue4, "LIFO Random Test 4 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue5, "LIFO Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    lifo_sim(lifo_sch, track_queue1, "LIFO Random Test 1 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue2, "LIFO Random Test 2 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue3, "LIFO Random Test 3 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue4, "LIFO Random Test 4 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue5, "LIFO Random Test 5 @ 199", 199, add_size);
    //-------------------
    //Weighted LIFO Tests
    //-------------------
    // Track 0 tests
    lifo_sim(lifo_sch, track_queue_wgt1, "LIFO Weighted Random Test 1 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue_wgt2, "LIFO Weighted Random Test 2 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue_wgt3, "LIFO Weighted Random Test 3 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue_wgt4, "LIFO Weighted Random Test 4 @ 0", 0, add_size);
    lifo_sim(lifo_sch, track_queue_wgt5, "LIFO Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    lifo_sim(lifo_sch, track_queue_wgt1, "LIFO Weighted Random Test 1 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue_wgt2, "LIFO Weighted Random Test 2 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue_wgt3, "LIFO Weighted Random Test 3 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue_wgt4, "LIFO Weighted Random Test 4 @ 100", 100, add_size);
    lifo_sim(lifo_sch, track_queue_wgt5, "LIFO Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    lifo_sim(lifo_sch, track_queue_wgt1, "LIFO Weighted Random Test 1 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue_wgt2, "LIFO Weighted Random Test 2 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue_wgt3, "LIFO Weighted Random Test 3 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue_wgt4, "LIFO Weighted Random Test 4 @ 199", 199, add_size);
    lifo_sim(lifo_sch, track_queue_wgt5, "LIFO Weighted Random Test 5 @ 199", 199, add_size);
    

    // checks if the sstf read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments sstf_good_reads
    // SSTF Tests
    // reads in SSTF_read_size entries from the track_queue:
    // Track 0 tests
    sstf sstf_sch(max_tracks, max_buffer, start_track);
    sstf_sim(sstf_sch, track_queue1, "SSTF Random Test 1 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue2, "SSTF Random Test 2 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue3, "SSTF Random Test 3 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue4, "SSTF Random Test 4 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue5, "SSTF Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    sstf_sim(sstf_sch, track_queue1, "SSTF Random Test 1 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue2, "SSTF Random Test 2 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue3, "SSTF Random Test 3 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue4, "SSTF Random Test 4 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue5, "SSTF Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    sstf_sim(sstf_sch, track_queue1, "SSTF Random Test 1 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue2, "SSTF Random Test 2 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue3, "SSTF Random Test 3 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue4, "SSTF Random Test 4 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue5, "SSTF Random Test 5 @ 199", 199, add_size);
    //-------------------
    //Weighted SSTF Tests
    //-------------------
    // Track 0 tests
    sstf_sim(sstf_sch, track_queue_wgt1, "SSTF Weighted Random Test 1 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue_wgt2, "SSTF Weighted Random Test 2 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue_wgt3, "SSTF Weighted Random Test 3 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue_wgt4, "SSTF Weighted Random Test 4 @ 0", 0, add_size);
    sstf_sim(sstf_sch, track_queue_wgt5, "SSTF Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    sstf_sim(sstf_sch, track_queue_wgt1, "SSTF Weighted Random Test 1 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue_wgt2, "SSTF Weighted Random Test 2 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue_wgt3, "SSTF Weighted Random Test 3 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue_wgt4, "SSTF Weighted Random Test 4 @ 100", 100, add_size);
    sstf_sim(sstf_sch, track_queue_wgt5, "SSTF Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    sstf_sim(sstf_sch, track_queue_wgt1, "SSTF Weighted Random Test 1 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue_wgt2, "SSTF Weighted Random Test 2 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue_wgt3, "SSTF Weighted Random Test 3 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue_wgt4, "SSTF Weighted Random Test 4 @ 199", 199, add_size);
    sstf_sim(sstf_sch, track_queue_wgt5, "SSTF Weighted Random Test 5 @ 199", 199, add_size);
    // SSTF Standard Test
    sstf_sch.reset("SSTF Standard Test", 100);
    for(int i = 0; i < standard.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(sstf_sch.full()){
                i = j;
                break;
            }
            sstf_sch.add(standard[j]);
        }
        sstf_sch.read();
    }
    report = sstf_sch.print_report();
    std::cout << "SSTF Standard Test" << "\n" << report << std::endl;


    // SCAN Tests
    // reads in scan_read_size entries from the track_queue:
    // Track 0 tests
    // checks if the scan read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments scan_good_reads
    scan scan_sch(max_tracks, max_buffer, start_track);
    scan_sim(scan_sch, track_queue1, "SCAN Random Test 1 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue2, "SCAN Random Test 2 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue3, "SCAN Random Test 3 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue4, "SCAN Random Test 4 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue5, "SCAN Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    scan_sim(scan_sch, track_queue1, "SCAN Random Test 1 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue2, "SCAN Random Test 2 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue3, "SCAN Random Test 3 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue4, "SCAN Random Test 4 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue5, "SCAN Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    scan_sim(scan_sch, track_queue1, "SCAN Random Test 1 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue2, "SCAN Random Test 2 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue3, "SCAN Random Test 3 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue4, "SCAN Random Test 4 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue5, "SCAN Random Test 5 @ 199", 199, add_size);
    //-------------------
    //Weighted SCAN Tests
    //-------------------
    // Track 0 tests
    scan_sim(scan_sch, track_queue_wgt1, "SCAN Weighted Random Test 1 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue_wgt2, "SCAN Weighted Random Test 2 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue_wgt3, "SCAN Weighted Random Test 3 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue_wgt4, "SCAN Weighted Random Test 4 @ 0", 0, add_size);
    scan_sim(scan_sch, track_queue_wgt5, "SCAN Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    scan_sim(scan_sch, track_queue_wgt1, "SCAN Weighted Random Test 1 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue_wgt2, "SCAN Weighted Random Test 2 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue_wgt3, "SCAN Weighted Random Test 3 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue_wgt4, "SCAN Weighted Random Test 4 @ 100", 100, add_size);
    scan_sim(scan_sch, track_queue_wgt5, "SCAN Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    scan_sim(scan_sch, track_queue_wgt1, "SCAN Weighted Random Test 1 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue_wgt2, "SCAN Weighted Random Test 2 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue_wgt3, "SCAN Weighted Random Test 3 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue_wgt4, "SCAN Weighted Random Test 4 @ 199", 199, add_size);
    scan_sim(scan_sch, track_queue_wgt5, "SCAN Weighted Random Test 5 @ 199", 199, add_size);
    // SCAN Standard Test
    scan_sch.reset("SCAN Standard Test", 100);
    for(int i = 0; i < standard.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(scan_sch.full()){
                i = j;
                break;
            }
            scan_sch.add(standard[j]);
        }
        scan_sch.read();
    }
    report = scan_sch.print_report();
    std::cout << "SCAN Standard Test" << "\n" << report << std::endl;

    // CSCAN Tests
    // reads in cscan_read_size entries from the track_queue:
    // Track 0 tests
    // checks if the cscan read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments cscan_good_reads
    cscan cscan_sch(max_tracks, max_buffer, start_track, INC);
    cscan_sim(cscan_sch, track_queue1, "CSCAN Random Test 1 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue2, "CSCAN Random Test 2 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue3, "CSCAN Random Test 3 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue4, "CSCAN Random Test 4 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue5, "CSCAN Random Test 5 @ 0", 0, add_size, INC);
    // Track 100 tests
    cscan_sim(cscan_sch, track_queue1, "CSCAN Random Test 1 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue2, "CSCAN Random Test 2 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue3, "CSCAN Random Test 3 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue4, "CSCAN Random Test 4 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue5, "CSCAN Random Test 5 @ 100", 100, add_size, INC);
    // Track 199 tests
    cscan_sim(cscan_sch, track_queue1, "CSCAN Random Test 1 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue2, "CSCAN Random Test 2 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue3, "CSCAN Random Test 3 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue4, "CSCAN Random Test 4 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue5, "CSCAN Random Test 5 @ 199", 199, add_size, INC);
    //-------------------
    //Weighted CSCAN Tests
    //-------------------
    // Track 0 tests
    cscan_sim(cscan_sch, track_queue_wgt1, "CSCAN Weighted Random Test 1 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt2, "CSCAN Weighted Random Test 2 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt3, "CSCAN Weighted Random Test 3 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt4, "CSCAN Weighted Random Test 4 @ 0", 0, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt5, "CSCAN Weighted Random Test 5 @ 0", 0, add_size, INC);
    // Track 100 tests
    cscan_sim(cscan_sch, track_queue_wgt1, "CSCAN Weighted Random Test 1 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt2, "CSCAN Weighted Random Test 2 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt3, "CSCAN Weighted Random Test 3 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt4, "CSCAN Weighted Random Test 4 @ 100", 100, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt5, "CSCAN Weighted Random Test 5 @ 100", 100, add_size, INC);
    // Track 199 tests
    cscan_sim(cscan_sch, track_queue_wgt1, "CSCAN Weighted Random Test 1 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt2, "CSCAN Weighted Random Test 2 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt3, "CSCAN Weighted Random Test 3 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt4, "CSCAN Weighted Random Test 4 @ 199", 199, add_size, INC);
    cscan_sim(cscan_sch, track_queue_wgt5, "CSCAN Weighted Random Test 5 @ 199", 199, add_size, INC);
    // CSCAN Standard Test
    cscan_sch.reset("CSCAN Standard Test", 100);
    for(int i = 0; i < standard.size(); ){
        for(int j = i; j < i+add_size; ++j){
            if(cscan_sch.full()){
                i = j;
                break;
            }
            cscan_sch.add(standard[j]);
        }
        cscan_sch.read();
    }
    report = cscan_sch.print_report();
    std::cout << "CSCAN Standard Test" << "\n" << report << std::endl;

    // N_STEP_SCAN Tests
    // reads in n_step_scan_read_size entries from the track_queue:
    // Track 0 tests
    // checks if the n_step_scan read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments n_step_scan_good_reads
	n_step_scan n_step_sch(max_tracks, max_buffer, start_track, small_buffer, IDLE);
	n_step_sim(n_step_sch, track_queue1, "N STEP SCAN Random Test 1 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue2, "N STEP SCAN Random Test 2 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue3, "N STEP SCAN Random Test 3 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue4, "N STEP SCAN Random Test 4 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue5, "N STEP SCAN Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    n_step_sim(n_step_sch, track_queue1, "N STEP SCAN Random Test 1 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue2, "N STEP SCAN Random Test 2 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue3, "N STEP SCAN Random Test 3 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue4, "N STEP SCAN Random Test 4 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue5, "N STEP SCAN Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    n_step_sim(n_step_sch, track_queue1, "N STEP SCAN Random Test 1 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue2, "N STEP SCAN Random Test 2 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue3, "N STEP SCAN Random Test 3 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue4, "N STEP SCAN Random Test 4 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue5, "N STEP SCAN Random Test 5 @ 199", 199, add_size);
    //-------------------
    //Weighted N STEP SCAN Tests
    //-------------------
    // Track 0 tests
    n_step_sim(n_step_sch, track_queue_wgt1, "N STEP SCAN Weighted Random Test 1 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue_wgt2, "N STEP SCAN Weighted Random Test 2 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue_wgt3, "N STEP SCAN Weighted Random Test 3 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue_wgt4, "N STEP SCAN Weighted Random Test 4 @ 0", 0, add_size);
    n_step_sim(n_step_sch, track_queue_wgt5, "N STEP SCAN Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    n_step_sim(n_step_sch, track_queue_wgt1, "N STEP SCAN Weighted Random Test 1 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue_wgt2, "N STEP SCAN Weighted Random Test 2 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue_wgt3, "N STEP SCAN Weighted Random Test 3 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue_wgt4, "N STEP SCAN Weighted Random Test 4 @ 100", 100, add_size);
    n_step_sim(n_step_sch, track_queue_wgt5, "N STEP SCAN Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    n_step_sim(n_step_sch, track_queue_wgt1, "N STEP SCAN Weighted Random Test 1 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue_wgt2, "N STEP SCAN Weighted Random Test 2 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue_wgt3, "N STEP SCAN Weighted Random Test 3 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue_wgt4, "N STEP SCAN Weighted Random Test 4 @ 199", 199, add_size);
    n_step_sim(n_step_sch, track_queue_wgt5, "N STEP SCAN Weighted Random Test 5 @ 199", 199, add_size);

    
    // FSCAN Tests
    // reads in fscan_read_size entries from the track_queue:
    // Track 0 tests
    // checks if the fscan read_queue is full; if it isn't, reads in 25 entries from the track_queue_wgt: increments fscan_good_reads
	fscan fscan_sch(max_tracks, max_buffer, start_track, IDLE);
	fscan_sim(fscan_sch, track_queue1, "FSCAN Random Test 1 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue2, "FSCAN Random Test 2 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue3, "FSCAN Random Test 3 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue4, "FSCAN Random Test 4 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue5, "FSCAN Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    fscan_sim(fscan_sch, track_queue1, "FSCAN Random Test 1 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue2, "FSCAN Random Test 2 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue3, "FSCAN Random Test 3 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue4, "FSCAN Random Test 4 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue5, "FSCAN Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    fscan_sim(fscan_sch, track_queue1, "FSCAN Random Test 1 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue2, "FSCAN Random Test 2 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue3, "FSCAN Random Test 3 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue4, "FSCAN Random Test 4 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue5, "FSCAN Random Test 5 @ 199", 199, add_size);
    //-------------------
    //Weighted FSCAN Tests
    //-------------------
    // Track 0 tests
    fscan_sim(fscan_sch, track_queue_wgt1, "FSCAN Weighted Random Test 1 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue_wgt2, "FSCAN Weighted Random Test 2 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue_wgt3, "FSCAN Weighted Random Test 3 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue_wgt4, "FSCAN Weighted Random Test 4 @ 0", 0, add_size);
    fscan_sim(fscan_sch, track_queue_wgt5, "FSCAN Weighted Random Test 5 @ 0", 0, add_size);
    // Track 100 tests
    fscan_sim(fscan_sch, track_queue_wgt1, "FSCAN Weighted Random Test 1 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue_wgt2, "FSCAN Weighted Random Test 2 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue_wgt3, "FSCAN Weighted Random Test 3 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue_wgt4, "FSCAN Weighted Random Test 4 @ 100", 100, add_size);
    fscan_sim(fscan_sch, track_queue_wgt5, "FSCAN Weighted Random Test 5 @ 100", 100, add_size);
    // Track 199 tests
    fscan_sim(fscan_sch, track_queue_wgt1, "FSCAN Weighted Random Test 1 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue_wgt2, "FSCAN Weighted Random Test 2 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue_wgt3, "FSCAN Weighted Random Test 3 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue_wgt4, "FSCAN Weighted Random Test 4 @ 199", 199, add_size);
    fscan_sim(fscan_sch, track_queue_wgt5, "FSCAN Weighted Random Test 5 @ 199", 199, add_size);

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