#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstdint>

void solution(const std::string& filename) {
    std::fstream fs(filename, std::fstream::in);
    std::string line;

    if(!fs.is_open())
        return;


    int dial{ 50 };
    ssize_t part1{ 0 };
    ssize_t part2{ 0 };
    
    while(std::getline(fs, line)) {
        ssize_t direction = line.at(0) == 'L' ? -1 : 1;
        try {
            int value = std::stoi(line.substr(1));
            for(int i = 0; i < value; i++) {
                dial = (dial + direction) % 100;
                if(dial == 0)
                    part2++;
            }
        } catch(std::invalid_argument const& ex) {
            std::cout << ex.what() << std::endl;
        } catch(std::out_of_range const& ex) {
            std::cout << ex.what() << std::endl;
        }

        if(dial == 0)
            part1++;
        
    }

    fs.close();
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}


int main() {
    solution("day1/input");

    return 0;
}
