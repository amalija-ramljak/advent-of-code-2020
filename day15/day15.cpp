#include <iostream>
#include <fstream>
#include <vector>

#define VEC_SIZE 30000000
#define MAX_ITER 30000000

int main() {
    // in format with whitespace or newline between numbers
    std::ifstream puzzle_input("day15.txt");
    std::vector<int> last(VEC_SIZE, 0);
    int most_recent = -1, most_recent_last = -1, current_turn = 1, first;
    while(!puzzle_input.eof()) {
        most_recent_last = most_recent;
        puzzle_input >> most_recent;
        last[most_recent] = current_turn;
        current_turn++;
    }
    while(current_turn <= MAX_ITER) {
        most_recent_last = most_recent;
        most_recent = current_turn - 1 - last[most_recent];
        last[most_recent_last] = current_turn - 1;

        if(current_turn == 2020) first = most_recent;

        if(last[most_recent] == 0) {
            last[most_recent] = current_turn;
        } 

        current_turn++;
    }
    std::cout << "First task - 2020th number" << std::endl << first << std::endl << std::endl;
    std::cout << "Second task - 30000000th number" << std::endl << most_recent << std::endl;
}