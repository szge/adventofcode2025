#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main () {
    std::ifstream inf { "../day5/input.txt" };
    if (!inf) {
        std::cerr << "could not read file";
        return 1;
    }

    int solution {0};

    std::string strInput{};
    std::vector<std::pair<long long, long long>> ranges{};
    std::vector<long long> ingredient_ids{};
    while (std::getline(inf, strInput)) {
        if (strInput.empty()) continue;
        if (strInput.contains('-'))
        {
            std::istringstream ss(strInput);
            long long start, end;
            char dash;
            if (ss >> start >> dash >> end && dash == '-') {
                ranges.emplace_back(start, end);
            }
        }
        else
        {
            ingredient_ids.emplace_back(std::stoll(strInput));
        }
    }

    for (const auto ingredient_id : ingredient_ids)
    {
        for (const auto [lb, ub] : ranges)
        {
            if (lb <= ingredient_id && ingredient_id <= ub)
            {
                ++solution;
                break;
            }
        }
    }

    std::println("The solution is {}", solution);

    return 0;
}
