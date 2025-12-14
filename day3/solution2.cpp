#include <fstream>
#include <iostream>
#include <string>
#include <print>

constexpr long long pow10[] = {
    1LL, 10LL, 100LL, 1000LL, 10000LL, 100000LL,
    1000000LL, 10000000LL, 100000000LL, 1000000000LL,
    10000000000LL, 100000000000LL, 1000000000000LL,
    10000000000000LL, 100000000000000LL, 1000000000000000LL,
    10000000000000000LL, 100000000000000000LL, 1000000000000000000LL
};

int getHighestDigitIdx(const std::string_view num_sv) {
    if (num_sv.empty()) return 0;
    int highestDigit {0};
    int highestDigitIdx {0};
    for (int i {0}; i < num_sv.length(); i++) {
        if (num_sv[i] - '0' > highestDigit) {
            highestDigit = num_sv[i] - '0';
            highestDigitIdx = i;
        }
    }
    return highestDigitIdx;
}

constexpr int JOLTAGE_LENGTH = 12; // number of digits allowed in the joltage solution

long long getJoltage(const std::string_view num_sv) {
    long long highestJoltage {0LL};

    int prevSelectedIdx {0};
    // std::println("Solving input {}", num_sv);
    // employ greedy alg; always select the highest number first
    for (int sol_digit {0}; sol_digit < JOLTAGE_LENGTH; sol_digit++) {
        // 1. from the remaining digits, get the index of the highest digit
        const int lower_idx = (sol_digit == 0) ? 0 : prevSelectedIdx + 1; // anything after the previously selected digit is acceptable
        const int higher_idx = static_cast<int>(num_sv.length()) - JOLTAGE_LENGTH + sol_digit + 1; // anything before
        const std::string_view pick_from_digits {num_sv.substr(lower_idx, higher_idx - lower_idx)};
        // std::println("attempting solution, lower_idx {}, higher_idx {}, pick_from_digits {}", lower_idx, higher_idx, pick_from_digits);
        const int selectedIdx = lower_idx + getHighestDigitIdx(pick_from_digits);
        // std::println("picking value {}", num_sv[selectedIdx]);
        // 2. add it into highestJoltage (with the appropriate magnitude)
        highestJoltage += (num_sv[selectedIdx] - '0') * pow10[JOLTAGE_LENGTH - sol_digit - 1];
        prevSelectedIdx = selectedIdx;
    }
    // std::println("final highestJoltage answer: {}", highestJoltage);

    return highestJoltage;
}

int main () {
    std::ifstream inf { "../day3/input.txt" };
    if (!inf) {
        std::cerr << "could not read file";
        return 1;
    }

    long long solution{0LL};

    std::string strInput{};
    while (std::getline(inf, strInput)) {
        solution += getJoltage(strInput);
    }

    std::println("The solution is: {}", solution);

    return 0;
}