#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main () {
    std::ifstream input("day02.txt");
    int lb, ub, count, valid_one = 0, valid_two = 0;
    char letter;
    while(!input.eof()) {
        char* line = (char*) malloc((uint) 64);
        char password[32];

        input.getline(line, (long int) 64);
        sscanf(line, "%d-%d %c: %s", &lb, &ub, &letter, password);

        std::string pwd(password);
        // task one
        count = std::count(pwd.begin(), pwd.end(), letter);
        if (count <= ub && count >= lb) {
            valid_one++;
        }
        // task two
        if ((pwd[lb-1] == letter) ^ (pwd[ub-1] == letter)) {
            valid_two++;
        }
    }
    std::cout << "First task - number of valid passwords with letter occurrence within range" << std::endl << valid_one << std::endl << std::endl;
    std::cout << "Second task - number of valid passwords with only one letter at either position" << std::endl << valid_two << std::endl;
    return 0;
}