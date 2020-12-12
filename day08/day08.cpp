#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>

#define JUMP "jmp"
#define ACCUMULATE "acc"
#define NO_OPERATION "nop"


void jump(int value, int *idx) {
    *idx += value - 1;
}

void no_operation(int value, int *idx) {
    return;
}

void accumulate(int value, int *accumulator) {
    *accumulator += value;
}

int main() {
    std::ifstream puzzle_input("day08.txt");

    std::map<std::string, std::function<void(int, int*)>> functions;
    functions[JUMP] = jump;
    functions[NO_OPERATION] = no_operation;
    functions[ACCUMULATE] = accumulate;


    std::vector<std::pair<std::string, int>> instructions;
    std::string instruction_type;
    int instruction_value;
    while(!puzzle_input.eof()) {
        puzzle_input >> instruction_type >> instruction_value;
        instructions.push_back(std::pair<std::string, int>(instruction_type, instruction_value));
    }

    int ACCUMULATOR = 0;
    int current_instruction = 0;
    std::map<std::string, int*> second_arguments;
    second_arguments[JUMP] = &current_instruction;
    second_arguments[ACCUMULATE] = &ACCUMULATOR;
    second_arguments[NO_OPERATION] = &current_instruction;

    std::set<int> visited_instructions;
    std::pair<std::string, int> instruction;
    while(visited_instructions.find(current_instruction) == visited_instructions.end()) {
        visited_instructions.insert(current_instruction);
        instruction = instructions[current_instruction];
        functions[instruction.first](instruction.second, second_arguments[instruction.first]);
        current_instruction = current_instruction + 1;
    }
    std::cout << "First task - what is the value of the accumulator before we notice a loop?" << std::endl << ACCUMULATOR << std::endl << std::endl;

    std::map<std::string, std::string> swap_pair;
    swap_pair[JUMP] = NO_OPERATION;
    swap_pair[NO_OPERATION] = JUMP;
    for(auto &instr : instructions) {
        if(swap_pair.find(instr.first) == swap_pair.end()) {
            continue;
        }
        instr.first = swap_pair[instr.first];
        visited_instructions.clear();
        current_instruction = 0;
        ACCUMULATOR = 0;
        while(visited_instructions.find(current_instruction) == visited_instructions.end() && current_instruction < instructions.size()) {
            visited_instructions.insert(current_instruction);
            instruction = instructions[current_instruction];
            functions[instruction.first](instruction.second, second_arguments[instruction.first]);
            current_instruction = current_instruction + 1;
        }
        if(current_instruction >= instructions.size()) {
            std::cout << "Second task - what is the value of the accumulator when the program terminates?" << std::endl << ACCUMULATOR << std::endl << std::endl;
            break;
        } 
        instr.first = swap_pair[instr.first];
    }
}