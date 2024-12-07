#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>

void parseInput(std::ifstream& input, std::vector<std::pair<uint64_t, std::vector<int>>>& equations)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;

        equations.push_back({});

        while (ss >> word)
        {
            if (word[word.size() - 1] == ':')
                equations[equations.size() - 1].first = std::stoull(word.substr(0, word.size() - 1));
            else
                equations[equations.size() - 1].second.push_back(std::stoull(word));
        }
    }
}

bool recursionHelper1(const uint64_t expectedResult, const std::vector<int>& operands, uint64_t currentResult, int index)
{
    if (expectedResult == currentResult && index == operands.size())
        return true;
    if (expectedResult < currentResult)
        return false;
    if (index == operands.size())
        return false;

    return recursionHelper1(expectedResult, operands, currentResult + operands[index], index + 1) ||
           recursionHelper1(expectedResult, operands, currentResult * operands[index], index + 1);
}

bool recursionHelper2(const uint64_t expectedResult, const std::vector<int>& operands, uint64_t currentResult, int index)
{
    if (expectedResult == currentResult && index == operands.size())
        return true;
    if (expectedResult < currentResult)
        return false;
    if (index == operands.size())
        return false;

    return recursionHelper2(expectedResult, operands, currentResult + operands[index], index + 1) ||
           recursionHelper2(expectedResult, operands, currentResult * operands[index], index + 1) ||
           recursionHelper2(expectedResult, operands, std::stoull(std::to_string(currentResult) + std::to_string(operands[index])), index + 1);
}

uint64_t solution1(const std::vector<std::pair<uint64_t, std::vector<int>>>& equations)
{
    uint64_t ans = 0;

    for (const auto& equation : equations)
        if (recursionHelper1(equation.first, equation.second, 0, 0))
            ans += equation.first;
    
    return ans;
}

uint64_t solution2(const std::vector<std::pair<uint64_t, std::vector<int>>>& equations)
{
    uint64_t ans = 0;

    for (const auto& equation : equations)
        if (recursionHelper2(equation.first, equation.second, 0, 0))
            ans += equation.first;

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::pair<uint64_t, std::vector<int>>> equations; // result, operands
    parseInput(input, equations);

    std::cout << solution1(equations) << std::endl;
    std::cout << solution2(equations) << std::endl;
}