#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

void parseInput(std::ifstream& input, std::vector<int>& left, std::vector<int>& right)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            left.push_back(std::stoi(word));
            ss >> word;
            right.push_back(std::stoi(word));
        }
    }
}

int solution1(const std::vector<int>& left, const std::vector<int>& right)
{
    int ans = 0;

    for (int i = 0; i < left.size(); i++)
        ans += std::abs(left[i] - right[i]);

    return ans;
}

int solution2(const std::vector<int>& left, const std::vector<int>& right)
{
    int ans = 0;
    std::unordered_map<int, int> counts;

    for (const int i : right)
        counts[i]++;

    for (const int i : left)
        ans += (i * counts[i]);

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<int> left, right;
    parseInput(input, left, right);

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::cout << solution1(left, right) << std::endl;
    std::cout << solution2(left, right) << std::endl;
}