#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    std::ifstream inf {"../day2/input.txt"};
    if (!inf)
    {
        std::cerr << "could not read file";
        return 1;
    }

    int solution {0};

    std::istringstream input;


    std::cout << "The solution is: " << solution << std::endl;
    return 0;
}