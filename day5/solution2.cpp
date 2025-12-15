#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main () {
    std::ifstream inf { "../day5/input.txt" };
    if (!inf) {
        std::cerr << "could not read file";
        return 1;
    }

    std::string strInput{};
    std::vector<std::pair<long long, long long>> intervals{};
    while (std::getline(inf, strInput)) {
        if (strInput.contains('-'))
        {
            std::istringstream ss(strInput);
            long long start, end;
            char dash;
            if (ss >> start >> dash >> end && dash == '-') {
                intervals.emplace_back(start, end);
            }
        }
    }

    // interval merging
    // 1. sort the intervals by their starts
    std::ranges::sort(intervals); // thanks, c++!
    // 2. if curr overlaps with prev, then combine
    std::vector result{intervals[0]};
    for (int i {1}; i < intervals.size(); ++i)
    {
        auto& [prev_lb, prev_ub] = result.back();
        const auto [curr_lb, curr_ub] = intervals[i];
        if (curr_lb <= prev_ub)
        {
            prev_ub = std::max(curr_ub, prev_ub);
        } else
        {
            result.emplace_back(curr_lb, curr_ub);
        }
    }

    long long solution {0};
    for (auto [lb, ub] : result)
    {
        // std::println("lb: {}, ub: {}", lb, ub);
        solution += ub - lb + 1;
    }

    std::println("The solution is {}", solution);

    return 0;
}
