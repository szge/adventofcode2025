#include <fstream>
#include <iostream>

int getJoltage(const std::string_view sv) {
    int highestJoltage {0};
    for (int firstIdx {0}, firstNum{sv[firstIdx] - '0'}; firstIdx < sv.length(); firstIdx++, firstNum = sv[firstIdx] - '0') {
        for (int secondIdx {firstIdx + 1}, secondNum{sv[secondIdx] - '0'}; secondIdx < sv.length(); secondIdx++, secondNum = sv[secondIdx] - '0') {
            const int joltage {firstNum * 10 + secondNum};
            if (joltage > highestJoltage) highestJoltage = joltage;
        }
    }
    return highestJoltage;
}

int main () {
    std::ifstream inf { "../day3/input.txt" };
    if (!inf) {
        std::cerr << "could not read file";
        return 1;
    }

    int solution{0};

    std::string strInput{};
    while (std::getline(inf, strInput)) {
        solution += getJoltage(strInput);
    }

    std::cout << "The solution is: " << solution << std::endl;

    return 0;
}
