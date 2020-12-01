#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int main() {
    std::vector<int> entries;
    std::ifstream numbersFile("day1.txt");
    int entry;
    while(!numbersFile.eof()) {
        numbersFile >> entry;
        entries.push_back(entry);
    }

    const int sum = 2020;
    bool first = false;
    bool second = false;
    std::vector<int>::iterator it;
    for(auto i = 0; i < entries.size(); i++) {
        if(!first) {
            it = std::find(entries.begin(), entries.end(), sum-entries[i]);
            if(it != entries.end()) {
                first = true;
                std::cout << "First task - sum of two elements is " << sum << std::endl;
                std::cout << entries[i] << " + " << *it << " = " << entries[i] + *it << std::endl;
                std::cout << entries[i] << " * " << *it << " = " << entries[i] * *it << std::endl << std::endl;
            }
        }
        if(!second) {
            for(auto j = 0; j < entries.size(); j++) {
                if(j == i) continue;
                it = std::find(entries.begin(), entries.end(), sum-entries[i]-entries[j]);
                if(it != entries.end()) {
                    second = true;
                    std::cout << "Second task - sum of three elements is " << sum << std::endl;
                    std::cout << entries[i] << " + " << entries[j] << " + " << *it << " = " << entries[i] + entries[j] + *it << std::endl;
                    std::cout << entries[i] << " * " << entries[j] << " * " << *it << " = " << entries[i] * entries[j] * *it << std::endl << std::endl;
                    break;
                }
            }
        }
    }
}