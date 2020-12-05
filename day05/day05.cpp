#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define max(a,b) a > b ? a : b

int main() {
    std::ifstream puzzle_input("day05.txt");
    std::vector<int> IDs;
    int max_id = -1;
    int row_min, row_max, col_min, col_max;
    while(!puzzle_input.eof()) {
        row_min = 0; row_max = 127;
        col_min = 0; col_max = 7;
        std::string boarding_pass;
        puzzle_input >> boarding_pass;
        for(auto character: boarding_pass) {
            if(character == 'F') {
                row_max = row_min + ((row_max - row_min) / 2);
            } else if(character == 'B') {
                row_min = row_max - ((row_max - row_min) / 2);
            } else if(character == 'R') {
                col_min = col_max - ((col_max - col_min) / 2);
            } else if(character == 'L') {
                col_max = col_min + ((col_max - col_min) / 2);
            }
        }
        IDs.push_back(8 * row_max + col_max);
        max_id = max(max_id, 8*row_max + col_max);
    }
    std::cout << "First task - highest pass ID" << std::endl << max_id << std::endl << std::endl;

    std::sort(IDs.begin(), IDs.end());
    int previous_id = -1;
    for(auto id: IDs) {
        if(previous_id == -1) {
            previous_id = id;
            continue;
        }
        if(id - previous_id > 1) {
            std::cout << "Second task - find my pass ID" << std::endl << id-1 << std::endl;
            break;
        }
        previous_id = id;
    }
}