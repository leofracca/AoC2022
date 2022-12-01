#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>

void task1(int currentSum, int &maxValue)
{
    if (currentSum > maxValue)
        maxValue = currentSum;
}

void task2(int currentSum, std::array<int, 3> &topThree)
{
    int minOfTopThree = *std::min_element(topThree.begin(), topThree.end());
    int index = std::distance(topThree.begin(), std::find(topThree.begin(), topThree.end(), minOfTopThree));
    if (currentSum > minOfTopThree)
        topThree[index] = currentSum;
}

int main()
{
    std::ifstream input("input.txt");
    std::string line;
    int maxValue = -1;
    int currentSum = 0;
    std::array<int, 3> topThree = {-1, -1, -1};
    
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            task1(currentSum, maxValue);
            task2(currentSum, topThree);
            
            currentSum = 0;
        }
        else
            currentSum += std::stoi(line);
    }

    std::cout << maxValue << std::endl;
    std::cout << topThree[0] + topThree[1] + topThree[2] << std::endl;

    return 0;
}