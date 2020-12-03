#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define TREE '#'

int main() {
    std::ifstream puzzle_input("day03.txt");
    std::vector<std::string> map_chunk;
    std::string t;
    while(!puzzle_input.eof()) {
        puzzle_input >> t;
        map_chunk.push_back(t);
    }
    int slopes[5][2] = {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2},
    };
    int first_task_count = 0;
    long int multiple = 1;
    for(int i = 0; i < 5; i++) {
        int tree_count = 0;
        int row = 0, col = 0;
        int dcol = slopes[i][0], drow = slopes[i][1];
        while(row < map_chunk.size()) {
            if(map_chunk[row][col] == TREE) {
                tree_count++;
            }
            row += drow;
            col = (col + dcol) % map_chunk[0].length();
        }
        multiple *= tree_count;
        if(i == 1) {
            first_task_count = tree_count;
        }
    }
    std::cout << "First task - count trees in the way" << std::endl << first_task_count << std::endl << std::endl;
    std::cout << "Second task - multiply tree counts on different slopes" << std::endl << multiple << std::endl << std::endl;
    return 0;
}