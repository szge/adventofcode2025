#include <iostream>
#include <fstream>

// how many clicks happen when currRot is rotated by change
int numClicks(const int currRot, const int change)
{
    // currRot = 20, change = -230, result = 90, clicks = 3
    // currRot = 20, change = 290, result = 10, clicks = 3
    const int hundredsClicks = abs(change / 100); // integer division
    if (currRot == 0) return hundredsClicks;
    const int remainingChange = change % 100; // should be signed
    const int finalRot = currRot + remainingChange;
    const bool extraClick = (finalRot <= 0) || (finalRot >= 100);
    return hundredsClicks + extraClick;
}

// the result of rotating curr by change. non-negative result guaranteed (0-99)
int rotate(const int currRot, const int change)
{
    return (((currRot + change) % 100) + 100) % 100;
}

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
        int change = std::stoi(strInput.substr(1));
        if (dir == 'L') change *= -1;
        answer += numClicks(rot, change);
        rot = rotate(rot, change);
        // std::cout << "answer: " << answer << " rot: " << rot << "\n";
    }

    std::cout << "The answer is: " << answer << std::endl;
    return 0;
}