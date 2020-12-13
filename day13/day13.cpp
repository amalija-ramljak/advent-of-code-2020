#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

long long int mod(long long int a, long long int b) {
    if(a < 0) {
        return (a % b) + b;
    } else {
        return a % b;
    }
}

int main() {
    std::ifstream puzzle_input("day13.txt");
    int earliest_timestamp;
    puzzle_input >> earliest_timestamp;

    std::vector<int> buses;
    std::map<int, int> order;
    int bus, bus_id = 0, i = 0;
    long long int N = 1;
    while(!puzzle_input.eof()) {
        bus = puzzle_input.get();
        if(bus >= 48 && bus <= 57) {
            bus -= 48;
            bus_id *= 10;
            bus_id += bus;
        } else {
            if(bus_id > 0) {
                buses.push_back(bus_id);
                order[bus_id] = -i;
                N *= bus_id;
                i++;
            }
            if(bus == 'x') {
                i++;
            }
            bus_id = 0;
        }
    }

    // task 1
    bus = -1;
    int leave_time = earliest_timestamp - 1;
    bool found = false;
    do {
        leave_time++;
        for(auto const& bus_id : buses) {
            if(leave_time % bus_id == 0) {
                found = true;
                bus = bus_id;
                break;
            }
        }
    } while(!found);
    std::cout << "First task - what's the earliest bus I can catch multiplied by wait time?" << std::endl << bus * (leave_time - earliest_timestamp) << std::endl << std::endl;

    // task 2
    long long int timestamp = 0;
    long long int Ni, n, xi, it;
    for(auto const& el : order) {
        n = -1;
        Ni = N / el.first;
        do {
            n++;
            xi = (n * el.first + 1) % (Ni % el.first);
        } while(xi != 0);
        xi = (n * el.first + 1) / (Ni % el.first);
        timestamp += mod(el.second * Ni * xi, N);
    }
    std::cout << "Second task - find consecutive timestamps" << std::endl << mod(timestamp, N) << std::endl;
}