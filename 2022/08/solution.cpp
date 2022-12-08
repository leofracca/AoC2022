#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<int>> trees;

    constexpr int ASCII_OFFSET = 48;

    int i = 0;
    std::string line;
    while (std::getline(input, line))
    {
        trees.push_back({});

        for (auto c : line)
            trees[i].push_back(c - ASCII_OFFSET);
        i++;
    }

    // Print the trees
    // for (auto v : trees)
    // {
    //     for (auto t : v)
    //         std::cout << t;
    //     std::cout << "\n";
    // }

    // Loop through the trees (matrix)
    int task1 = 0, task2 = 0;
    for (int i = 1; i < trees.size() - 1; i++)
    {
        for (int j = 1; j < trees[i].size() - 1; j++)
        {
            // Check if the current tree is visible from at least one side
            // Check how many trees are visible from the current tree
            bool visibleLeft = true, visibleRight = true, visibleTop = true, visibleBottom = true; // Visible from that side
            int treesLeft = 0, treesRight = 0, treesTop = 0, treesBottom = 0; // Number of trees visible from the current tree
            int current = trees[i][j];

            // Look left
            for (int k = j - 1; k >= 0; k--)
            {
                treesLeft++;
                if (trees[i][k] >= current)
                {
                    visibleLeft = false;
                    break;
                }
            }

            // Look right
            for (int k = j + 1; k < trees[i].size(); k++)
            {
                treesRight++;
                if (trees[i][k] >= current)
                {
                    visibleRight = false;
                    break;
                }
            }

            // Look top
            for (int k = i - 1; k >= 0; k--)
            {
                treesTop++;
                if (trees[k][j] >= current)
                {
                    visibleTop = false;
                    break;
                }
            }

            // Look bottom
            for (int k = i + 1; k < trees.size(); k++)
            {
                treesBottom++;
                if (trees[k][j] >= current)
                {
                    visibleBottom = false;
                    break;
                }
            }

            if (visibleLeft || visibleRight || visibleTop || visibleBottom)
                task1++;

            int scenicScore = treesLeft * treesRight * treesTop * treesBottom;
            if (scenicScore > task2)
                task2 = scenicScore;
        }
    }

    // Add the perimeter (task1)
    task1 += (trees.size() + trees[0].size() - 2) * 2;

    std::cout << task1 << std::endl;
    std::cout << task2 << std::endl;

    return 0;
}