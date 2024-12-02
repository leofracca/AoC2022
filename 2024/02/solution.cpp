#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

void parseInput(std::ifstream& input, std::vector<std::vector<int>>& reports)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;

        reports.push_back({});
        while (ss >> word)
        {
            reports[reports.size() - 1].push_back(std::stoi(word));
        }
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

int solution1(const std::vector<std::vector<int>>& reports)
{
    int ans = 0;

    for (auto const& report : reports)
    {
        if (isSafe(report))
            ans++;
    }

    return ans;
}

// Brute force approach :D
// TODO: give an optimized implementation
int solution2(std::vector<std::vector<int>>& reports)
{
    int ans = 0;

    for (auto& report : reports)
    {
        bool safe = false;
        int i = 0;
        while (!safe && i < report.size())
        {
            int tmp = report[i];
            report.erase(report.begin() + i);
            safe = isSafe(report);
            report.insert(report.begin() + i, tmp);
            i++;
        }

        if (safe)
            ans++;
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<int>> reports;
    parseInput(input, reports);

    std::cout << solution1(reports) << std::endl;
    std::cout << solution2(reports) << std::endl;
}