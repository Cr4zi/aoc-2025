#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

using u64 = uint64_t;

bool is_invalidp1(u64 num) {
    int digits = std::floor(std::log10(num)) + 1;
    u64 half = digits / 2;

    if(digits % 2 != 0)
        return false;

    u64 first_half = num % static_cast<u64>(std::pow(10, half));
    u64 second_half = num / static_cast<u64>(std::pow(10, half));
    return first_half == second_half;
}

bool is_invalid(u64 num) {
    int digits = std::floor(std::log10(num)) + 1;

    for(int i = 1; i <= digits / 2; i++) {
        if(digits % i != 0)
            continue;

        u64 ten_length = static_cast<u64>(std::pow(10, i));
        u64 seq = num % ten_length;
        u64 temp{ num };

        bool repeat = true;
        while(temp != 0 && repeat) {
            if(temp % ten_length != seq)
                repeat = false;

            temp /= ten_length;
        }

        if(repeat)
            return true;
    }
    return false;
}

void solution(const std::string& filename) {
    std::fstream fs(filename, std::fstream::in);
    if(!fs.is_open())
        return;
        
    std::string range;
    u64 sum1 { 0 };
    u64 sum2 { 0 };
    while(std::getline(fs, range, ',')) {
        char *token = std::strtok(range.data(), "-");
        u64 start = std::stoll(token);
        token = std::strtok(nullptr, "-");
        u64 end = std::stoll(token);

        std::cout << start << "-" << end << std::endl;
        for(u64 i = start; i <= end; i++) {
            if(is_invalidp1(i))
                sum1 += i;
            if(is_invalid(i))
                sum2 += i;

        }
    }
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;
}

int main() {
    solution("day2/input");

    return 0;
}

