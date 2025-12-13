#include <iostream>
#include <fstream>

int main()
{
    std::ifstream inf { "../day1/input.txt" };
    if (!inf)
    {
        std::cerr << "could not read file";
        return 1;
    }

    int answer {0};

    int rot {50};
    std::string strInput{};
    while (std::getline(inf, strInput))
    {
        const char dir = strInput[0];
        int amt = std::stoi(strInput.substr(1));
        if (dir == 'L') amt *= -1;
        rot += amt;
        rot = ((rot % 100) + 100) % 100; // guarantees non-negative result
        answer += (rot == 0);
    }

    std::cout << "The answer is: " << answer << std::endl;
    return 0;
}