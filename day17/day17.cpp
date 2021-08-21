#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

int main() {
    std::ifstream puzzle_input("day17.txt");

    std::unordered_set<std::vector<int>, VectorHash> active_positions_input, active_positions_current, active_positions_next;

    std::string line;
    int x = 0, y = 0, z = 0, w = 0;
    std::pair<int, int> borders_x ({0, 0}), borders_y ({0, 0}), borders_z ({0, 0}), borders_w ({0, 0});
    std::pair<int, int> borders_x_next ({0, 0}), borders_y_next ({0, 0}), borders_z_next ({0, 0}), borders_w_next ({0, 0});
    while(!puzzle_input.eof()) {
        std::getline(puzzle_input, line);
        for(auto const& position : line) {
            if (position == '#') {
                active_positions_input.insert({x, y, z, w});
            }
            x++;
        }
        borders_x.second = x - 1;
        x = 0;
        y++;
    }
    borders_y.second = y - 1;

    borders_x_next.first = borders_x.first; borders_x_next.second = borders_x.second;
    borders_y_next.first = borders_y.first; borders_y_next.second = borders_y.second;
    borders_z_next.first = borders_z.first; borders_z_next.second = borders_z.second;
    borders_w_next.first = borders_w.first; borders_w_next.second = borders_w.second;

    std::vector<int> searched ({0,0,0,0});
    int nb_x, nb_y, nb_z, nb_w, nb_active_count;
    bool is_active;
    bool second_task;
    for(int task = 1; task < 3; task++) {
        active_positions_current = active_positions_input;
        second_task = task == 2;
        for(int cycle = 0; cycle < 6; cycle++) {
            /** Outside loop, going over the area and then some */
            for(x = borders_x.first - 1; x <= borders_x.second + 1; x++) {
                for(y = borders_y.first - 1; y <= borders_y.second + 1; y++) {
                    for(z = borders_z.first - 1; z <= borders_z.second + 1; z++) {
                        for(w = second_task ? borders_w.first - 1 : 0; w <= (second_task ? borders_w.second + 1 : 0); w++) {
            /** Outside loop definition */
                            nb_active_count = 0;
                            /** Inner loop, neighbours of specific position */
                            for(nb_x = -1; nb_x < 2; nb_x++) {
                                for(nb_y = -1; nb_y < 2; nb_y++) {
                                    for(nb_z = -1; nb_z < 2; nb_z++) {
                                        for(nb_w = second_task ? -1 : 0; nb_w < (second_task ? 2 : 1); nb_w++) {
                            /** Inner loop definition */
                                            if (nb_x == 0 && nb_y == 0 && nb_z == 0 && nb_w == 0) {
                                                continue;
                                            }
                                            searched[0] = x + nb_x;
                                            searched[1] = y + nb_y;
                                            searched[2] = z + nb_z;
                                            searched[3] = w + nb_w;
                                            if (active_positions_current.find(searched) != active_positions_current.end()) {
                                                nb_active_count++;
                                            }
                                        }
                                    }
                                }
                            }
                            /** Inner loop */
                            if (nb_active_count != 2 && nb_active_count != 3) {
                                continue;
                            }
                            searched[0] = x;
                            searched[1] = y;
                            searched[2] = z;
                            searched[3] = w;
                            is_active = active_positions_current.find(searched) != active_positions_current.end();
                            if (is_active || !is_active && nb_active_count == 3) {
                                if (x < borders_x.first) {
                                    borders_x_next.first = x;
                                } else if (x > borders_x.second) {
                                    borders_x_next.second = x;
                                }
                                if (y < borders_y.first) {
                                    borders_y_next.first = y;
                                } else if (y > borders_y.second) {
                                    borders_y_next.second = y;
                                }
                                if (z < borders_z.first) {
                                    borders_z_next.first = z;
                                } else if (z > borders_z.second) {
                                    borders_z_next.second = z;
                                }
                                if (w < borders_w.first) {
                                    borders_w_next.first = w;
                                } else if (w > borders_w.second) {
                                    borders_w_next.second = w;
                                }
                                active_positions_next.insert({x, y, z, w});
                            }
                        }
                    }
                }
            }
            active_positions_current = active_positions_next;
            borders_x = borders_x_next;
            borders_y = borders_y_next;
            borders_z = borders_z_next;
            borders_w = borders_w_next;
            active_positions_next.clear();
        }

        switch (task)
        {
        case 1:
            std::cout << "First task - 3D active after 6 cycles" << std::endl << active_positions_current.size() << std::endl << std::endl;
            break;
        
        case 2:
            std::cout << "Second task - 4D active after 6 cycles" << std::endl << active_positions_current.size() << std::endl;
            break;
        }
    }
}