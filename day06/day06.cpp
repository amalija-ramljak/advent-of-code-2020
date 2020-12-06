#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <algorithm>

int main() {
    std::ifstream puzzle_input("day06.txt");
    std::set<char> group_questions_1;
    std::set<char> group_questions_2;
    int sum_1 = 0;
    int sum_2 = 0;
    bool first = true;
    while(!puzzle_input.eof()) {
        std::string line;
        std::getline(puzzle_input, line);
        if(line.length() == 0) {
            sum_1 += group_questions_1.size();
            sum_2 += group_questions_2.size();
            group_questions_1.clear();
            group_questions_2.clear();
            first = true;
            continue;
        }
        std::set<char> person;
        for(auto question: line) {
            group_questions_1.insert(question);
            person.insert(question);
        }
        if(first) {
            group_questions_2 = person;
            first = false;
        } else {
            std::set<char> temp;
            std::set_intersection(
                group_questions_2.begin(), group_questions_2.end(),
                person.begin(), person.end(),
                std::inserter(temp, temp.begin())
            );
            group_questions_2 = temp;
        }
    }
    std::cout << "First task - anyone said yes" << std::endl << sum_1 << std::endl << std::endl;
    std::cout << "Second task - everyone said yes" << std::endl << sum_2 << std::endl;
}