#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <functional>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

std::map<std::string, int> legend ({
    {"N", NORTH},
    {"E", EAST},
    {"S", SOUTH},
    {"W", WEST},
});

std::vector<std::string> legend_back = {"N", "E", "S", "W"};

std::vector<std::pair<int, int>> direction_vectors ({
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
});

// i => -north +south
// j => +east -west

int ship_direction_1 = EAST;
int ship_position_i_1 = 0;
int ship_position_j_1 = 0;

int ship_position_i_2 = 0;
int ship_position_j_2 = 0;
int waypoint_i = -1;
int waypoint_j = 10;

void rotate_ship(std::string direction, int value) {
    int move = direction == "R" ? value/90 : 4-value/90;
    ship_direction_1 = (ship_direction_1 + move) % 4;
}

void move_ship(std::string direction, int value) {
    int direction_idx = direction == "F" ? ship_direction_1 : legend[direction];
    ship_position_i_1 += value * direction_vectors[direction_idx].first;
    ship_position_j_1 += value * direction_vectors[direction_idx].second;
}

void move_ship_2(std::string direction, int value) {
    int move_i = value * waypoint_i;
    int move_j = value * waypoint_j;
    ship_position_i_2 += move_i;
    ship_position_j_2 += move_j;
}

void rotate_waypoint(std::string direction, int value) {
    int rot_count = direction == "R" ? value/90 : 4-value/90;
    int new_i, new_j;
    switch (rot_count)
    {
        case 1:
            new_i = waypoint_j;
            new_j = -waypoint_i;
            break;

        case 2:
            new_i = -waypoint_i;
            new_j = -waypoint_j;
            break;
        
        case 3:
            new_i = -waypoint_j;
            new_j = waypoint_i;
            break;

        default:
            break;
    }
    waypoint_i = new_i;
    waypoint_j = new_j;
}

void move_waypoint(std::string direction, int value) {
    int direction_idx = legend[direction];
    waypoint_i += value * direction_vectors[direction_idx].first;
    waypoint_j += value * direction_vectors[direction_idx].second;
}

std::map<std::string, std::function<void(std::string, int)>> actions_1({
    {"N", move_ship},
    {"S", move_ship},
    {"E", move_ship},
    {"W", move_ship},
    {"F", move_ship},
    {"R", rotate_ship},
    {"L", rotate_ship},
});

std::map<std::string, std::function<void(std::string, int)>> actions_2({
    {"N", move_waypoint},
    {"S", move_waypoint},
    {"E", move_waypoint},
    {"W", move_waypoint},
    {"F", move_ship_2},
    {"R", rotate_waypoint},
    {"L", rotate_waypoint},
});

int main() {
    std::ifstream puzzle_input("day12.txt");

    std::regex direction_regex("[A-Z]");
    std::smatch direction_match;
    std::regex value_regex("[0-9]+");
    std::smatch value_match;

    std::string line;
    std::string direction;
    std::string value;
    while(!puzzle_input.eof()) {
        puzzle_input >> line;
        std::regex_search(line, direction_match, direction_regex);
        std::regex_search(line, value_match, value_regex);
        direction = direction_match[0];
        value = value_match[0];
        actions_1.at(direction)(direction, std::stoi(value));
        actions_2.at(direction)(direction, std::stoi(value));
    }

    std::cout << "First task - Manhattan distance of start and end point" << std::endl << std::abs(ship_position_i_1) + std::abs(ship_position_j_1) << std::endl << std::endl;
    std::cout << "Second task - Manhattan distance of start and end point, new rules" << std::endl << std::abs(ship_position_i_2) + std::abs(ship_position_j_2) << std::endl;
}