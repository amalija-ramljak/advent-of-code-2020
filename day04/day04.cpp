#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <regex>
#include <map>

#define BIRTH_YEAR "byr"
#define ISSUE_YEAR "iyr"
#define EXPIRATION_YEAR "eyr"
#define HEIGHT "hgt"
#define HAIR_COLOUR "hcl"
#define EYE_COLOUR "ecl"
#define PASSPORT_ID "pid"
#define COUNTRY_ID "cid"

#define HEIGHT_CM "cm"
#define HEIGHT_IN "in"

int main() {
    std::ifstream puzzle_input("day04.txt");
    int valid_1 = 0;
    int reqs_1 = 0;
    int valid_2 = 0;
    int reqs_2 = 0;
    std::regex hair_regex("#([0-9]|[a-f]){6}");
    std::regex eye_regex("amb|blu|brn|gry|grn|hzl|oth");
    std::regex pid_regex("([0-9]){9}");
    std::regex height_regex("[0-9]+(cm|in)");
    std::regex extract_height_regex("[0-9]+");
    std::regex extract_height_type_regex("(cm|in)");
    std::map<std::string, std::vector<int>> bounds;
    bounds[BIRTH_YEAR] = {1920, 2002};
    bounds[ISSUE_YEAR] = {2010, 2020};
    bounds[EXPIRATION_YEAR] = {2020, 2030};
    bounds[HEIGHT_CM] = {150, 193};
    bounds[HEIGHT_IN] = {59, 76};

    while(!puzzle_input.eof()) {
        char* linestr = (char *) malloc(80);
        puzzle_input.getline(linestr, 80);
        if(strlen(linestr) == 0) {
            if (reqs_1 == 7) {
                valid_1++;
                // won't be 7 unless all required keys are there
                if(reqs_2 == 7) {
                    valid_2++;
                }
            }
            reqs_1 = 0;
            reqs_2 = 0;
            continue;
        }
        std::istringstream line(linestr);
        while(!line.eof()) {
            std::string field;
            line >> field;
            std::string key = field.substr(0, 3), value = field.substr(4);
            if(key != COUNTRY_ID) {
                reqs_1++;
                bool valid_key = false;
                if(key == BIRTH_YEAR || key == ISSUE_YEAR || key == EXPIRATION_YEAR) {
                    int year = std::stoi(value);
                    valid_key = year >= bounds[key][0] && year <= bounds[key][1];
                } else if(key == HAIR_COLOUR || key == EYE_COLOUR || key == PASSPORT_ID) {
                    std::smatch match;
                    std::regex reg = key == HAIR_COLOUR ? hair_regex : key == EYE_COLOUR ? eye_regex : pid_regex;
                    std::regex_match(value, match, reg);
                    valid_key = match.size() >= 1 && value == match[0];
                } else if (key == HEIGHT) {
                    std::smatch match;
                    std::regex_match(value, match, height_regex);
                    if(match.size() >= 1) {
                        std::smatch extract_number;
                        std::smatch extract_type;
                        std::regex_search(value, extract_number, extract_height_regex);
                        std::regex_search(value, extract_type, extract_height_type_regex);
                        int height = std::stoi(extract_number[0]);
                        valid_key = height >= bounds[extract_type[0]][0] && height <= bounds[extract_type[0]][1];
                    }
                }
                if(valid_key) {
                    reqs_2++;
                }
            }
        }
    }
    std::cout << "First task - passports with all required fields" << std::endl << valid_1 << std::endl << std::endl;
    std::cout << "Second task - passports with all required fields valid" << std::endl << valid_2 << std::endl;
}