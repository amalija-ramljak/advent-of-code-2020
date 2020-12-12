#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <set>

#define EMPTY "no other"
#define LOOKING_FOR "shiny gold"

bool contains(
    const std::map<std::string, std::map<std::string, int>> &rules,
    const std::string &container,
    std::set<std::string> &found_containers
) {
    if(rules.at(container).empty()) {
        return false;
    }
    if(rules.at(container).find(LOOKING_FOR) != rules.at(container).end()
        || found_containers.find(container) != found_containers.end()) {
        found_containers.insert(container);
        return true;
    }
    for(auto const& el : rules.at(container)) {
        if(contains(rules, el.first, found_containers)) {
            found_containers.insert(container);
            return true;
        }
    }
    return false;
}

int count_bags(
    const std::map<std::string, std::map<std::string, int>> &rules,
    const std::string &container,
    int parent_count
) {
    if(rules.at(container).empty()) {
        return 0;
    }
    int counter = 0;
    for(auto const& el : rules.at(container)) {
        counter += parent_count*el.second + count_bags(rules, el.first, parent_count*el.second);
    }
    return counter;
}

int main() {
    std::ifstream puzzle_input("day07.txt");

    std::regex bag_regex("([0-9]+ |)[a-z]+ [a-z]+ bag");
    std::regex colour_regex("[a-z]+ [a-z]+");
    std::regex count_regex("[0-9]+");

    std::smatch bag_match;
    std::smatch colour_match;
    std::smatch count_match;

    std::string key;
    std::string key_in;
    std::string count;

    std::map<std::string, std::map<std::string, int>> rules;
    std::string rule;
    while(!puzzle_input.eof()) {
        std::getline(puzzle_input, rule);

        bool start = true;
        while(std::regex_search(rule, bag_match, bag_regex)) {
            key_in = bag_match[0];
            rule = bag_match.suffix().str();
            std::regex_search(key_in, colour_match, colour_regex);
            std::regex_search(key_in, count_match, count_regex);
            count = count_match[0];
            key_in = colour_match[0];
            if(start) {
                start = false;
                key = key_in;
                rules.insert(std::pair<std::string, std::map<std::string, int>>(key, std::map<std::string, int>()));
            } else {
                if(key_in != EMPTY) {
                    rules[key].insert(std::pair<std::string, int>(key_in, std::stoi(count)));
                }
            }
        }
    }
    std::set<std::string> container_bags;
    for(auto const& el : rules) {
        if(container_bags.find(el.first) != container_bags.end()) {
            continue;
        }
        contains(rules, el.first, container_bags);
    }
    std::cout << "First task - how many types of bags can contain shiny gold?" << std::endl << container_bags.size() << std::endl << std::endl;

    std::cout << "Second task - how many bags do I have to stuff into shiny gold?" << std::endl << count_bags(rules, LOOKING_FOR, 1) << std::endl;
}