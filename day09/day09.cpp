#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>

#define PREAMBLE 25

int main() {
    std::ifstream puzzle_input("day09.txt");

    std::vector<long int> numbers;
    std::deque<long int> preamble;

    long int n;
    for(int i = 0; i < PREAMBLE; i++) {
        puzzle_input >> n;
        preamble.push_back(n);
        numbers.push_back(n);
    }
    bool sum_of_two;
    long int broken = 0;
    while(!puzzle_input.eof()) {
        puzzle_input >> n;
        numbers.push_back(n);
        if(broken == 0) {
            sum_of_two = false;
            for(auto i = 0; i < preamble.size(); i++) {
                for(auto j = i + 1; j < preamble.size(); j++) {
                    if(preamble[i] != preamble[j] && preamble[i]+preamble[j] == n) {
                        sum_of_two = true;
                        break;
                    } 
                }
                if(sum_of_two) break;
            }
            if(!sum_of_two) {
                broken = n;
            }
            preamble.pop_front();
            preamble.push_back(n);
        }
    }
    if(!sum_of_two) {
        std::cout << "First task - first element that breaks the property" << std::endl << broken << std::endl << std::endl;
    }
    long int sum = 0;
    std::deque<long int> summed;
    for(auto i = 0; i < numbers.size(); i++) {
        if(sum < broken) {
            sum += numbers[i];
            summed.push_back(numbers[i]);
        } else if(sum > broken || sum == broken && summed.size() < 2) {
            sum -= summed[0];
            summed.pop_front();
            i--;
        } else {
            break;
        }
    }
    std::sort(summed.begin(), summed.end());
    std::cout << "Second task - smallest and largest number in contiguous sum equal to broken element" << std::endl << *summed.begin() + *(summed.end()-1) << std::endl;
}