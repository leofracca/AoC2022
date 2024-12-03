#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

void parseInput(std::ifstream& input, std::string& memory)
{
    std::string line;
    while (std::getline(input, line))
    {
        memory += line;
    }
}

bool isSafe(const std::vector<int>& report)
{
    int a = report[0];
    int b = report[1];
    bool isIncreasing = a < b;
    bool isSafe = true;

    int i;
    for (i = 1; i < report.size(); i++)
    {
        a = report[i - 1];
        b = report[i];

        if ((a == b) ||
            (std::abs(a - b) > 3) ||
            (isIncreasing && a > b) ||
            (!isIncreasing && a < b))
        {
            return false;
        }
    }

    return true;
}

int solution1(const std::string& memory)
{
    int ans = 0;
    const std::regex pattern{R"(mul(\((\d{1,3}),(\d{1,3})\)))"};
    std::smatch matches;

    auto searchStart = memory.cbegin();
    while (std::regex_search(searchStart, memory.cend(), matches, pattern))
    {
        ans += stoi(matches[2]) * stoi(matches[3]);

        searchStart = matches.suffix().first;
    }

    return ans;
}

int solution2(const std::string& memory)
{
    int ans = 0;
    const std::regex pattern{R"(don\'t\(\)|do\(\)|mul(\((\d{1,3}),(\d{1,3})\)))"};
    std::smatch matches;

    bool enabled = true;
    auto searchStart = memory.cbegin();
    while (std::regex_search(searchStart, memory.cend(), matches, pattern))
    {
        std::string match = matches[0];

        if (match == "do()") enabled = true;
        else if (match == "don't()") enabled = false;
        else if (enabled)
            ans += stoi(matches[2]) * stoi(matches[3]);

        searchStart = matches.suffix().first;
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::string memory;
    parseInput(input, memory);

    std::cout << solution1(memory) << std::endl;
    std::cout << solution2(memory) << std::endl;
}