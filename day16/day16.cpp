#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>

int main() {
    std::ifstream puzzle_input("day16.txt");
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> rules;
    std::unordered_set<std::string> departure_idx = {
        "departure location",
        "departure station",
        "departure platform",
        "departure track",
        "departure date",
        "departure time"
    };
    std::regex number_regex("[0-9]+");
    std::smatch number_match;
    std::string line;
    std::vector<std::string> splitter;
    std::string rule_key;
    for(int i = 0; i < 20; i++) {
        std::getline(puzzle_input, line);

        boost::algorithm::iter_split(splitter, line, boost::algorithm::first_finder(":"));
        rule_key = splitter[0];
        rules[rule_key] = std::vector<std::pair<int, int>>();

        boost::algorithm::iter_split(splitter, splitter[1], boost::algorithm::first_finder(" or "));
        std::vector<std::string> constraint_bounds;
        for(auto& constraint : splitter) {
            boost::algorithm::trim(constraint);
            boost::algorithm::iter_split(constraint_bounds, constraint, boost::algorithm::first_finder("-"));
            rules[rule_key].push_back({std::stoi(constraint_bounds[0]), std::stoi(constraint_bounds[1])});
        }
    }

    std::vector<std::vector<std::string>> tickets;
    std::vector<std::string> ticket, my_ticket;
    bool me, valid, valid_ticket;
    int TSER = 0, value;
    while(!puzzle_input.eof()) {
        std::getline(puzzle_input, line);
        if(line == "") continue;
        if(line == "your ticket:") {
            me = true;
            continue;
        }
        if(line == "nearby tickets:") continue;
        if(me) {
            boost::algorithm::iter_split(my_ticket, line, boost::algorithm::first_finder(","));
            me = false;
        } else {
            boost::algorithm::iter_split(ticket, line, boost::algorithm::first_finder(","));
            valid_ticket = true;
            for(auto const& el : ticket) {
                valid = false;
                for(auto const& pair : rules) {
                value = std::stoi(el);
                    for(auto const& bounds : pair.second) {
                        if(valid) break;
                        valid |= value >= bounds.first && value <= bounds.second;
                    }
                    if(valid) break;
                }
                if(!valid) {
                    TSER += value;
                    valid_ticket = false;
                }
            }
            if(valid_ticket) {
                tickets.push_back(ticket);
            }
        }
    }
    std::cout << "First task - ticket scanning error rate" << std::endl << TSER << std::endl << std::endl;

    std::vector<std::pair<std::string, std::unordered_set<int>>> idx_list;
    int field_count = my_ticket.size();
    bool valid_field;
    for(auto const& r : rules) {
        idx_list.push_back({r.first, std::unordered_set<int>()});
        for(int field_idx = 0; field_idx < field_count; field_idx++) {
            valid_field = true;
            for(auto const& t : tickets) {
                TSER = std::stoi(t[field_idx]);
                valid = false;
                for(auto const& bounds : r.second) {
                    valid |= TSER >= bounds.first && TSER <= bounds.second;
                }
                valid_field = valid_field && valid;
                if(!valid_field) {
                    break;
                }
            }
            if(valid_field) {
                idx_list[idx_list.size()-1].second.insert(field_idx);
            }
        }
    }

    long long int mul = 1;
    std::unordered_set<int> used;
    int deps = 0;

    std::sort(idx_list.begin(), idx_list.end(), [](const auto& a, const auto& b) {return a.second.size() < b.second.size();});
    for(auto const& rule_fields : idx_list) {
        if (deps == departure_idx.size()) {
            break;
        }
        for(auto const& field : rule_fields.second) {
            if(used.find(field) == used.end()) {
                used.insert(field);
                if(departure_idx.find(rule_fields.first) != departure_idx.end()) {
                    deps++;
                    mul *= std::stoll(my_ticket[field]);
                }
            }
        }
    }

    std::cout << "Second task - multiple of all departure positions" << std::endl << mul << std::endl;
}