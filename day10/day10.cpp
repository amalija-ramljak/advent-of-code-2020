#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <set>

std::map<int, long long int> cache;

long long int count_paths(const std::map<int, std::vector<int>> &next, int current) {
    if(next.at(current).size() == 0) {
        return 1;
    }
    if(cache.find(current) != cache.end()) {
        return cache.at(current);
    }
    long long int count = 0;
    for(auto n : next.at(current)) {
        count += count_paths(next, n);
    }
    cache[current] = count;
    return count;
}

int main() {
    std::ifstream puzzle_input("day10.txt");

    std::vector<int> joltages;
    int j;
    while(!puzzle_input.eof()) {
        puzzle_input >> j;
        joltages.push_back(j);
    }
    joltages.push_back(0);
    std::sort(joltages.begin(), joltages.end());

    std::map<int, int> differences;
    differences[0] = 0;
    differences[1] = 0;
    differences[2] = 0;
    differences[3] = 1; // device joltage is 3 higher than highest
    int previous_jolt = 0;

    std::map<int, std::vector<int>> next; // 1 => [2, 3, 4]
    int i = 0;
    for(auto jolt : joltages) {
        // task 1
        differences[jolt-previous_jolt] += 1;
        previous_jolt = jolt;

        //task 2
        next[jolt] = std::vector<int>();
        for(j = i+1; j < joltages.size() && joltages[j] - jolt < 4; j++) {
            next[jolt].push_back(joltages[j]);
        }
        i++;
    }
    
    std::cout << "First task - multiple of 1-jolt-difference count and 3-jolt-difference count" << std::endl << differences[1] * differences[3] << std::endl << std::endl;
    std::cout << "Second task - in how many ways can the adapters be arranged?" << std::endl << count_paths(next, joltages[0]) << std::endl;
}