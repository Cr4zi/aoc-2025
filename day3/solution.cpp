#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <string_view>
#include <stack>
#include <cmath>

using u64 = uint64_t;

// returns the index of the earliest max joltage meaning 293393 returns the first 9 after 2
char LargestJoltage(std::string_view battery) {
    char max = 0;
    for(char i = 0; i < battery.length(); i++) {
        if(battery.at(i) - '0' > battery.at(max) - '0')
            max = i;
    }

    return max;
}

void solution(const std::string& filename) {
    std::fstream fs(filename, std::fstream::in);
    if(!fs.is_open())
        return;

    u64 sum1{ 0 };
    u64 sum2{ 0 };
    std::string battery;
    while(std::getline(fs, battery)) {
        /* part 1 */
        int value = 0;
        char max = LargestJoltage(battery);
        
        if(max == battery.length() - 1) {
            char second = LargestJoltage(battery.substr(0, battery.length() - 1));
            value = (battery.at(second) - '0') * 10 + (battery.at(max) - '0');
        } else {
            value = (battery.at(LargestJoltage(battery.substr(max + 1)) + max + 1) - '0') + (battery.at(max) - '0') * 10;
        }

        sum1 += value;
        
        /* part 2 */
        std::stack<char> s;
        char stack_size = 0;
        size_t len = battery.length();
        for(int i = 0; i < len; i++) {
            while(!s.empty() && battery.at(i) - '0' > s.top() && 12 - stack_size < len - i) {
                s.pop();
                stack_size--;
            }

            if(stack_size < 12) {
                s.push(battery.at(i) - '0');
                stack_size++;
            }
        }

        // assemble new num
        u64 val{ 0 };
        int i{ 0 };
        while(!s.empty()) {
            val += s.top() * std::pow(10, i);
            s.pop();
            i++;
        }
        sum2 += val;
    }


    fs.close();

    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;
}

int main() {
    solution("day3/input");
    return 0;
}
