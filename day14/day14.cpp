#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>

#define INT_LENGTH 36

int main() {
    std::ifstream puzzle_input("day14.txt");

    unsigned long int clear_mask = 0, or_mask = 0, clear_mask_X = 0;
    std::vector<unsigned long int> or_masks;
    std::map<unsigned long int, unsigned long int> memory;
    std::map<unsigned long int, unsigned long int> memory_2;
    
    std::string mask_input, line;
    std::regex number_regex("[0-9]+");
    std::smatch numbers;
    std::vector<unsigned long int> memval;
    while(!puzzle_input.eof()) {
        std::getline(puzzle_input, line);
        if(line[1] == 'a') {
            mask_input = line.substr(7, INT_LENGTH);
            clear_mask = 0; or_mask = 0;
            or_masks.clear();
            for(auto it=line.begin(); it < line.end(); it++) {
                // starts as 0, so is irrelevant at beginning
                // won't shift too far after end of mask!
                clear_mask <<= 1;
                or_mask <<= 1;
                clear_mask_X <<= 1;
                if(or_masks.size() > 0) {
                    for(auto it=or_masks.begin(); it < or_masks.end(); it++) {
                        *it <<= 1;
                    }
                }
                switch (*it) {
                    case '0':
                        clear_mask += 1;
                        break;
                    case '1':
                        clear_mask += 1;
                        or_mask += 1;
                        clear_mask_X += 1;
                        if(or_masks.size() > 0) {
                            for(auto it=or_masks.begin(); it < or_masks.end(); it++) {
                                *it += 1;
                            }
                        }
                        break;
                    case 'X':
                        clear_mask_X += 1;
                        if(or_masks.size() > 0) {
                            int s = or_masks.size();
                            for(auto i = 0; i < s; i++) {
                                // add the pushed mask with 0 in place of X
                                or_masks.push_back(or_masks[i]);
                                // amend the old mask with 1 in place of X
                                or_masks[i] += 1;
                            }
                        } else {
                            // no masks? get the first ones in there
                            // or_mask has 1 where there are 1s, 0 where 0s
                            // these masks have that + 1s or 0s where X
                            or_masks.push_back(or_mask + 1);
                            or_masks.push_back(or_mask);
                        }
                        break;
                }
            }
        } else {
            while(std::regex_search(line, numbers, number_regex)) {
                memval.push_back(std::stol(numbers[0]));
                line = numbers.suffix().str();
            }
            // first the places with 0 and 1 are cleared, then the 0s in same places are replaces with 1s and 0s in or_mask
            memory[memval[0]] = ((memval[1] & ~clear_mask) | or_mask);
            for(auto orm : or_masks) {
                memory_2[((memval[0] & ~clear_mask_X) | orm)] = memval[1];
            }
            memval.clear();
        }
    }
    unsigned long int sum = 0;
    for(auto const& pair : memory) {
        sum += pair.second;
    }
    std::cout << "First task - decoder version 1" << std::endl << sum << std::endl << std::endl;
    sum = 0;
    for(auto const& pair : memory_2) {
        sum += pair.second;
    }
    std::cout << "Second task - decoder version 2" << std::endl << sum << std::endl;
}