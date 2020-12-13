#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <functional>

#define OCCUPIED '#'
#define EMPTY 'L'
#define FLOOR '.'

#define THRESHOLD_1 4
#define THRESHOLD_2 5

std::map<char, char> swap_element({
    {OCCUPIED, EMPTY}, {EMPTY, OCCUPIED}
});

std::vector<std::pair<int, int>> directions({
    std::pair<int, int>(0, 1),
    std::pair<int, int>(0, -1),
    std::pair<int, int>(1, 0),
    std::pair<int, int>(-1, 0),
    std::pair<int, int>(1, 1),
    std::pair<int, int>(1, -1),
    std::pair<int, int>(-1, 1),
    std::pair<int, int>(-1, -1),
});

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

bool is_now_empty_1(const std::vector<std::vector<char>> &map, int row, int column) {
    int occupied = 0;
    for(int i = max(0, (row - 1)); i <= min((map.size() - 1), (row + 1)); i++) {
        for(int j = max(0, (column - 1)); j <= min((map[0].size()-1), (column + 1)); j++) {
            if(i == row && j == column) continue;
            if(map[i][j] == OCCUPIED) occupied++;
            if(occupied >= THRESHOLD_1) return true;
        }
    }
    return false;
}

bool is_now_occupied_1(const std::vector<std::vector<char>> &map, int row, int column) {
    for(int i = max(0, (row - 1)); i <= min((map.size() - 1), (row + 1)); i++) {
        for(int j = max(0, (column - 1)); j <= min((map[0].size() - 1), (column + 1)); j++) {
            if(i == row && j == column) continue;
            if(map[i][j] == OCCUPIED) return false;
        }
    }
    return true;
}

bool is_within_bounds(int row, int col, int rows, int cols, int dir_row, int dir_col) {
    //                     not on edge             left/top, no further (-)     right/bottom, no further (+)
    bool row_bounds = row > 0 && row < rows - 1 || row == 0 && dir_row > -1 || row == rows - 1 && dir_row < 1;
    bool col_bounds = col > 0 && col < cols - 1 || col == 0 && dir_col > -1 || col == cols - 1 && dir_col < 1;
    return row_bounds && col_bounds;
}

bool is_now_empty_2(const std::vector<std::vector<char>> &map, int row, int column) {
    int occupied = 0;
    int i, j;
    for(auto dir : directions) {
        i = row; j = column;
        while(is_within_bounds(i, j, map.size(), map[0].size(), dir.first, dir.second)) {
            i += dir.first;
            j += dir.second;
            if(map[i][j] != FLOOR) {
                if(map[i][j] == OCCUPIED) {
                    occupied++;
                }
                break;
            }
        }
        if(occupied >= THRESHOLD_2) return true;
    }
    return false;
}

bool is_now_occupied_2(const std::vector<std::vector<char>> &map, int row, int column) {
    int i, j;
    for(auto dir : directions) {
        i = row; j = column;
        while(is_within_bounds(i, j, map.size(), map[0].size(), dir.first, dir.second)) {
            i += dir.first;
            j += dir.second;
            if(map[i][j] != FLOOR) {
                if(map[i][j] == OCCUPIED) {
                    return false;
                }
                break;
            }
        }
    }
    return true;
}

bool will_change_1(const std::vector<std::vector<char>> &map, int row, int column) {
    return (map[row][column] == EMPTY && is_now_occupied_1(map, row, column)) || (map[row][column] == OCCUPIED && is_now_empty_1(map, row, column));
}

bool will_change_2(const std::vector<std::vector<char>> &map, int row, int column) {
    return (map[row][column] == EMPTY && is_now_occupied_2(map, row, column)) || (map[row][column] == OCCUPIED && is_now_empty_2(map, row, column));
}

bool iterate(std::vector<std::vector<char>> &map, std::function<bool(const std::vector<std::vector<char>> &, int, int)> will_change) {
    std::vector<std::vector<char>> new_map;
    std::vector<char> row;
    bool changed = false;
    for(auto i = 0; i < map.size(); i++) {
        for(auto j = 0; j < map[0].size(); j++) {
            if(will_change(map, i, j)) {
                changed = true;
                row.push_back(swap_element[map[i][j]]);
            } else {
                row.push_back(map[i][j]);
            }
        }
        new_map.push_back(row);
        row.clear();
    }
    map = new_map;
    return changed;
}

int count_occupied(const std::vector<std::vector<char>> &map) {
    int occupied = 0;
    for(auto row : map) {
        for(auto seat : row) {
            if(seat == OCCUPIED) occupied++;
        }
    }
    return occupied;
}

int main() {
    std::ifstream puzzle_input("day11.txt");
    std::vector<std::vector<char>> original_map;
    std::string line;
    std::vector<char> line_vector;
    while(!puzzle_input.eof()) {
        puzzle_input >> line;
        for(auto c : line) {
            line_vector.push_back(c);
        }
        original_map.push_back(line_vector);
        line_vector.clear();
    }

    std::vector<std::vector<char>> map_1 = original_map;
    while(iterate(map_1, will_change_1)) {}
    std::cout << "First task - how many seats are occupied in the converged state?" << std::endl << count_occupied(map_1) << std::endl << std::endl;

    std::vector<std::vector<char>> map_2 = original_map;
    while(iterate(map_2, will_change_2)) {}
    std::cout << "Second task - how many seats are occupied in the converged state with new rules?" << std::endl << count_occupied(map_2) << std::endl;
}