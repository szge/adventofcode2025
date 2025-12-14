#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int numDigits(const long long x) {
    const long long absX = (x < 0) ? -x : x;

    return (absX < 10LL ? 1 :
        (absX < 100LL ? 2 :
        (absX < 1000LL ? 3 :
        (absX < 10000LL ? 4 :
        (absX < 100000LL ? 5 :
        (absX < 1000000LL ? 6 :
        (absX < 10000000LL ? 7 :
        (absX < 100000000LL ? 8 :
        (absX < 1000000000LL ? 9 :
        (absX < 10000000000LL ? 10 :
        (absX < 100000000000LL ? 11 :
        (absX < 1000000000000LL ? 12 :
        (absX < 10000000000000LL ? 13 :
        (absX < 100000000000000LL ? 14 :
        (absX < 1000000000000000LL ? 15 :
        (absX < 10000000000000000LL ? 16 :
        (absX < 100000000000000000LL ? 17 :
        (absX < 1000000000000000000LL ? 18 :
        19))))))))))))))))));
}

// this avoids using std::pow which returns a double, losing precision
constexpr long long pow10[] = {
    1LL, 10LL, 100LL, 1000LL, 10000LL, 100000LL,
    1000000LL, 10000000LL, 100000000LL, 1000000000LL,
    10000000000LL, 100000000000LL, 1000000000000LL,
    10000000000000LL, 100000000000000LL, 1000000000000000LL,
    10000000000000000LL, 100000000000000000LL, 1000000000000000000LL
};

bool isNumInvalid(const long long num) {
    const int digits = numDigits(num);
    for (int seqLen {1}; seqLen <= digits / 2; seqLen++) {
        if (digits % seqLen) continue; // avoids passing cases like 30303, also efficiency
        long long numClone {num};
        const long long targetDigits {numClone % pow10[seqLen]};
        bool allMatching {true};
        while (numClone > 0) {
            if (numClone % pow10[seqLen] != targetDigits) {
                allMatching = false;
                break;
            }
            // reduce numClone
            numClone /= pow10[seqLen];
        }
        if (allMatching) return true;
    }
    return false;
}

long long sumOfInvalidIDs(const long long start, const long long end) {
    long long sum {0};
    for (long long i = start; i <= end; i++) {
        if (isNumInvalid(i)) {
            std::cout << "invalid ID found: " << i << "\n";
            sum += i;
        }
    }
    return sum;
}

int main()
{
    std::ifstream inf {"../day2/input.txt"};
    if (!inf)
    {
        std::cerr << "could not read file";
        return 1;
    }

    long long solution {0};

    std::string segment;
    while (std::getline(inf, segment, ',')) {
        std::istringstream ss(segment);
        std::string startStr, endStr;
        std::getline(ss, startStr, '-');
        std::getline(ss, endStr);
        std::cout << "start: " << startStr << " end: " << endStr << "\n";
        solution += sumOfInvalidIDs(std::stoll(startStr), std::stoll(endStr));
    }

    std::cout << "The solution is: " << solution << std::endl;
    return 0;
}