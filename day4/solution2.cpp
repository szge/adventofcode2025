#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 *
 * @param grid
 * @param grid_dims pair <width, height>
 * @param pos current position <x, y>
 * @return whether or not the roll can be moved; rule: a roll can be moved if there are <4 adjacent rolls
 */
bool is_valid(const std::vector<bool>& grid, std::pair<int, int> grid_dims, std::pair<int, int> pos)
{
    const auto [width, height] = grid_dims;
    const auto [x, y] = pos;

    int neighbor_rolls {0};
    std::vector<std::pair<int, int>> neighbors{};

    for (int n_x {std::max(0, x - 1)}; n_x <= std::min(width - 1, x + 1); ++n_x)
    {
        for (int n_y {std::max(0, y - 1)}; n_y <= std::min(height - 1, y + 1); ++n_y)
        {
            if (!(n_x == x && n_y == y)) neighbors.emplace_back(n_x, n_y);
        }
    }

    for (const auto [n_x, n_y] : neighbors)
    {
        neighbor_rolls += grid[width * n_y + n_x];
        if (neighbor_rolls == 4) return false;
    }

    return true;
}

/**
 *
 * @param grid
 * @param grid_dims pair <width, height>
 * @return
 */
int count_num_removed(std::vector<bool>& grid, std::pair<int, int> grid_dims)
{
    auto [width, height] = grid_dims;
    int num_removed {0};
    bool has_removed {true};
    while (has_removed)
    {
        has_removed = false;
        for (int y {0}; y < height; ++y)
        {
            for (int x {0}; x < width; ++x)
            {
                if (grid[y * width + x] && is_valid(grid, grid_dims, {x, y}))
                {
                    ++num_removed;
                    grid[y * width + x] = false;
                    has_removed = true;
                }
            }
        }
    }
    return num_removed;
}

int main () {
    std::ifstream inf { "../day4/input.txt" };
    if (!inf) {
        std::cerr << "could not read file";
        return 1;
    }

    std::string strInput{};
    std::vector<bool> grid;
    int width {1};
    while (std::getline(inf, strInput)) {
        width = static_cast<int>(strInput.length());
        for (const auto c : strInput) grid.push_back(c == '@');
    }
    const int height = static_cast<int>(grid.size()) / width;

    std::println("The solution is {}", count_num_removed(grid, {width, height}));

    return 0;
}
